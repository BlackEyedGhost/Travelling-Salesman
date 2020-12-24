#include "Point.h"
#include <stdlib.h>

Point::Point(){
	int rando = std::rand()*RAND_MAX+std::rand();
	if(rando<0) rando = -rando;
	x = (double)(rando%1180);
	y = (double)((rando/1180)%620);
}
Point::Point(double x, double y):x(x), y(y){
}