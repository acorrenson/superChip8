#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "readRom.h"

// SYSTEM SPECIFICATIONS
#define MEMORY_SIZE 4096
#define MEMORY_START 512

#define WIDTH 640
#define HEIGHT 320
#define SQW 10  // square width
#define SQH 10  // square height
#define FRAMES_PER_SECOND 60

void point(SDL_Renderer * renderer, int x, int y)
{
  // Draw a point to the screen
  SDL_Rect rect;
  rect.x = (x+1)*SQW;
  rect.y = (y+1)*SQH;
  rect.h = SQH;
  rect.w = SQW;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

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

  
  // -- MAIN PROGRAM --
  if ( pWindow ) {
    printf("Successfully created superChip8 window\n");

    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw a 0 to the screen
    point(renderer, 0, 0);
    point(renderer, 0, 1);
    point(renderer, 0, 2);
    point(renderer, 0, 3);

    point(renderer, 1, 0);
    point(renderer, 1, 3);

    point(renderer, 2, 0);
    point(renderer, 2, 1);
    point(renderer, 2, 2);
    point(renderer, 2, 3);

    printf("--- READING THE ROM %s ---\n", argv[1]);
    romSize = readRom(memoryPtr, argv[1]);
    // printMemory(memoryPtr, romSize);
    printf("rom size : %d\n", romSize);

    // for(int i=0; i < romSize; i++)
      // desasembler(memoryPtr[i]);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;

    // LOOP
    while ( !quit ) {
      while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) {
          quit = 1;
        }
        if ( e.type == SDL_KEYDOWN ) {
          quit = 1;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          quit = 1;
        }
      }
    }
  } else {
    // ERROR
    printf("Error ! \n");
  }
  
  // EXIT
  SDL_Quit();
  return 0;
}
