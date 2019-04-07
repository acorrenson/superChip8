#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "readRom.h"
#include "system.h"

int main(int argc, char const *argv[]) {
  
  // -- INIT CHIP8 SYSTEM -- 
  // memory of the system
  unsigned short memory[MEMORY_SIZE];
  // programCounter to the first readable memory location
  // the 512 first location are reserved by the system
  unsigned short * memoryPtr = memory + MEMORY_START;
  // programCounter to the current opCode
  unsigned short programCounter = 0;
  // Number of opCodes loaded
  unsigned short romSize = 0;
  // 16 8-bit registers
  unsigned char V[16];
  // adress register (void pointer)
  unsigned short I = 0;
  // stack for subroutines
  unsigned char stack[48];
  unsigned short stackPtr = 0;

  // timers
  unsigned short delayTimer = 0;
  unsigned short soundTimer = 0;

  unsigned char keyBoardState[16] =
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

  // -- INIT WINDOW --
  printf("Creating superChip8 window\n");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* pWindow = NULL;
  SDL_Renderer* renderer;

  pWindow = SDL_CreateWindow(
    "superChip8",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH + SQW,
    HEIGHT + SQH,
    SDL_WINDOW_SHOWN);

  // state of the keyboard
  const Uint8 *state;
  // current event
  SDL_Event e;
  // while the window is open
  int quit = 0;
  
  // -- MAIN PROGRAM --
  if ( pWindow ) {
    printf("Successfully created superChip8 window\n");

    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    dispAllChar(renderer, charTable);


    // ==== TEST ZONE ================================
    printf("--- READING THE ROM %s ---\n", argv[1]);
    romSize = readRom(memoryPtr, argv[1]);
    printf("rom size : %d\n", romSize);

    for(int i=0; i < romSize; i++) {
      desasembler(memoryPtr[i]);
    }

    SDL_RenderPresent(renderer);
    // ===============================================

    // LOOP
    while ( !quit ) {
      state = SDL_GetKeyboardState(NULL);
      while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) {
          quit = 1;
        }
      }

      setKeyBoardState(state, keyBoardState);

      // Read instructions at 60Hz
      SDL_Delay(FRAMES_PER_SECOND);
    }
  } else {
    // ERROR
    printf("Error ! \n");
  }
  
  // EXIT
  SDL_Quit();
  return 0;
}
