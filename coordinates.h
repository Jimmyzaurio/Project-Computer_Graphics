#include <math.h>
#include <stdio.h>
#ifdef NAN
/* NAN is supported */
#endif

#ifdef INFINITY
/* INFINITY is supported */
#endif

typedef struct Coord{
	int x;
	int y;
}Coord;

double getSlope(Coord, Coord);
int getOctant(double, int, int);
int isCrescentX(Coord, Coord);
int isCrescentY(Coord, Coord);
void swapY(Coord*, Coord*);
void swapX(Coord*, Coord*);
void diagonalAxisReflection(Coord*, Coord*);
void printCoordinates(Coord);
int maxY(Coord, Coord, Coord);
int minY(Coord, Coord, Coord);
