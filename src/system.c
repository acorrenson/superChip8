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
  rect.x = (x)*SQW;
  rect.y = (y)*SQH;
  rect.h = SQH;
  rect.w = SQW;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void erase(SDL_Renderer * renderer, int x, int y)
{
  // Draw a point to the screen
  SDL_Rect rect;
  rect.x = (x)*SQW;
  rect.y = (y)*SQH;
  rect.h = SQH;
  rect.w = SQW;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
}


/**
 * @brief      Redraw the screen
 *
 * @param      renderer  The sdl-renderer
 * @param      screen    The screen
 */
void renderAll(SDL_Renderer *renderer, unsigned char screen[32][64])
{
  for (int i = 0; i < 32; ++i)
  {
    for (int j = 0; j < 64; ++j)
    {
      if (screen[i][j] == 1)
        point(renderer, j, i);
      else
        erase(renderer, j, i);
    }
  }
}


/**
 * @brief      Display a sprite to the screen
 *
 * @param      screen  The screen
 * @param      buff    The buffer
 * @param[in]  size    The size
 * @param[in]  x       x position
 * @param[in]  y       y position
 *
 * @return     If there is a collision with an other sprite, return 1
 */
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

/**
 * @brief      Sets the key board state.
 *
 * @param[in]  state          The SDL keyboard state
 * @param      keyBoardState  The chip8 keyboard state
 */
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