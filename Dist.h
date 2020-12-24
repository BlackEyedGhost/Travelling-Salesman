#include <cmath>
#include "Point.h"

class Dist{
  public:
	Point *p1, *p2;
	double val=0;
	Dist(Point *p1, Point *p2):p1(p1),p2(p2){
		(*this)();
	}
	Dist(){}
	Dist operator=(Dist* d){
		p1 = d->p1;
		p2 = d->p2;
		val = d->val;
		return *this;
	}
	bool operator<(Dist d){
		return val < d.val;
	}
	double operator()(){
		double dx = p2->x - p1->x;
		double dy = p2->y - p1->y;
		val = std::sqrt(dx*dx+dy*dy);
		return val;
	}
};