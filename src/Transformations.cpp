#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Transformations.h>


// scalar product of two vectors
float dot2D(Point A, Point B){
	return (A.x)*(B.x) + (A.y)*(B.y);
}

// finding the angle between vectors A(a,b) and B(a,c)
double getAngle(Point a, Point b, Point c){
	Point A,B;

	// Use of vector scalar product to find the angle
	A.x = b.x - a.x;
	A.y = b.y - a.y;

	B.x = c.x - a.x;
	B.y = c.y - a.y;

	double angle = acos(dot2D(A,B)/(dist(b,a)*dist(c,a)));

	// direction checkout
	double nz = ((b.x-a.x)*(c.y-b.y)) - ((b.y-a.y)*(c.x-b.x));
	if(nz < 0.0f) angle = -angle;

	return angle;
}


// Translates point a with offsets of vector v
Point translation(Point a, Point v){
	Point b;
	b.x = a.x + v.x;
	b.y = a.y + v.y;
	return b;
}

Point scale(Point v, Point u, float s){
	v.x -= u.x;
	v.y -= u.y;

	v.x = v.x*s;
	v.y = v.y*s;
		
	v.x += u.x;
	v.y += u.y;
	
	return v;
}

// Makes the rotation of an axis formed by two dots, u and v
Point rotate(Point v, Point u, float angle){

	v.x -= u.x;
	v.y -= u.y;

	double xT = v.x;
	v.x = v.x*cos(angle) - v.y*sin(angle);
	v.y = xT*sin(angle) + v.y*cos(angle);
		
	v.x += u.x;
	v.y += u.y;
	
	return v;
}