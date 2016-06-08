#ifndef __PROJECT_H
#define __PROJECT_H

#include "matrix.h"
#include "attenuation.h"
#include <string.h>
#include <time.h>

typedef struct radialLight {
	R3Coord position;
	Color lightColor;
	Attenuation att;

}Radial_light;

void initializeRadialLight(R3Coord, Color, Attenuation, Radial_light*);
void getFacesVertex(LIST*, LIST*, char*);
void discardFaces(VECTOR, LIST, LIST *);
void listTranslation(LIST *, double, double, double);
void listScaling(LIST *, double, double, double);
void listRotation(LIST*, double, int, char);
void drawModelAngle(LIST, LIST, VECTOR, Color, unsigned char Raster[COLUMNS][ROWS][3], LIST, Color, int);
LIST listPerspectiveProjection(LIST *, double);
LIST getColorPerFace(LIST, LIST, LIST, Color, Color, double, double);
LIST createRandomListRadialLight(int);

#endif