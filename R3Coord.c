#include "R3Coord.h"

void initializeR3Coord(double x, double y, double z, R3Coord *p) {
	(*p).x = x;
	(*p).y = y;
	(*p).z = z;
}

double distanceBetweenTwoPoints(R3Coord p1, R3Coord p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

void printR3Coordinate(R3Coord p) {
	printf("(%lf, %lf, %lf)\n", p.x, p.y, p.z);
}