#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include "Point.h"

typedef unsigned char uchar;

class Bitmap {
	uchar *img;
	int width, height;
  public:
	Bitmap(int w, int h):width(w), height(h){
		img = (unsigned char *)malloc(3*w*h);
		memset(img,0,3*w*h);
	}
	~Bitmap(){
		free(img);
	}
	void setPixel(int x, int y, uchar r, uchar g, uchar b){
		img[(x+width*y)*3+2] = r;
		img[(x+width*y)*3+1] = g;
		img[(x+width*y)*3+0] = b;
	}
	void drawLine(Point &p1, Point &p2, uchar r, uchar g, uchar b){
		double dx = (p2.x-p1.x);
		double dy = (p2.y-p1.y);
		double dist = std::sqrt(dx*dx+dy*dy);
		dx = dx/dist;
		dy = dy/dist;
		double x = (int)(p1.x)+50;
		double y = (int)(p1.y)+50;
		for(int i=0; i<dist; ++i){
			setPixel((int)x, (int)y, r,g,b);
			x += dx;
			y += dy;
		}
	}
	void saveAs(const char *str){
		FILE *f;
		int filesize = 54 + 3*width*height;  //w is your image width, h is image height, both int

		uchar bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
		uchar bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
		uchar bmppad[3] = {0,0,0};

		*(int*)(&bmpfileheader[2]) = filesize;
		*(int*)(&bmpinfoheader[4]) = width;
		*(int*)(&bmpinfoheader[8]) = height;
		
		f = fopen(str, "w");
		fwrite(bmpfileheader,1,14,f);
		fwrite(bmpinfoheader,1,40,f);
		for(int i=0; i<height; i++){
			fwrite(i*width*3+img,3, width, f);
			fwrite(bmppad,1,(4-(width*3)%4)%4,f);
		}

		fclose(f);
	}
};
