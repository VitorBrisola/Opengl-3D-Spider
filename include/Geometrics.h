#ifndef _GEOMETRICS_H_
#define _GEOMETRICS_H_

using namespace std;

#define lines 1000

typedef struct {
	float x,y,z;
}Point;

typedef struct {
	Point c;
	float r;
}Circle;

typedef struct {
	float x,y,z;
	float size;
}Vector;

Vector createVector(Point , Point );

Vector createNormalizedVector(Point,Point);

float dist(Point, Point);

Point createPoint(float,float,float);

#endif