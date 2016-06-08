#include "matrix.h"

void initializeMatrix(MATRIX *a, int rows, int cols) {
	int i;
	a->rows = rows;
	a->columns = cols;
	a->m = (double**) malloc(rows * sizeof(double*));
	for(i = 0 ; i < rows ;i++)
		a->m[i] = (double *) malloc (cols * sizeof(double));
}

void printMatrix(MATRIX a) {
	int i, j;
	printf("Rows = %d\nColumns = %d\n", a.rows, a.columns);
	for(i = 0 ; i < a.rows ; i++){
		for(j = 0; j < a.columns ; j++)
			printf(" %lf ", a.m[i][j]);
		printf("\n");
	}
}

MATRIX multiplication(MATRIX a, MATRIX b) {
	MATRIX r;
	int i, j, k;

	if (!(a.columns == b.rows)) {
		printf("ERROR: Matrix size are not correct\n");
		exit(-1);
	}
	initializeMatrix(&r, a.rows, b.columns);

	for (i = 0; i < r.rows ; i++)
		for (j = 0; j < r.columns; j++){
			r.m[i][j] = 0;
			for (k = 0; k < a.columns; k++)
				r.m[i][j] = r.m[i][j] + a.m[i][k] * b.m[k][j];
		}
	return r;
}

MATRIX createTranslationMatrix(double tx, double ty) {
	MATRIX translationMatrix;
	initializeMatrix(&translationMatrix, 3, 3);

	translationMatrix.m[0][0] = 1.0;
	translationMatrix.m[1][0] = 0.0;
	translationMatrix.m[2][0] = 0.0;

	translationMatrix.m[0][1] = 0.0;
	translationMatrix.m[1][1] = 1.0;
	translationMatrix.m[2][1] = 0.0;

	translationMatrix.m[0][2] = tx;
	translationMatrix.m[1][2] = ty;
	translationMatrix.m[2][2] = 1.0;	

	return translationMatrix;
}

MATRIX createScalingMatrix(double sx, double sy) {
	MATRIX scalingMatrix;
	initializeMatrix(&scalingMatrix, 3, 3);
	
	scalingMatrix.m[0][0] = sx;
	scalingMatrix.m[1][0] = 0;
	scalingMatrix.m[2][0] = 0;

	scalingMatrix.m[0][1] = 0;
	scalingMatrix.m[1][1] = sy;
	scalingMatrix.m[2][1] = 0;

	scalingMatrix.m[0][2] = 0;
	scalingMatrix.m[1][2] = 0;
	scalingMatrix.m[2][2] = 1;

	return scalingMatrix;
}

//Crea una matriz de rotacion
//3D HOMOGENEUS FORM
MATRIX createRotationMatrix(double angle, int clocWise) {
	MATRIX rotationMatrix;
	int s;
	initializeMatrix(&rotationMatrix, 3, 3);

	if (clocWise == 1)
		s = 1;
	else
		s = -1;

	rotationMatrix.m[0][0] = cos(angle);
	rotationMatrix.m[1][0] = s*sin(angle);
	rotationMatrix.m[2][0] = 0;

	rotationMatrix.m[0][1] = s*-sin(angle);
	rotationMatrix.m[1][1] = cos(angle);
	rotationMatrix.m[2][1] = 0;

	rotationMatrix.m[0][2] = 0;
	rotationMatrix.m[1][2] = 0;
	rotationMatrix.m[2][2] = 1;

	return rotationMatrix;
}

MATRIX createTranslationHomogeneusMatrix(double tx, double ty, double tz) {
	MATRIX translationMatrix;
	initializeMatrix(&translationMatrix, 4, 4);

	translationMatrix.m[0][0] = 1.0;
	translationMatrix.m[1][0] = 0.0;
	translationMatrix.m[2][0] = 0.0;
	translationMatrix.m[3][0] = 0.0;

	translationMatrix.m[0][1] = 0.0;
	translationMatrix.m[1][1] = 1.0;
	translationMatrix.m[2][1] = 0.0;
	translationMatrix.m[3][1] = 0.0;

	translationMatrix.m[0][2] = 0.0;
	translationMatrix.m[1][2] = 0.0;
	translationMatrix.m[2][2] = 1.0;
	translationMatrix.m[3][2] = 0.0;

	translationMatrix.m[0][3] = tx;
	translationMatrix.m[1][3] = ty;
	translationMatrix.m[2][3] = tz;
	translationMatrix.m[3][3] = 1.0;	

	return translationMatrix;	
}//Crea una matriz homogenea de traslacion

MATRIX createScalingHomogeneusMatrix(double sx, double sy, double sz) {
	MATRIX scalingMatrix;
	initializeMatrix(&scalingMatrix, 4, 4);
	
	scalingMatrix.m[0][0] = sx;
	scalingMatrix.m[1][0] = 0;
	scalingMatrix.m[2][0] = 0;
	scalingMatrix.m[3][0] = 0;

	scalingMatrix.m[0][1] = 0;
	scalingMatrix.m[1][1] = sy;
	scalingMatrix.m[2][1] = 0;
	scalingMatrix.m[3][1] = 0;

	scalingMatrix.m[0][2] = 0;
	scalingMatrix.m[1][2] = 0;
	scalingMatrix.m[2][2] = sz;
	scalingMatrix.m[3][2] = 0;

	scalingMatrix.m[0][3] = 0;
	scalingMatrix.m[1][3] = 0;
	scalingMatrix.m[2][3] = 0;
	scalingMatrix.m[3][3] = 1;

	return scalingMatrix;	
}//Crea una matriz homogenea de escalacion

MATRIX createRotationHomogeneusMatrix(double angle, int clocWise, char axis) {
	MATRIX rotationMatrix;
	int s;
	initializeMatrix(&rotationMatrix, 4, 4);

	if (clocWise == 1)
		s = 1;
	else
		s = -1;

	if (axis == 'x') {
		rotationMatrix.m[0][0] = 1;
		rotationMatrix.m[1][0] = 0;
		rotationMatrix.m[2][0] = 0;
		rotationMatrix.m[3][0] = 0;

		rotationMatrix.m[0][1] = 0;
		rotationMatrix.m[1][1] = cos(angle);
		rotationMatrix.m[2][1] = s*sin(angle);
		rotationMatrix.m[3][1] = 0;

		rotationMatrix.m[0][2] = 0;
		rotationMatrix.m[1][2] = s*-sin(angle);
		rotationMatrix.m[2][2] = cos(angle);
		rotationMatrix.m[3][2] = 0;

		rotationMatrix.m[0][3] = 0;
		rotationMatrix.m[1][3] = 0;
		rotationMatrix.m[2][3] = 0;
		rotationMatrix.m[3][3] = 1;
	}

	if (axis == 'y') {
		rotationMatrix.m[0][0] = cos(angle);
		rotationMatrix.m[1][0] = 0;
		rotationMatrix.m[2][0] = s*sin(angle);
		rotationMatrix.m[3][0] = 0;

		rotationMatrix.m[0][1] = 0;
		rotationMatrix.m[1][1] = 1;
		rotationMatrix.m[2][1] = 0;
		rotationMatrix.m[3][1] = 0;

		rotationMatrix.m[0][2] = s*-sin(angle);
		rotationMatrix.m[1][2] = 0;
		rotationMatrix.m[2][2] = cos(angle);
		rotationMatrix.m[3][2] = 0;

		rotationMatrix.m[0][3] = 0;
		rotationMatrix.m[1][3] = 0;
		rotationMatrix.m[2][3] = 0;
		rotationMatrix.m[3][3] = 1;
	}

	if (axis == 'z') {
		rotationMatrix.m[0][0] = cos(angle);
		rotationMatrix.m[1][0] = s*sin(angle);
		rotationMatrix.m[2][0] = 0;
		rotationMatrix.m[3][0] = 0;

		rotationMatrix.m[0][1] = s*-sin(angle);
		rotationMatrix.m[1][1] = cos(angle);
		rotationMatrix.m[2][1] = 0;
		rotationMatrix.m[3][1] = 0;

		rotationMatrix.m[0][2] = 0;
		rotationMatrix.m[1][2] = 0;
		rotationMatrix.m[2][2] = 1;
		rotationMatrix.m[3][2] = 0;

		rotationMatrix.m[0][3] = 0;
		rotationMatrix.m[1][3] = 0;
		rotationMatrix.m[2][3] = 0;
		rotationMatrix.m[3][3] = 1;
	}
	return rotationMatrix;
}//Crea una matriz homogenea de rotacion

//crea matriz de perspectiva
MATRIX createPerspectiveProjectionMatrix(double d, double z) {
	MATRIX perspectiveProjectionMatrix;
	initializeMatrix(&perspectiveProjectionMatrix, 4, 4);

	perspectiveProjectionMatrix.m[0][0] = d/z;
	perspectiveProjectionMatrix.m[1][0] = 0;
	perspectiveProjectionMatrix.m[2][0] = 0;
	perspectiveProjectionMatrix.m[3][0] = 0;

	perspectiveProjectionMatrix.m[0][1] = 0;
	perspectiveProjectionMatrix.m[1][1] = d/z;
	perspectiveProjectionMatrix.m[2][1] = 0;
	perspectiveProjectionMatrix.m[3][1] = 0;

	perspectiveProjectionMatrix.m[0][2] = 0;
	perspectiveProjectionMatrix.m[1][2] = 0;
	perspectiveProjectionMatrix.m[2][2] = 1;
	perspectiveProjectionMatrix.m[3][2] = 0;

	perspectiveProjectionMatrix.m[0][3] = 0;
	perspectiveProjectionMatrix.m[1][3] = 0;
	perspectiveProjectionMatrix.m[2][3] = 0;
	perspectiveProjectionMatrix.m[3][3] = 1;

	return perspectiveProjectionMatrix;

}

MATRIX R2CoordinateToMatrix(Coord p) {
	MATRIX m;
	initializeMatrix(&m, 3, 1);

	m.m[0][0] = p.x;
	m.m[1][0] = p.y;
	m.m[2][0] = 1;

	return m;
}

MATRIX R3CoordinateToMatrix(R3Coord p) {
	MATRIX m;
	initializeMatrix(&m, 4, 1);
	m.m[0][0] = p.x;
	m.m[1][0] = p.y;
	m.m[2][0] = p.z;
	m.m[3][0] = 1;

	return m;
}

Coord R2MatrixToCoordinates(MATRIX m) {
	Coord p;
	p.x = round(m.m[0][0]);
	p.y = round(m.m[1][0]);
	return p;
}

R3Coord R3MatrixToCoordinates(MATRIX m) {
	R3Coord p;
	p.x = round(m.m[0][0]);
	p.y = round(m.m[1][0]);
	p.z = round(m.m[2][0]);
	return p;
}
