#include "types.h"
#include "graphics.h"
#include "canvas.h"
#include "mouse.h"
#include "card.h"

#include <stdbool.h>
#include <mem.h>

dword palette[] = {
	0x1A1C2CL,
	0x5D275DL,
	0xB13E53L,
	0xEF7D57L,
	0xFFCD75L,
	0xA7F070L,
	0x38B764L,
	0x257179L,
	0x29366FL,
	0x3B5DC9L,
	0x41A676L,
	0x73EFF7L,
	0xF4F4F4L,
	0x94B0C2L,
	0x566C86L,
	0x333C57L
};






extern byte *VGA;

void paletteInit() {
	int i;
	for(i=0;i<16;i++) {
		int r=(int)((palette[i] & 0xFF0000L) >> 16);
		int g=(int)((palette[i] & 0x00FF00L) >> 8);
		int b=(int)((palette[i] & 0x0000FFL));
		r=(int)((double)r/255*63);
		g=(int)((double)g/255*63);
		b=(int)((double)b/255*63);

		setPalette(i,r,g,b);
	}

	for(i=16;i<256;i++) {
		int r=(int)((palette[0] & 0xFF0000L) >> 16);
		int g=(int)((palette[0] & 0x00FF00L) >> 8);
		int b=(int)((palette[0] & 0x0000FFL));
		r=(int)((double)r/255*63);
		g=(int)((double)g/255*63);
		b=(int)((double)b/255*63);

		setPalette(i,r,g,b);
	}
}

int main(void) {
	bool quit=false;
	int key;
	byte *buf=calloc(SCREEN_SIZE,sizeof(*buf));
	Canvas *canvas=NULL;
	Card *deck[52];
	int ndeck=0;
	int i,j,k,l;
	int hand[3][13];
	int nhand[3];
	int f;
	Mouse *mouse=NULL;

	srand(time(NULL));

	canvas=Canvas_Load("cards/cards.cvs");

	for(i=0;i<52;i++) {
		deck[ndeck++]=Card_New(
				canvas, i, 52,
				i%13, i/13,
				(i%13)*(16+1)+1, (i/13)*(16+1)+1, i,
				rand()%2);
	}

	mouse=Mouse_New("mouse.cvs");
	Mouse_Init(&mouse->on,&mouse->nbuttons);

	setMode(0x13);
	paletteInit();

	while(!quit) {
		memset(buf,6,SCREEN_SIZE);

		for(i=0;i<16;i++) {
			FillRect(buf,i*16,SCREEN_HEIGHT-16,16,16,i);
		}

		for(i=0;i<52;i++) {
			Card_Draw(deck[i],buf);
		}

		Mouse_Update(mouse);
		Mouse_Draw(mouse,buf);

		if(kbhit()) {
			key=getch();
			if(key==0) key=getch()+256;
			if(key==27) quit=true;
		}

		vsync();
		memcpy(VGA,buf,SCREEN_SIZE);
	}

	setMode(0x03);

	return 0;
}


