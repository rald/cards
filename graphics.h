#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT)

#define INPUT_STATUS_1 0x03DA
#define VRETRACE       0x08

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

void vsync(void);
void setmode(unsigned char mode);
void setpalette(byte idx,byte r,byte g,byte b);

#endif
