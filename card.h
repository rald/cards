#ifndef CARD_H
#define CARD_H

#include "types.h"
#include "canvas.h"
#include "mouse.h"

#include <stdbool.h>

typedef struct {
	Canvas *canvas;
	int front,back;
	word x,y,z;
	bool isFront;
	int rank;
	int suit;
} Card;

Card *Card_New(Canvas *canvas,int front,int back,int rank,int suit,int x,int y,int z,bool isFront);
void Card_Free(Card *card);
void Card_Draw(Card *card,byte *srf);

#endif
