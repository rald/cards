#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT)

#define INPUT_STATUS_1 0x03DA
#define VRETRACE       0x08

void vsync(void);
void setMode(unsigned char mode);
void setPalette(byte idx,byte r,byte g,byte b);

void DrawPoint(byte *srf,int x,int y,int c);
void FillRect(byte *srf,int x,int y,int w,int h,int c);


#endif
