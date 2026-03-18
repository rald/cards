#include "card.h"


Card *Card_New(Canvas *canvas,int front,int back,int rank,int suit,int x,int y,int z,bool isFront) {
	Card *card=malloc(sizeof(*card));

	card->canvas=canvas;
	card->front=front;
	card->back=back;
	card->rank=rank;
	card->suit=suit;
	card->x=x;
	card->y=y;
	card->z=z;
	card->isFront=isFront;

	return card;
}

void Card_Free(Card *card) {
	free(card);
}

void Card_Draw(Card *card,byte *srf) {
	if(card->isFront) {
		Canvas_Draw(card->canvas,srf,card->x,card->y,card->front);
	} else {
		Canvas_Draw(card->canvas,srf,card->x,card->y,card->back);
	}
}
