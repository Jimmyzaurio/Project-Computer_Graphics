#ifndef __R3COORDINATES_H
#define __R3COORDINATES_H
#include <stdio.h>
#include <math.h>
typedef struct R3Coord{
	double x;
	double y;
	double z;
}R3Coord;

void initializeR3Coord(double, double, double, R3Coord*);
double distanceBetweenTwoPoints(R3Coord, R3Coord);
void printR3Coordinate(R3Coord);

#endif