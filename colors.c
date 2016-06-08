#include "colors.h"

void ColorPlusColor(Color *c, Color c1, Color c2) {
	(*c).red = (c1.red + c2.red > 255)? 255: c1.red + c2.red;
	(*c).green = (c1.green + c2.green > 255)? 255: c1.green + c2.green;
	(*c).blue = (c1.blue + c2.blue > 255)? 255: c1.blue + c2.blue;	
}

void ColorPerConstant(Color *res, Color col, double ct) {
	(*res).red = (col.red * ct > 255)? 255: col.red * ct;
	(*res).green = (col.green * ct > 255)? 255: col.green * ct;
	(*res).blue = (col.blue * ct > 255)? 255: col.blue * ct;	
}

void initializeColor(Color *c, unsigned char red, unsigned char green, unsigned char blue) {
	(*c).red = red;
	(*c).green = green;
	(*c).blue = blue;
}

void printColor(Color c) {
	printf("(%d %d %d)\n", c.red, c.green, c.blue);
}
