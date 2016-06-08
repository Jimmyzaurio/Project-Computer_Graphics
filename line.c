#include "line.h"

void cleanRaster(unsigned char raster[COLUMNS][ROWS][3]) {
    unsigned int i, j = 0;
    Color c;
    initializeColor(&c, 0,0,0);
    Coord p;
    int red = 0;

    for (i = 0 ; i < ROWS ; i++) {
        p.y = i;
        for (j = 0 ; j < COLUMNS ; j++) {
            p.x = j;            
            red = red + 15;
            put_M_PIxel(raster, p, c);
        }
    }
}

bool put_M_PIxel(unsigned char raster[COLUMNS][ROWS][3], Coord p, Color c) {
    raster[p.x][p.y][0] = c.red;
    raster[p.x][p.y][1] = c.green;
    raster[p.x][p.y][2] = c.blue;
    return TRUE;
}

void makeppm(unsigned char raster[COLUMNS][ROWS][3], char *name) {
    int rows = ROWS;
    int cols = COLUMNS;
    unsigned int i, j = 0;
    FILE *archivo = fopen(name, "w");
    fprintf(archivo, "P3\n%d %d 255\n", cols, rows);

    for(i = 0; i < ROWS ; i++){
        for(j = 0; j< COLUMNS; j++)
            fprintf(archivo, " %d %d %d ", raster[j][i][0], raster[j][i][1], raster[j][i][2]);
        fprintf(archivo,"\n");
    }
}

LIST getTable(Coord *p1, Coord *p2, int algoritm){
    int octant = getOctant(getSlope(*p1, *p2), isCrescentX(*p1, *p2), isCrescentY(*p1, *p2));
    Coord ap1, ap2;
    ap1 = *p1;
    ap2 = *p2;
    LIST table; 

    switch(octant){
        case 1:
			table = SelectAlgorithm(ap1, ap2, algoritm);
			break;
        case 2:
			diagonalAxisReflection(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			diagonalAxisReflectionCoordinates(&table);
			diagonalAxisReflection(&ap1, &ap2);
			break;
        case 3:
			swapY(&ap1, &ap2);
			diagonalAxisReflection(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			diagonalAxisReflectionCoordinates(&table);
			swapYCoordinates(&table);
			swapY(&ap1, &ap2);
			diagonalAxisReflection(&ap1, &ap2);
			break;
        case 4:
			swapY(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			swapYCoordinates(&table);
			swapY(&ap1, &ap2);
			break;
        case 5:
			swapY(&ap1, &ap2);
			swapX(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			swapXCoordinates(&table);
			swapYCoordinates(&table);
			swapY(&ap1, &ap2);
			swapX(&ap1, &ap2);
			break;
        case 6:
			diagonalAxisReflection(&ap1, &ap2);
			swapX(&ap1, &ap2);
			swapY(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			swapYCoordinates(&table);
			swapXCoordinates(&table);
			diagonalAxisReflectionCoordinates(&table);
			diagonalAxisReflection(&ap1,&ap2);
			swapX(&ap1, &ap2);
			swapY(&ap1, &ap2);
			break;
        case 7:
			diagonalAxisReflection(&ap1, &ap2);
			swapY(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			swapYCoordinates(&table);
			diagonalAxisReflectionCoordinates(&table);
			diagonalAxisReflection(&ap1, &ap2);
			swapY(&ap1, &ap2);
			break;
        case 8:
			swapX(&ap1, &ap2);
			table = SelectAlgorithm(ap1, ap2, algoritm);
			swapXCoordinates(&table);
			swapX(&ap1, &ap2);
			break;
        case 9:
			initializeList(&table, sizeof(Coord));
			prepend(&table,&ap1);
			break;
    }
    return table;
}

LIST naiveAlgorithm(Coord p1, Coord p2) {
    int x = 0;
    int y = 0;
    float m = 0.0f;
    float b = 0.0f;
    LIST results;
    initializeList(&results, sizeof(Coord));
    Coord aux;
    m = getSlope(p1, p2);
    b = p2.y - m*p2.x;
    for (x = p1.x ; x <= p2.x; x++) {
        y = m*x+b;
        aux.x = x;
        aux.y = y;
        prepend(&results, &aux);
    }
    //printTable(results);
    return results;
}

LIST DDRAlgorithm(Coord p1, Coord p2) {
    int x, y;
    float m = getSlope(p1, p2);
    LIST results;
    initializeList(&results, sizeof(Coord));
    Coord aux;
    y = p1.y;
    for (x = p1.x ; x <= p2.x ; x++) {
        aux.x = x;
        aux.y = y;
        y += m;
        prepend(&results, &aux);
    }
    //printTable(results, sizeArray);
    return results;
}

LIST BresenhanAlgorithm(Coord p1, Coord p2) {
    int x, y;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int d = 2 * dy - dx;
    int incE = 2*dy;
    int incNe = 2*(dy - dx);
    LIST results;
    initializeList(&results, sizeof(Coord));
    Coord aux;
    for(x = p1.x, y = p1.y; x <= p2.x ; x++) {
        aux.x = x;
        aux.y = y;
        if (d <= 0) {
            d += incE;
        } else {
            d += incNe;
            y++;
        }
        prepend(&results, &aux);
    }
    return results;
}

LIST SelectAlgorithm(Coord p1, Coord p2, int algorithm) {
    switch(algorithm){
        case 1:
            return naiveAlgorithm(p1, p2);
            break;
        case 2:
            return DDRAlgorithm(p1, p2);
            break;
        case 3:
            return BresenhanAlgorithm(p1, p2);
            break;
    }
    LIST aux;
    initializeList(&aux, 0);
    return aux;
}

void diagonalAxisReflectionCoordinates(LIST *table) {
    Coord aux, *node;
    NODE* ptr = table -> head;

    for (ptr = table -> head;ptr; ptr = ptr -> next) {
        node =(Coord*) ptr->data;
        aux.x = node->x;
        node->x = node->y;
        node->y = aux.x;
        ptr->data = (void *)node;
    }
}

void swapXCoordinates(LIST* table) {
    NODE* ptr;
    Coord *node;
    for (ptr = table->head; ptr ; ptr = ptr->next) {
        node = (Coord*) ptr -> data;
        node-> y *= -1; 
        ptr->data = (void *)node;
    }   
}

void swapYCoordinates(LIST* table) {
    NODE* ptr;
    Coord *node;
    for(ptr = table -> head; ptr ; ptr = ptr->next){
        node = (Coord*) ptr -> data;
        node-> x *= -1;
        ptr->data = (void *)node;
    }
}

LIST drawLine(Coord p1, Coord p2, unsigned char Raster[COLUMNS][ROWS][3], Color c) {
	Coord *p;
	NODE* ptr;
	LIST table; 
	table = getTable(&p1, &p2, 3);
	for(ptr = table.head; ptr; ptr = ptr->next){
		p = (Coord *)ptr -> data;
		put_M_PIxel(Raster,*p, c);
	}
	return table;
}

void printTable(LIST l) {
	NODE *ptr;
	Coord *node;

	for (ptr = l . head ; ptr ; ptr = ptr ->next) {
		node = (Coord *)ptr -> data;
		printCoordinates(*node);
	}
}

void drawTriangle(Coord p1, Coord p2, Coord p3, Color c, unsigned char Raster[COLUMNS][ROWS][3]) {
	LIST l1, l2, l3;
	Color c0;
	initializeColor(&c0, 0, 0, 0);
	l1 = drawLine(p1, p2, Raster, c0);
	l2 = drawLine(p2, p3, Raster, c0);
	l3 = drawLine(p1, p3, Raster, c0);
	scanLine(maxY(p1, p2, p3), minY(p1, p2, p3), l1, l2, l3, c, Raster);
	drawLine(p1, p2, Raster, c0);
	drawLine(p2, p3, Raster, c0);
	drawLine(p1, p3, Raster, c0);
}

int findYinList(int y, LIST l, Coord *c) {
	NODE *ptr;
	Coord *node;
	for (ptr = l.head ; ptr ; ptr = ptr -> next) {
		node = (Coord *)ptr -> data;
		if (node->y == y) {
			*c = *node;
			return 1;
		}
	}
	return 0;    
}

void scanLine(int max, int min, LIST l1, LIST l2, LIST l3, Color c, unsigned char Raster[COLUMNS][ROWS][3]) {
	int y;
	Coord initial, final;

	for (y = max ; y >= min; y--) {
		if (findYinList(y, l1, &initial)) {
			if (findYinList(y, l2, &final))
				drawLine(initial, final, Raster, c);
			if (findYinList(y, l3, &final))
				drawLine(initial, final, Raster, c);
		} else if (findYinList(y, l2, &initial)) {
			if (findYinList(y, l1, &final))
				drawLine(initial, final, Raster, c);
			if (findYinList(y, l3, &final))
				drawLine(initial, final, Raster, c);
		} else if (findYinList(y, l3, &initial)) {
			if (findYinList(y, l1, &final))
				drawLine(initial, final, Raster, c);
			if (findYinList(y, l2, &final))
				drawLine(initial, final, Raster, c);
		}
	}
}
