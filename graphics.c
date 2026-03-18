#include "graphics.h"

byte *VGA=(byte*)0xA0000000L;
word *myclock=(word*)0x0000046CL;

bool inrect(int x,int y,int rx,int ry,int rw,int rh) {
	if(x>=rx && x<=rx+rw && y>=ry && y<=ry+rh) {
		return true;
	}
	return false;
}

void vsync(void) {
	while(inp(INPUT_STATUS_1) & VRETRACE);
	while(!(inp(INPUT_STATUS_1) & VRETRACE));
}

void setMode(unsigned char mode) {
	union REGS regs;
	regs.h.ah=0x00;
	regs.h.al=mode;
	int86(0x10,&regs,&regs);
}

void setPalette(byte idx,byte r,byte g,byte b) {
	outp(0x03c8,idx);
	outp(0x03c9,r);
	outp(0x03c9,g);
	outp(0x03c9,b);
}

void DrawPoint(byte *srf,int x,int y,int c) {
	if(x>=0 && x<SCREEN_WIDTH && y>=0 && y<SCREEN_HEIGHT) {
		srf[SCREEN_WIDTH*y+x]=c;
	}
}

void FillRect(byte *srf,int x,int y,int w,int h,int c) {
	int i,j;
	for(j=0;j<h;j++) {
		for(i=0;i<w;i++) {
			DrawPoint(srf,i+x,j+y,c);
		}
	}
}
