#include "vector.h"

void initializeVector(R3Coord p1, R3Coord p2, VECTOR *v) {
	(*v).i = p2.x - p1.x;
	(*v).j = p2.y - p1.y;
	(*v).k = p2.z - p1.z; 
}

double magnitude(VECTOR v) {
	return sqrt(v.i * v.i + v.j * v.j + v.k * v.k);
}

void crossProduct(VECTOR *vout, VECTOR v1, VECTOR v2) {
	(*vout).i = (v1.j * v2.k) - ( v2.j * v1.k);
	(*vout).j = -1 * ((v1.i * v2.k) - (v2.i * v1.k));
	(*vout).k = (v1.i * v2.j) - (v1.i * v2.j);
}

double dotProduct(VECTOR v1, VECTOR v2) {
	return (v1.i * v2.i) + (v1.j * v2.j) + (v1.k * v2.k);
}

double angleBetweenTwoVectors(VECTOR v1, VECTOR v2) {
	return acos(dotProduct(v1, v2) / (magnitude(v1) * magnitude(v2)));
}

void normalization(VECTOR *v) {
	double mg = magnitude(*v);
	(*v).i /= mg;
	(*v).j /= mg;
	(*v).k /= mg; 
}

void printVector(VECTOR v) {
	printf("(%lf, %lf, %lf)\n", v.i, v.j, v.k);
}