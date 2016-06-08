#include <stdio.h>

typedef struct color{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}Color;

void ColorPlusColor(Color*, Color, Color);
void ColorPerConstant(Color*, Color, double);
void initializeColor(Color*, unsigned char, unsigned char, unsigned char);
void printColor(Color);