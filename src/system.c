#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "system.h"

void clearScreen(SDL_Renderer * renderer, unsigned char screen[32][64])
{
  for (int i = 0; i < 32; i++)
  {
    for (int j = 0; j < 64; j++)
    {
      screen[i][j] = 0;
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}



/**
 * @brief      Draw a point to the screen
 *
 * @param      renderer  The renderer
 * @param[in]  x         X Position
 * @param[in]  y         Y Position
 */
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

void erase(SDL_Renderer * renderer, int x, int y)
{
  // Draw a point to the screen
  SDL_Rect rect;
  rect.x = (x+1)*SQW;
  rect.y = (y+1)*SQH;
  rect.h = SQH;
  rect.w = SQW;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
}


void renderAll(SDL_Renderer *renderer, unsigned char screen[32][64])
{
  for (int i = 0; i < 32; ++i)
  {
    for (int j = 0; j < 64; ++j)
    {
      if (screen[i][j] == 1)
        point(renderer, j+1, i+1);
      else
        erase(renderer, j+1, i+1);
    }
  }
}


/**
 * @brief      Display a character to the screen
 *
 * @param      renderer  The renderer
 * @param      table     The character table
 * @param[in]  c         The number of the character to display (between 0 and 15)
 * @param[in]  x         X position
 * @param[in]  y         Y position
 */
void disp(SDL_Renderer * renderer, unsigned char table[16][5], int c, int x, int y)
{
  unsigned char code;
  unsigned char test;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      code = table[c][i] >> 4;
      test = (unsigned char) pow(2, j);
      if ( (code & test) ==  test )
        point(renderer, 1 + 4 - j + x, 1 + i + y);
    }
  }
}

/**
 * @brief      Display all possible characters to the screen
 *
 * @param      renderer  The renderer
 * @param      table     The characters table
 */
void dispAllChar(SDL_Renderer * renderer, unsigned char table[16][5])
{
  for (int i = 0; i < 16; i++) {
    disp(renderer, table, i, (i%4)*5, (i/4)*6);
  }
}

/**
 * @brief      Update all the timers of the chip8 system
 *
 * @param      delayTimer  The delay timer
 * @param      soundTimer  The sound timer
 */
void updateTimers(unsigned short * delayTimer, unsigned short * soundTimer)
{
  if (*delayTimer > 0)
    --*delayTimer;

  if (*soundTimer > 0)
    --*soundTimer;
}

void setKeyBoardState(const Uint8 * state, int keyBoardState[16])
{
  keyBoardState[1] = state[SDL_SCANCODE_1];
  keyBoardState[2] = state[SDL_SCANCODE_2];
  keyBoardState[3] = state[SDL_SCANCODE_3];

  keyBoardState[12] = state[SDL_SCANCODE_4];
  keyBoardState[13] = state[SDL_SCANCODE_R];
  keyBoardState[14] = state[SDL_SCANCODE_F];
  keyBoardState[15] = state[SDL_SCANCODE_V];

  keyBoardState[7] = state[SDL_SCANCODE_A];
  keyBoardState[8] = state[SDL_SCANCODE_S];
  keyBoardState[9] = state[SDL_SCANCODE_D];

  keyBoardState[10] = state[SDL_SCANCODE_Z];
  keyBoardState[0] = state[SDL_SCANCODE_X];
  keyBoardState[11] = state[SDL_SCANCODE_C];


  keyBoardState[4] = state[SDL_SCANCODE_Q];
  keyBoardState[5] = state[SDL_SCANCODE_W];
  keyBoardState[6] = state[SDL_SCANCODE_E];
}