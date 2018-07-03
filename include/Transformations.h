#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

using namespace std;

#include <Geometrics.h>

Point translation(Point , Point);

Point rotate(Point, Point,float);

Point scale(Point, Point, float);

double getAngle(Point, Point, Point);

#endif