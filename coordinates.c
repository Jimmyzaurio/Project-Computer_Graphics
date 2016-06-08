#include "coordinates.h"

double getSlope(Coord p1, Coord p2) {
    return (p2.y - p1.y)/(double)(p2.x - p1.x);
}

int getOctant(double slp, int crescentX, int crescentY) {
    if((slp > 0 && slp < 1 && crescentX == 1 && crescentY == 1) || (slp == 1 && crescentX == 1 && crescentY == 1) || (slp == 0 && crescentX == 1 && crescentY == 2))
        return 1;
    else if((slp > 1 && slp < INFINITY && crescentX == 1 && crescentY == 1) || (slp == INFINITY && crescentX == 2 && crescentY == 1))
        return 2;
    else if((slp > -INFINITY && slp < -1 && crescentX == 0 && crescentY == 1) )
        return 3;
    else if((slp > -1 && slp < 0 && crescentX == 0 && crescentY == 1) || (slp == 0 && crescentX == 0 && crescentY == 2) || (slp == -1 && crescentX == 0 && crescentY == 1))
        return 4;
    else if((slp > 0 && slp < 1 && crescentX == 0 && crescentY == 0) || (slp == 1 && crescentX == 0 && crescentY == 0))
        return 5;
    else if((slp > 1 && slp < INFINITY && crescentX == 0 && crescentY == 0) || (slp == -1 && crescentX == 1 && crescentY == 0)|| (slp == -INFINITY && crescentX == 2 && crescentY == 0))
        return 6;
    else if(slp > -INFINITY && slp < -1 && crescentX == 1 && crescentY == 0)
        return 7;
    else if((slp > -1 && slp < 0 && crescentX == 1 && crescentY == 0) || (slp == -1 && crescentX == 1 && crescentY == 0))
        return 8;
    return 9;
}

int isCrescentX(Coord p1, Coord p2) {
    if(p2.x > p1.x)     return 1;
    if(p2.x < p1.x)     return 0;
    return 2;
}

int isCrescentY(Coord p1, Coord p2) {
    if(p2.y > p1.y)     return 1;
    if(p2.y < p1.y)     return 0;
    return 2;
}

void swapY(Coord *p1, Coord *p2) {
    p1->x = -p1->x;
    p2->x = -p2->x;
}

void swapX(Coord *p1, Coord *p2) {
    p1->y = -p1->y;
    p2->y = -p2->y;
}

void diagonalAxisReflection(Coord *p1, Coord *p2) {
    int aux = p1->x;
    p1->x = p1->y;
    p1->y = aux;
    aux = p2->x;
    p2->x = p2->y;
    p2->y = aux;
}

void printCoordinates(Coord p) {
    printf("(%d, %d)\n",p.x, p.y );
}

int maxY(Coord p1, Coord p2, Coord p3) {
	if(p1.y > p2.y && p1.y > p3.y)     return p1.y;
	if(p2.y > p1.y && p2.y > p3.y)     return p2.y;
    return p3.y;
}

int minY(Coord p1, Coord p2, Coord p3) {
    if(p1.y < p2.y && p1.y < p3.y)  return p1.y;
    if(p2.y < p1.y && p2.y < p3.y)  return p2.y;
    return p3.y;
}
