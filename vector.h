#ifndef __VECTOR_H
#define __VECTOR_H

#include "R3Coord.h"
#include <math.h>
#include <stdio.h>

typedef struct vector{
	double i;
	double j;
	double k;
}VECTOR;

void initializeVector(R3Coord, R3Coord, VECTOR*);
double magnitude(VECTOR);
void crossProduct(VECTOR*, VECTOR, VECTOR);
double dotProduct(VECTOR, VECTOR);
double angleBetweenTwoVectors(VECTOR, VECTOR);
void normalization(VECTOR*);
void printVector(VECTOR);

#endif