#include "vector.h"
#include "line.h"

typedef struct matrix{
	double **m;
	int rows;
	int columns;
}MATRIX;

void initializeMatrix(MATRIX *, int, int);
void printMatrix(MATRIX);
MATRIX multiplication(MATRIX, MATRIX);
MATRIX createTranslationMatrix(double, double);
MATRIX createScalingMatrix(double, double);
MATRIX createRotationMatrix(double, int);
//3D HOMOGENEUS FORM
MATRIX createTranslationHomogeneusMatrix(double, double, double);
MATRIX createScalingHomogeneusMatrix(double, double, double);
MATRIX createRotationHomogeneusMatrix(double, int, char);
MATRIX createPerspectiveProjectionMatrix(double, double);
MATRIX R2CoordinateToMatrix(Coord);
MATRIX R3CoordinateToMatrix(R3Coord);
Coord R2MatrixToCoordinates(MATRIX);
R3Coord R3MatrixToCoordinates(MATRIX);