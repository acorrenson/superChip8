#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include "utils.h"
#include "system.h"


int main(int argc, char const *argv[]) {
  
  // -- INIT CHIP8 SYSTEM -- 
  unsigned char memory[4096];
  unsigned short PC = 512;
  unsigned char V[16];
  unsigned short stack[48];
  unsigned char stackPtr = 0;

  unsigned short I = 0;

  unsigned short opCode;
  unsigned short delayTimer = 0;
  unsigned short soundTimer = 0;
  
  memset(memory, 0, sizeof(memory));
  memset(V, 0, sizeof(V));
  memset(stack, 0, sizeof(stack));

  int quit = 0;
  int romSize;

  FILE * f = fopen(argv[1], "rb");
  romSize = fread(&memory[0x200], 1, MAXSIZE, f);
  fclose(f);

  printf("ROM size %d\n", romSize);

  for (int i = 0; i < romSize; i+=2) {
    unsigned short opc = (memory[0x200+i] << 8 ) | (memory[0x200+i+1]);
    desasembler(opc, V, I, stack, stackPtr);
  }

  int keyBoardState[16] =
    {0, 0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  unsigned char charTable[16][5] = {
    {0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
    {0x20, 0x60, 0x20, 0x20, 0x70}, // 1
    {0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
    {0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
    {0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
    {0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
    {0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
    {0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
    {0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
    {0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
    {0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
    {0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
    {0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
    {0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
    {0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
    {0xF0, 0x80, 0xF0, 0x80, 0x80}  // E
  };

  unsigned char screen[32][64];

  // filling memory with standard sprites
  for (int i = 0; i < 16; i++)
    for (int j = 0; j < 5; j++)
      memory[i*5+j] = charTable[i][j];

  for (int i = 0; i < 32; i++)
    for (int j = 0; j < 64; j++)
      screen[i][j] = 0;

  // -- INIT WINDOW --
  printf("Creating superChip8 window\n");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* pWindow = NULL;
  SDL_Renderer* renderer;

  pWindow = SDL_CreateWindow(
    "superChip8",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_SHOWN);

  // state of the keyboard
  const Uint8 *state;
  // current event
  SDL_Event e;
  // while the window is open
  quit = 0;
  
  // -- MAIN PROGRAM --

  if ( pWindow ) {
    printf("Successfully created superChip8 window\n");

    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    clearScreen(renderer, screen);

    // LOOP
    while ( !quit ) {
      state = SDL_GetKeyboardState(NULL);
      while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) {
          quit = 1;
        }
      }
      
      setKeyBoardState(state, keyBoardState);      
      opCode = (memory[PC] << 8) | (memory[PC+1]);

      unsigned short nnn = opCode & 0x0FFF;
      unsigned char x = (opCode & 0x0F00) >> 8;
      unsigned char y = (opCode & 0x00F0) >> 4;
      unsigned char n = opCode & 0x000F;
      unsigned short kk = opCode & 0x00FF;

      if (opCode == 0x00E0){
        // CLS
        printf("%04X - CLS\n", opCode);
        for (int i = 0; i < 32; i++)
          for (int j = 0; j < 64; j++)
            screen[i][j] = 0;
        PC += 2;
      }

      else if (opCode == 0x00EE) {
        // RET
        printf("%04X - RET [nw PC = %d]\n", opCode, stack[stackPtr]);
        PC = stack[stackPtr];
        stack[stackPtr] = 0;
        --stackPtr;
      }
      
      else if (opCode >> 12 == 0x0) {
        printf("%04X - DEPRECATED SYS CALL\n", opCode);
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0x1000) {
        printf("%04X - JP %d\n", opCode, nnn);
        PC = nnn;
      }
      
      else if ((opCode & 0xF000) == 0x2000) {
        printf("%04X - CALL %d\n", opCode, nnn);
        ++stackPtr;
        stack[stackPtr] = PC+2;
        PC = nnn;
      }
      
      else if ((opCode & 0xF000) == 0x3000) {
        printf("%04X - SE V%d (%d) %d\n", opCode, x, V[x], kk);
        PC += V[x] == kk ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0x4000) {
        // SNE_Vx_byte(opCode, pProgramCounter, V);
        printf("%04X - SNE_Vx_byte\n", opCode);
        PC += V[x] != kk ? 4 : 2;
      }
      
      else if ((opCode & 0xF00F) == 0x5000) {
        printf("%04X - SE V%d (%d) V%d (%d)\n", opCode, x, V[x], y, V[y]);
        PC += V[x] == V[y] ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0x6000) {
        printf("%04X - LD V%d (%d) %d\n", opCode, x, V[x], kk);
        V[x] = kk;
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0x7000) {
        // ADD Vx Byte
        printf("%04X - ADD V%d (%d) %d\n", opCode, x, V[x], kk);
        V[x] += kk;
        PC += 2;
      }
        
      else if ((opCode & 0xF00F) == 0x8000) {
        printf("%04X - LD V%d (%d) V%d %d\n", opCode, x, V[x], y, V[y]);
        V[x] = V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8001) {
        printf("%04X - OR_Vx_Vy\n", opCode);
        V[x] = V[x] | V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8002) {
        printf("%04X - AND_Vx_Vy\n", opCode);
        V[x] = V[x] & V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8003) {
        printf("%04X - XOR_Vx_Vy\n", opCode);
        V[x] = V[x] ^ V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8004) {
        printf("%04X - ADD V%d (%d) V%d (%d) \n", opCode, x, V[x], y, V[y]);
        if ((int) V[x] + (int) V[y] > 255)
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] + V[y];
        PC += 2; 
      }
      
      else if ((opCode & 0xF00F) == 0x8005) {
        printf("%04X - SUB Vx - Vy\n", opCode);
        if (V[x] > V[y])
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] - V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8006) {
        printf("%04X - SHR Vx\n", opCode);
        if (V[x] << 7 != 0)
          V[15] = 1;
        else
          V[15] = 1;
        V[x] = V[x] >> 2;
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8007) {
        printf("%04X - SUNB Vx Vy\n", opCode);
        if (V[y] > V[x])
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[y] - V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x800E) {
        printf("%04X - SHL Vx\n", opCode);
        if (V[x] >> 7 == 0x1)
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] << 2;
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x9000) {
        printf("%04X - SNE V%d (%d) V%d (%d)\n", opCode, x, V[x], y, V[y]);
        PC += V[x] != V[y] ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0xA000) {
        printf("%04X - LD I %d [set I = %d]\n", opCode, nnn, nnn);
        I = nnn;
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0xB000) {
        printf("%04X - JP V%d (%d)  + %d\n", opCode, x, V[x], nnn);
        PC = V[0] + nnn;
      }
      
      else if ((opCode & 0xF000) == 0xC000) {
        printf("%04X - RND\n", opCode);
        srand(time(0));
        unsigned char r = rand() % 256;
        V[x] = r & kk;
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0xD000) {
        printf("%04X - DRW %d\n", opCode, I);        
        int col = sprite(screen, &memory[I], n, V[x], V[y]);
        V[15] = col;
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xE09E) {
        printf("%04X - SKP K\n", opCode);
        if (keyBoardState[V[x]])
          PC += 4;
        else
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xE0A1) {
        printf("%04X - SKNP Vx\n", opCode);
        if (!keyBoardState[V[x]])
          PC += 4;
        else
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF007) {
        printf("%04X - LD_Vx_DT\n", opCode);
        V[x] = delayTimer;
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF00A) {
        printf("%04X - LD_Vx_K\n", opCode);
        int pressed = 0;
        for (int i = 0; i < 16; i++) {
          if (keyBoardState[i] == 1) {
            V[x] = i;
            pressed = 1;
            i = 16;
          }
        }

        if (pressed)
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF015) {
        printf("%04X - LD_DT_Vx\n", opCode);
        delayTimer = V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF018) {
        printf("%04X - LD_ST_Vx\n", opCode);
        soundTimer = V[x];
        PC += 2; 
      }
      
      else if ((opCode & 0xF0FF) == 0xF01E) {
        printf("%04X - ADD I (%d) V%d (%d)\n", opCode, I, x, V[x]);
        I = I + V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF029) {
        printf("%04X - LD F V%d (%d) [set I to %d]\n", opCode, x, V[x], V[x]*5);
        I = V[x] * 5;
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF033) {
        printf("%04X - LD B\n", opCode);
        memory[I]   = (V[x] % 1000) / 100; // hundred's digit
        memory[I+1] = (V[x] % 100) / 10;   // ten's digit
        memory[I+2] = (V[x] % 10); // one's digit
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF055) {
        printf("%04X - LD I V%d (%d) [set mem %d-%d]\n", opCode, x, V[x], I, I+x);
        for(int i = 0; i < x; i++)
          memory[I+x] = V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF065) {
        printf("%04X - LD V%d (%d) I [set reg %d-%d]\n", opCode, x, V[x], 0, x);
        for(int i = 0; i < x; i++)
          V[x] = memory[I+x];
        PC += 2;
      }

      renderAll(renderer, screen);
      
      SDL_RenderPresent(renderer);

      updateTimers(&delayTimer, &soundTimer);

      // Read instructions at 60Hz
      SDL_Delay(2);

    }
  } else {
    // ERROR
    printf("Error ! \n");
  }
  
  // EXIT
  SDL_Quit();
  return 0;
}
