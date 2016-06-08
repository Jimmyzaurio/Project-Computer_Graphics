#ifndef __LINE_H
#define __LINE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "colors.h"
#include "coordinates.h"

#define COLUMNS 1920
#define ROWS 1080

void cleanRaster (unsigned char raster[COLUMNS][ROWS][3]);
bool put_M_PIxel (unsigned char raster[COLUMNS][ROWS][3], Coord, Color);
void makeppm (unsigned char raster[COLUMNS][ROWS][3], char *);
LIST getTable (Coord *, Coord *, int);
LIST naiveAlgorithm (Coord, Coord);
LIST DDRAlgorithm (Coord, Coord);
LIST BresenhanAlgorithm (Coord, Coord);
LIST SelectAlgorithm (Coord, Coord, int);
void diagonalAxisReflectionCoordinates (LIST *);
void swapXCoordinates (LIST *);
void swapYCoordinates (LIST *);
LIST drawLine (Coord, Coord, unsigned char Raster[COLUMNS][ROWS][3], Color);
void printTable (LIST);
void drawTriangle (Coord, Coord, Coord, Color, unsigned char Raster[COLUMNS][ROWS][3]);
int findYinList (int, LIST, Coord *);
void scanLine (int, int, LIST, LIST, LIST, Color, unsigned char Raster[COLUMNS][ROWS][3]);

#endif