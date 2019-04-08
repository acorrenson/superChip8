#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "readRom.h"
#include "system.h"
#define MAXSIZE 0X10000 - 0x200

int sprite(unsigned char screen[32][64],
  unsigned char buff[], int size, int x, int y)
{
  int col;
  unsigned char test;
  unsigned char code;
  for (int i = 0; i < size; i++) {
    for (int j = 7; j >= 0; j--) {
      code = buff[i];
      test = (unsigned char) pow(2, j);
      if ( (code & test) ==  test ) {
        if ( screen[(i + y)%32][(7 - j + x)%64] == 0 ) {
          screen[(i + y)%32][(7 - j + x)%64] = 1;
        } else {
          screen[(i + y)%32][(7 - j + x)%64] = 0;
          col = 1;
        }
      }
    }
  }
  return col;
}

int main(int argc, char const *argv[]) {
  
  // -- INIT CHIP8 SYSTEM -- 
  unsigned char memory[4096];
  unsigned short PC = 512;
  unsigned char V[16];
  unsigned short stack[48];
  unsigned char stackPtr;

  unsigned short I;

  unsigned short opCode;
  unsigned short delayTimer;
  unsigned short soundTimer;

  int quit = 0;
  int romSize;

  FILE * f = fopen("/Users/arthur/Downloads/chip8-master/roms/brix.rom", "rb");
  romSize = fread(&memory[0x200], 1, MAXSIZE, f);
  fclose(f);

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

      printf("%04X\n", opCode);

      unsigned short nnn = opCode & 0x0FFF;
      unsigned char x = (opCode & 0x0F00) >> 8;
      unsigned char y = (opCode & 0x00F0) >> 4;
      unsigned char n = opCode & 0x000F;
      unsigned short kk = opCode & 0x00FF;

      if (opCode == 0x00E0){
        // CLS
        for (int i = 0; i < 32; i++)
          for (int j = 0; j < 64; j++)
            screen[i][j] = 0;
        PC += 2;
      }

      else if (opCode == 0x00EE) {
        // RET
        PC = stack[stackPtr];
        printf("ret to %d -> %04X\n", PC, memory[PC]);
        --stackPtr;
      }
      
      else if (opCode >> 12 == 0x0) {
        printf("%04X - DEPRECATED SYS CALL\n", opCode);
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0x1000) {
        // JP addr
        // printf("JP to %04X\n", nnn);
        PC = nnn;
      }
      
      else if ((opCode & 0xF000) == 0x2000) {
        // CALL
        ++stackPtr;
        printf("CALL to %d saving %d\n", nnn, PC);
        stack[stackPtr] = PC;
        PC = nnn;
      }
      
      else if ((opCode & 0xF000) == 0x3000) {
        // SE_Vx_byte(opCode, pProgramCounter, V);
        printf("V%d = %d, kk = %d\n", x, V[x], kk);
        PC += V[x] == kk ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0x4000) {
        // SNE_Vx_byte(opCode, pProgramCounter, V);
        PC += V[x] != kk ? 4 : 2;
      }
      
      else if ((opCode & 0xF00F) == 0x5000) {
        // SE_Vx_Vy(opCode, pProgramCounter, V);
        PC += V[x] == V[y] ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0x6000) {
        // LD_Vx_byte(opCode, pProgramCounter, V);
        V[x] = kk;
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0x7000) {
        // ADD Vx Byte
        V[x] += kk;
        printf("V%u = %d\n", x, V[x]);
        PC += 2;
      }
        
      else if ((opCode & 0xF00F) == 0x8000) {
        // LD_Vx_Vy(opCode, pProgramCounter, V);
        V[x] = V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8001) {
        // OR Vx Vy
        V[x] = V[x] | V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8002) {
        // AND_Vx_Vy
        V[x] = V[x] & V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8003) {
        // XOR_Vx_Vy
        V[x] = V[x] ^ V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8004) {
        // ADD_Vx_Vy
        if ((int) V[x] + (int) V[y] > 255)
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] + V[y];
        PC += 2; 
      }
      
      else if ((opCode & 0xF00F) == 0x8005) {
        if (V[x] > V[y])
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] - V[y];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8006) {
        // SHR_Vx(opCode, pProgramCounter, V);
        if (V[x] << 7 != 0)
          V[15] = 1;
        else
          V[15] = 1;
        V[x] = V[x] >> 2;
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x8007) {
        // SUBN_Vx_Vy(opCode, pProgramCounter, V);
        if (V[y] > V[x])
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[y] - V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x800E) {
        // SHL_Vx(opCode, pProgramCounter, V);
        if (V[x] >> 7 == 0x1)
          V[15] = 1;
        else
          V[15] = 0;
        V[x] = V[x] << 2;
        PC += 2;
      }
      
      else if ((opCode & 0xF00F) == 0x9000) {
        // SNE_Vx_Vy(opCode, pProgramCounter, V);
        PC += V[x] != V[y] ? 4 : 2;
      }
      
      else if ((opCode & 0xF000) == 0xA000) {
        // LD_I_addr(opCode, pProgramCounter, pI);
        I = nnn;
        PC += 2;
      }
      
      else if ((opCode & 0xF000) == 0xB000) {
        // JP_V0_addr(opCode, pProgramCounter, V);
        PC = V[0] + nnn;
      }
      
      else if ((opCode & 0xF000) == 0xC000) {
        // RND_Vx_byte(opCode, pProgramCounter, V);
      }
      
      else if ((opCode & 0xF000) == 0xD000) {
        // DRW_Vx_Vy_nibble(opCode, pProgramCounter, V, pI, screen, memory);
        printf("DRW %d pt at %d %d from %d\n", n, V[x], V[y], I);
        int col = sprite(screen, &memory[I], n, V[x], V[y]);
        // unsigned char test;
        // unsigned char code;
        // for (int i = 0; i < n; i++) {
        //   printf("%04X\n", memory[I+i]);
        //   for (int j = 7; j >= 0; j--) {
        //     code = memory[I+i];
        //     test = (unsigned char) pow(2, j);
        //     if ( (code & test) ==  test ) {
        //       if ( screen[(i + V[y])%32][(7 - j + V[x])%64] == 0 ) {
        //         // printf("%d %d\n", (i + V[y])%32, (7 - j + V[x])%64);
        //         screen[(i + V[y])%32][(7 - j + V[x])%64] = 1;
        //       } else {
        //         screen[(i + V[y])%32][(7 - j + V[x])%64] = 0;
        //         col = 1;
        //       }
        //     }
        //   }
        // }
        V[15] = col;
        PC += 2;
        printf("FIN DRW\n");
      }
      
      else if ((opCode & 0xF0FF) == 0xE09E) {
        // SKP_Vx(opCode, pProgramCounter, V, keyBoardState);
        if (keyBoardState[V[x]])
          PC += 4;
        else
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xE0A1) {
        // SKNP_Vx(opCode, pProgramCounter, V, keyBoardState);
        if (!keyBoardState[V[x]])
          PC += 4;
        else
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF007) {
        // LD_Vx_DT(opCode, pProgramCounter, V, pDelayTimer);
        delayTimer = V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF00A) {
        // LD_Vx_K(opCode, pProgramCounter, V, keyBoardState);
        int pressed = 0;
        for (int i = 0; i < 16; i++) {
          if (keyBoardState[i] == 1)
            V[x] = i;
            pressed = 1;
            i = 16;
        }

        if (pressed)
          PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF015) {
        // LD_DT_Vx(opCode, pProgramCounter, V, pDelayTimer);
        delayTimer = V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF018) {
        // LD_ST_Vx(opCode, pProgramCounter, V, pSoundTimer);
        soundTimer = V[x];
        PC += 2; 
      }
      
      else if ((opCode & 0xF0FF) == 0xF01E) {
        // ADD_I_Vx(opCode, pProgramCounter, V, pI);
        I = I + V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF029) {
        // LD_F_Vx(opCode, pProgramCounter, V, pI);
        I = V[x] * 5;
        printf("I -> to %03X\n", V[x]*5);
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF033) {
        // LD_B_Vx(opCode, pProgramCounter, V, pI, memory);
        memory[I] = V[x] / 100;
        memory[I+1] = (V[x] % 100) / 10;
        memory[I+2] = V[x] % 10;
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF055) {
        // LD_I_Vx(opCode, pProgramCounter, V, pI, memory);
        for(int i = 0; i < x; i++)
          memory[I+x] = V[x];
        PC += 2;
      }
      
      else if ((opCode & 0xF0FF) == 0xF065) {
        // LD_Vx_I(opCode, pProgramCounter, V, pI, memory);
        for(int i = 0; i < x; i++)
          V[x] = memory[I+x];
        PC += 2;
      }
      renderAll(renderer, screen);
      
      SDL_RenderPresent(renderer);

      updateTimers(&delayTimer, &soundTimer);

      // Read instructions at 60Hz
      SDL_Delay(6);

    }
  } else {
    // ERROR
    printf("Error ! \n");
  }
  
  // EXIT
  SDL_Quit();
  return 0;
}
