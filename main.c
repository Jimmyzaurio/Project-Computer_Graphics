#include "project.h"

unsigned char Raster[COLUMNS][ROWS][3];
int main() {
	Color c1;
	Color ambientLight;
	LIST lightList;
	LIST vertexes, faces;

	initializeList(&vertexes, sizeof(R3Coord));
	initializeList(&faces, sizeof(int)*3);

	lightList = createRandomListRadialLight(6);	
	initializeColor(&ambientLight, rand() % 255, rand() % 255, rand() % 255);
	initializeColor(&c1, rand() % 50, rand() % 50, rand() % 50);
	
	cleanRaster(Raster);

	VECTOR c;
	c.i = 0;
	c.j = 0;
	c.k = 1;	
	getFacesVertex(&vertexes, &faces, "Charmander.obj"); /* We set the vertexes and faces information on the lists*/
	//getFacesVertex(&vertexes, &faces, "cubos.obj"); /* We set the vertexes and faces information on the lists*/
	
	int i;	
	for (i = 1200 ; i < 1360; i++)
		drawModelAngle(vertexes, faces, c, c1,Raster, lightList, ambientLight, i);
	printf("\nReady!\n");

	char command[50];
	sprintf(command, "convert -delay 5 -loop 0 *.ppm animation.gif");
	system(command);
}
