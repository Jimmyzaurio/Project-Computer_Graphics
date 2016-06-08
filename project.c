#include "project.h"

void getFacesVertex(LIST *vertexes, LIST *faces, char *fileName) {
	FILE *fp;
	int f[3];
	double v[3];
	char nused;
	char command[50];
	R3Coord r;

	sprintf(command, "cat %s | grep \"^v \">vertex.f", fileName);
	system(command);
	strcpy(command,"");
	sprintf(command, "cat %s | grep \"^f \">faces.f", fileName);
	system(command);

	fp = fopen("vertex.f", "r");
	while (!feof(fp)) {
		fscanf(fp, "%c %lf %lf %lf\n", &nused, &v[0], &v[1], &v[2]);
		initializeR3Coord(v[0], v[1], v[2], &r);
		append(vertexes, &r);
	}

	fp = fopen("faces.f", "r");	
	while (!feof(fp)) {
		fscanf(fp, "%c %d %d %d\n", &nused, &f[0], &f[1], &f[2]);
		append(faces, &f);
	}
}

void drawModelAngle(LIST ver, LIST faces, VECTOR camera, Color solidColor, unsigned char Raster[COLUMNS][ROWS][3], LIST lightL, Color ambientLight, int angle) {
	LIST vertexes, facesList, colorList;
	initializeList(&vertexes, sizeof(R3Coord));
	initializeList(&facesList, sizeof(int)*3);
	char PPMName[30];
	NODE *ptr;
	
	for (ptr = ver.head; ptr; ptr = ptr->next)
		append(&vertexes, ptr->data);
	
	for (ptr = faces.head ; ptr; ptr = ptr -> next)
		append(&facesList, ptr->data);

	Color faceColor;	
	int *b, j = 0;
	
	discardFaces(camera, vertexes, &facesList);
	colorList = getColorPerFace(facesList, vertexes, lightL, ambientLight, solidColor, 0.7, 0.8);
	listRotation(&vertexes, (180 * M_PI)/180, 1, 'z');
	listRotation(&vertexes, (angle * M_PI)/180, 1, 'y');
	listRotation(&vertexes, (20 * M_PI)/180, -1, 'x');
	
	listTranslation(&vertexes, 0, 0, 800); // We move the image 800 from the camera
	vertexes = listPerspectiveProjection(&vertexes, 600);

	for (ptr = facesList.head; ptr; ptr = ptr->next, j++) { 
		b = (int*)ptr->data;	

		Coord v1, v2, v3;
		v1 = *(Coord *)getData(vertexes, b[0]);
		v2 = *(Coord *)getData(vertexes, b[1]);
		v3 = *(Coord *)getData(vertexes, b[2]);
		
		faceColor = *(Color *)getData(colorList, j + 1);
		drawTriangle(v1, v2, v3, faceColor, Raster);
	}

	sprintf(PPMName, "out%d.ppm", angle);
	makeppm(Raster, PPMName);
	cleanRaster(Raster);
}

LIST getColorPerFace(LIST facesList, LIST vertexes, LIST lights, Color ambientLight, Color objectColor, double Kd, double Ka) {
	NODE *ptr;	
	LIST facesColor;	

	initializeList(&facesColor, sizeof(Color));
	
	for (ptr = facesList.head; ptr; ptr=ptr->next) {
		int *b;
		b = (int *)ptr->data; 
		R3Coord vertex1, vertex2, vertex3, aux;
		Color faceColor, colorRadialL, colorAmbientLight, prdct;

		initializeColor(&faceColor, 0, 0, 0);
		initializeColor(&colorRadialL, 0, 0, 0);
		initializeColor(&colorAmbientLight, 0, 0, 0);

		vertex1 = *(R3Coord *)getData(vertexes, b[0]);
		vertex2 = *(R3Coord *)getData(vertexes, b[1]);
		vertex3 = *(R3Coord *)getData(vertexes, b[2]);

		aux.x = (vertex1.x + vertex2.x + vertex3.x)/3; 
		aux.y = (vertex1.y + vertex2.y + vertex3.y)/3;
		aux.z = (vertex1.z + vertex2.z + vertex3.z)/3;
		
		NODE *ptr2;
		for (ptr2 = lights.head ; ptr2; ptr2 = ptr2 -> next) {
			Radial_light *auxRL;
			auxRL = (Radial_light*) ptr2 -> data;
			ColorPerConstant(&prdct, auxRL->lightColor, Kd * attFactor(auxRL->att, distanceBetweenTwoPoints(auxRL->position, aux)));
			ColorPlusColor(&colorRadialL, colorRadialL, prdct);
		}

		ColorPerConstant(&colorAmbientLight,ambientLight, Ka);
		ColorPlusColor(&faceColor, objectColor, colorAmbientLight);
		ColorPlusColor(&faceColor, faceColor, colorRadialL);
		append(&facesColor, &faceColor);
	}
	return facesColor;
}

void discardFaces(VECTOR camera, LIST vertexes, LIST *facesList) {
	NODE* ptr;
	LIST fl;

	initializeList(&fl, sizeof(int)*3);

	for (ptr = facesList -> head; ptr; ptr = ptr->next) {
		int *b;
		b = (int *)ptr->data;	
		VECTOR v1, v2, normal;
		R3Coord vertex1, vertex2, vertex3;
		
		vertex1 = *(R3Coord *)getData(vertexes, b[0]);
		vertex2 = *(R3Coord *)getData(vertexes, b[1]);
		vertex3 = *(R3Coord *)getData(vertexes, b[2]);
		
		initializeVector(vertex1, vertex2, &v1);
		initializeVector(vertex2, vertex3, &v2);
		crossProduct(&normal, v2, v1);
		
		double angle = angleBetweenTwoVectors(normal, camera) * 180 / M_PI;
		
		if (angle >= 90 && angle <= 270)
			append(&fl, ptr -> data);		
	}
	*facesList = fl;
}

LIST listPerspectiveProjection(LIST *vertexes, double d) {
	MATRIX translationMatrix, scalingMatrix;
	NODE *ptr;
	LIST pprList;

	translationMatrix = createTranslationHomogeneusMatrix(960, 840, 0); // We're going to translate the vertexes to the centre of the camera
	scalingMatrix = createScalingHomogeneusMatrix(9, 9, 0); //Now we increase the size of the image
	initializeList(&pprList, sizeof(Coord));
	
	for (ptr = vertexes->head ; ptr; ptr = ptr->next) {
		R3Coord* auxR3;
		MATRIX auxMatr;

		auxR3 = (R3Coord*)ptr->data;
		MATRIX perspectiveMatrix = createPerspectiveProjectionMatrix(d, auxR3->z);
		auxMatr = R3CoordinateToMatrix(*auxR3);
		auxMatr = multiplication(perspectiveMatrix, auxMatr);
		auxMatr = multiplication(scalingMatrix, auxMatr);
		auxMatr = multiplication(translationMatrix, auxMatr);
		Coord auxR2 = R2MatrixToCoordinates(auxMatr);
		
		append(&pprList, &auxR2);
	}
	initializeList(vertexes, sizeof(Coord));
	return pprList;
}

void listTranslation(LIST *vertexes, double tx, double ty, double tz) {
	MATRIX translationMatrix;
	NODE *ptr;

	translationMatrix = createTranslationHomogeneusMatrix(tx, ty, tz);

	for (ptr = vertexes->head ; ptr; ptr = ptr->next) {
		MATRIX auxMatr;
		R3Coord* aux;

		aux = (R3Coord*)ptr->data;
		auxMatr = R3CoordinateToMatrix(*aux);
		*aux = R3MatrixToCoordinates(multiplication(translationMatrix, auxMatr));
		ptr->data = (void*)aux;
	}
}

void listScaling(LIST *vertexes, double sx, double sy, double sz) {
	MATRIX scaleMatrix = createScalingHomogeneusMatrix(sx, sy, sz);
	NODE *ptr;

	for (ptr = vertexes->head ; ptr; ptr = ptr->next) {		
		R3Coord *aux = (R3Coord*)ptr->data;
		MATRIX auxMatr = R3CoordinateToMatrix(*aux);
		*aux =R3MatrixToCoordinates(multiplication(scaleMatrix, auxMatr));
		ptr->data = (void*)aux;
	}
}

void listRotation(LIST* vertexes, double angle, int clocWise, char axis) {
	MATRIX rotationMatrix = createRotationHomogeneusMatrix(angle, clocWise, axis);
	NODE *ptr;

	for (ptr = vertexes->head; ptr ; ptr = ptr-> next) {
		R3Coord *aux;
		aux = (R3Coord*)ptr -> data;
		MATRIX auxMatr = R3CoordinateToMatrix(*aux);
		*aux = R3MatrixToCoordinates(multiplication(rotationMatrix, auxMatr));
		ptr -> data = (void*)aux;
	}
}

void initializeRadialLight(R3Coord pos, Color c, Attenuation att, Radial_light *light) {
	light->position = pos;
	light->lightColor = c;
	light->att = att;	
}

LIST createRandomListRadialLight(int q) {
	srand(time(NULL));
	LIST lightList;
	initializeList(&lightList, sizeof(Radial_light));
	
	int x = 0;
	for (x = 0 ; x < q; x++) {
		Attenuation attF;
		R3Coord Lposition;
		Color ColorLight;
		Radial_light Lr1;

		initializeR3Coord(rand() % 10 - 10, rand() % 80, rand() % 10 - 10, &Lposition);
		initializeColor(&ColorLight, rand() % 255, rand() % 255, rand() % 255); 
		initializeAttenuationFactors(&attF, .007, .003, .0433);
		initializeRadialLight(Lposition, ColorLight, attF, &Lr1);
		append(&lightList, &Lr1);
	}
	return lightList;
}
