#include "graphics.h"
#include "canvas.h"

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

void InitPalette() {
	int i;
	for(i=0;i<16;i++) {
		int r=(int)((palette[i] & 0xFF0000L) >> 16);
		int g=(int)((palette[i] & 0x00FF00L) >> 8);
		int b=(int)((palette[i] & 0x0000FFL));
		r=(int)((double)r/255*63);
		g=(int)((double)g/255*63);
		b=(int)((double)b/255*63);

		SetPalette(i,r,g,b);
	}

	for(i=16;i<256;i++) {
		int r=(int)((palette[0] & 0xFF0000L) >> 16);
		int g=(int)((palette[0] & 0x00FF00L) >> 8);
		int b=(int)((palette[0] & 0x0000FFL));
		r=(int)((double)r/255*63);
		g=(int)((double)g/255*63);
		b=(int)((double)b/255*63);

		SetPalette(i,r,g,b);
	}
}

int main(void) {
	bool quit=false;
	int key;
	byte *buf=calloc(SCREEN_SIZE,sizeof(*buf));
	Canvas *canvas[52];
	int i,j;

	srand(time(NULL));

	canvas[ 0]=Canvas_Load("cards/ah.cvs");
	canvas[ 1]=Canvas_Load("cards/2h.cvs");
	canvas[ 2]=Canvas_Load("cards/3h.cvs");
	canvas[ 3]=Canvas_Load("cards/4h.cvs");
	canvas[ 4]=Canvas_Load("cards/5h.cvs");
	canvas[ 5]=Canvas_Load("cards/6h.cvs");
	canvas[ 6]=Canvas_Load("cards/7h.cvs");
	canvas[ 7]=Canvas_Load("cards/8h.cvs");
	canvas[ 8]=Canvas_Load("cards/9h.cvs");
	canvas[ 9]=Canvas_Load("cards/10h.cvs");
	canvas[10]=Canvas_Load("cards/jh.cvs");
	canvas[11]=Canvas_Load("cards/qh.cvs");
	canvas[12]=Canvas_Load("cards/kh.cvs");

	canvas[13]=Canvas_Load("cards/ad.cvs");
	canvas[14]=Canvas_Load("cards/2d.cvs");
	canvas[15]=Canvas_Load("cards/3d.cvs");
	canvas[16]=Canvas_Load("cards/4d.cvs");
	canvas[17]=Canvas_Load("cards/5d.cvs");
	canvas[18]=Canvas_Load("cards/6d.cvs");
	canvas[19]=Canvas_Load("cards/7d.cvs");
	canvas[20]=Canvas_Load("cards/8d.cvs");
	canvas[21]=Canvas_Load("cards/9d.cvs");
	canvas[22]=Canvas_Load("cards/10d.cvs");
	canvas[23]=Canvas_Load("cards/jd.cvs");
	canvas[24]=Canvas_Load("cards/qd.cvs");
	canvas[25]=Canvas_Load("cards/kd.cvs");

	canvas[26]=Canvas_Load("cards/ac.cvs");
	canvas[27]=Canvas_Load("cards/2c.cvs");
	canvas[28]=Canvas_Load("cards/3c.cvs");
	canvas[29]=Canvas_Load("cards/4c.cvs");
	canvas[30]=Canvas_Load("cards/5c.cvs");
	canvas[31]=Canvas_Load("cards/6c.cvs");
	canvas[32]=Canvas_Load("cards/7c.cvs");
	canvas[33]=Canvas_Load("cards/8c.cvs");
	canvas[34]=Canvas_Load("cards/9c.cvs");
	canvas[35]=Canvas_Load("cards/10c.cvs");
	canvas[36]=Canvas_Load("cards/jc.cvs");
	canvas[37]=Canvas_Load("cards/qc.cvs");
	canvas[38]=Canvas_Load("cards/kc.cvs");

	canvas[39]=Canvas_Load("cards/as.cvs");
	canvas[40]=Canvas_Load("cards/2s.cvs");
	canvas[41]=Canvas_Load("cards/3s.cvs");
	canvas[42]=Canvas_Load("cards/4s.cvs");
	canvas[43]=Canvas_Load("cards/5s.cvs");
	canvas[44]=Canvas_Load("cards/6s.cvs");
	canvas[45]=Canvas_Load("cards/7s.cvs");
	canvas[46]=Canvas_Load("cards/8s.cvs");
	canvas[47]=Canvas_Load("cards/9s.cvs");
	canvas[48]=Canvas_Load("cards/10s.cvs");
	canvas[49]=Canvas_Load("cards/js.cvs");
	canvas[50]=Canvas_Load("cards/qs.cvs");
	canvas[51]=Canvas_Load("cards/ks.cvs");

	SetMode(0x13);
	InitPalette();

	while(!quit) {
		memset(buf,6,SCREEN_SIZE);

		for(j=0;j<4;j++) {
			for(i=0;i<13;i++) {
				Canvas_Draw(canvas[j*13+i],buf,i*(16+1)+1,j*(16+1)+1);
			}
		}


		for(i=0;i<16;i++) {
			FillRect(buf,i*16,SCREEN_HEIGHT-16,16,16,i);
		}

		vsync();
		memcpy(VGA,buf,SCREEN_SIZE);

		if(kbhit()) {
			key=getch();
			if(key==0) key=getch()+256;
			if(key==27) quit=true;
		}

	}

	SetMode(0x03);

	Canvas_Free(canvas[0]);
	Canvas_Free(canvas[1]);

	return 0;
}
