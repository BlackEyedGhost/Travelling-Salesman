#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Dist.h"
#include "TriArray.h"
#include "Bitmap.h"

using namespace std;

const int ptCt = 999;

bool intersects(Point*,Point*,Point*,Point*);
void drawMap(Point*, const char[]);

int main(){
	
	Point points[ptCt];
	TriArray<Dist> dists(ptCt);
	for(int i=0; i<ptCt; ++i){
		for(int j=i+1; j<ptCt; ++j){
			dists(i,j) = new Dist(&points[i], &points[j]);
		}
	}
	
	sort(dists.items, dists.items+dists.length);
	Point *start = nullptr;
	for(int i=0; i<dists.length; ++i){
		Dist *d = &dists.items[i];
		Point *p1 = d->p1;
		Point *p2 = d->p2;
		if(p1->links<2 && p2->links<2 && p1->end != p2 && p2->end != p1){
			++(p1->links);
			++(p2->links);
			if(p1->end != nullptr){
				p1->lnk2 = p2;
				start = p1->end;
				if(p2->end != nullptr){
					p2->lnk2 = p1;
					p1->end->end = p2->end;
					p2->end->end = p1->end;
				} else {
					p2->lnk1 = p1;
					p2->end = p1->end;
					p1->end->end = p2;
				}
			} else {
				p1->lnk1 = p2;
				start = p1;
				if(p2->end != nullptr){
					p2->lnk2 = p1;
					p1->end = p2->end;
					p2->end->end = p1;
				} else {
					p2->lnk1 = p1;
					p1->end = p2;
					p2->end = p1;
				}
			}
		}
	}
	start->lnk2 = start->end;
	start->end->lnk2 = start;
	
	for(int i=0; i<ptCt; ++i){
		if(points[i].links == 1){
			cout << "endPt " << i << "\n";
		}
	}
	double total = 0;
	Point *cur = start;
	Point *prev = nullptr;
	do{
		if(cur->lnk1 == prev){
			prev = cur;
			cur = cur->lnk2;
		} else {
			prev = cur;
			cur = cur->lnk1;
		}
		Dist dist(cur, prev);
		
		total += dist.val;
	}while(cur != start);
	cout << "total dist: " << total;
	
	drawMap(start, "img.bmp");
	
	Point *iCur = start;
	Point *iPrev = nullptr;
	while(iCur != start || iPrev == nullptr){
		if(iCur->lnk1 == iPrev){
			iPrev = iCur;
			iCur = iCur->lnk2;
		} else {
			iPrev = iCur;
			iCur = iCur->lnk1;
		}
		Point *jCur = start->lnk1;
		Point *jPrev = start;
		do{
			if(jCur->lnk1 == jPrev){
				jPrev = jCur;
				jCur = jCur->lnk2;
			} else {
				jPrev = jCur;
				jCur = jCur->lnk1;
			}
			
			if(intersects(iPrev, iCur, jPrev, jCur)){
				// swap iCur and jPrev?
			}
			
		}while(jCur != start);
	}
	
	drawMap(start, "img2.bmp");
}

bool intersects(Point *a, Point *b, Point *c, Point *d){
	/*
	v1 = b-a;
	v2 = d-c;
	a+x*v1 = c+y*v2;
	if(0<x,y<1) return true;
	*/
	return false;
}

void drawMap(Point *start, const char name[]){
	Bitmap bmp(1280, 720);
	Point *cur = start;
	Point *prev = nullptr;
	do{
		if(cur->lnk1 == prev){
			prev = cur;
			cur = cur->lnk2;
		} else {
			prev = cur;
			cur = cur->lnk1;
		}
		bmp.drawLine(*prev, *cur, 0,255,255);
	}while(cur != start);
	bmp.saveAs(name);
}