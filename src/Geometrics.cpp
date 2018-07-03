#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <Geometrics.h>

// Calculates the distance between point a and b
float dist(Point a, Point b){
	return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2) + pow((a.z - b.z),2));
}

Point createPoint(float x,float y,float z){
	Point p;

	p.x = x;p.y = y;p.z = z;

	return p;
}

// create new vector from point a to b
Vector createVector(Point a, Point b){
		Vector v;

		v.x = b.x - a.x;
		v.y = b.y - a.y;
		v.z = b.z - a.z;

		v.size = dist(a,b);

		return v;
}

// Creates a new vector based on points a and b and normalizes it
Vector createNormalizedVector(Point a, Point b){
	Vector v = createVector(a,b);

	v.x /= v.size;
	v.y /= v.size;
	v.z /= v.size;

	v.size =1.0f;

	return v;
}
