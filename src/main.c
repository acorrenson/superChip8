#include <stdio.h>
#include <SDL2/SDL.h>
#include "readRom.h"

// SYSTEM SPECIFICATIONS
#define MEMORY_SIZE 4096

#define WIDTH 640
#define HEIGHT 320
#define SQW 10  // square width
#define SQH 10  // square height

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

int main() {

  printf("Creating superChip8 window\n");

  // INIT WINDOW
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* pWindow = NULL;
  SDL_Renderer* renderer;

  // INIT CHIP8 SYSTEM
  unsigned short memory[MEMORY_SIZE];

  pWindow = SDL_CreateWindow(
    "superChip8",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH + SQW,
    HEIGHT + SQH,
    SDL_WINDOW_SHOWN);


  // MAIN PROGRAM
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

    readRom(memory, "/Users/arthur/Downloads/chip8-master/roms/15puzzle.rom");

    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;

    // LOOP
    while ( !quit ) {
      while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) {
          // handling SDL_QUIT event
          quit = 1;
        }
        if ( e.type == SDL_KEYDOWN ) {
          // handling KEYDOWN event
          quit = 1;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          // handling MOUSECLICK event
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
