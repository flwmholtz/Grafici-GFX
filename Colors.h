#ifndef ARDU_DATAVIS_COLOR_H
#define ARDU_DATAVIS_COLOR_H

#include <math.h>

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class Gradient
{
	public:
	Gradient(int size, Color * colors);
	Color *colors;
	int size;
	Color getColor(float value);
};

const Color lineColor = {255, 255, 255};		 //white
const Color markerColor = {255, 0, 0}; //red
const Color fillColor = {127, 127, 127}; //gray
const Color bkgColor = {0, 0, 0};	//black

#endif //ARDU_DATAVIS_COLOR_H
