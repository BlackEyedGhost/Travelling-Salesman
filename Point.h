#ifndef POINT_H
#define POINT_H

class Point{
  public:
	double x, y;
	int links=0;
	Point *lnk1=nullptr, *lnk2=nullptr, *end=nullptr;
	Point();
	Point(double, double);
};

#endif