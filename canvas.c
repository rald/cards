#include "canvas.h"

void Canvas_Free(Canvas *canvas) {
	free(canvas->data);
	free(canvas);
}

Canvas *Canvas_Load(char *filename) {
	Canvas *canvas = malloc(sizeof(*canvas));
	FILE *fp;
	char *hex="0123456789ABCDEF";
	int i,j,k;
	int ch;

	if((fp=fopen(filename,"r"))==NULL) {
		printf("Error opening file %s\n",filename);
		free(canvas);
		canvas=NULL;
		return canvas;
	}

	fscanf(fp,"%d,%d,%d",&canvas->width,&canvas->height,&canvas->transparent);

	canvas->data=calloc(canvas->width*canvas->height,sizeof(*canvas->data));

	k=0;
	while((ch=fgetc(fp))!=EOF) {
		j=-1;
		for(i=0;i<16;i++) {
			if(ch==hex[i]) {
				j=i;
				break;
			}
		}
		if(j!=-1) {
			canvas->data[k++]=j;
		}
	}

	fclose(fp);

	return canvas;
}

int Canvas_Save(Canvas *canvas,char *filename) {
	FILE *fp;
	char *hex="0123456789ABCDEF";
	int i,j,k;

	if((fp=fopen(filename,"w"))==NULL) {
		printf("Error opening file %s",filename);
		return 1;
	}

	fprintf(fp,"%d,%d,%d\n\n",canvas->width,canvas->height,canvas->transparent);

	k=0;
	for(j=0;j<canvas->height;j++) {
		for(i=0;i<canvas->width;i++) {
			fputc(hex[canvas->data[k++]],fp);
		}
		fputc('\n',fp);
	}
	fputc('\n',fp);

	fclose(fp);

	return 0;
}

void Canvas_Draw(Canvas *canvas,byte *srf,int x,int y) {
	int i,j,k,l;
	for(j=0;j<canvas->height;j++) {
		for(i=0;i<canvas->width;i++) {
			k=j*canvas->width+i;
			l=canvas->data[k];
			if(l!=canvas->transparent) {
				DrawPoint(srf,x+i,y+j,l);
			}
		}
	}
}

