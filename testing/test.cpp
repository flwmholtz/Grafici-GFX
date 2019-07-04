#include "File_GFX.h"

#include "../visitors/VisitorDrawScatter.h"
#include "../visitors/VisitorDrawBar.h"
#include "../visitors/VisitorDrawLine.h"
#include "../visitors/VisitorDrawAxis.h"

#include "../dataset/DataSetFloat.h"
#include "../dataset/DecoratorDataSetSpline.h"
#include "../dataset/DecoratorDataSetHistogram.h"

#include "../colorschemes/ColorSchemeHeat.h"

#include "../Display.h"
#include "../Widget.h"

//todo make an h file to include all basic essentials
#include <iostream>

float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
float dataArrayY[11] = {0, 2, 2, 2, 2, 6, 5, 10, 10, 10, 9};

int main()
{
	//TODO create factory that takes in input just displayDriver, dataset (, style)

	DisplayDriver displayDriver;
	DataSetFloat dataset;
	DecoratorDataSetSpline dataSpline;
	DecoratorDataSetHistogram dataHist;
	VisitorDrawScatter visitorScatter;
	VisitorDrawBar visitorBar;
	VisitorDrawLine visitorLine;
	VisitorDrawAxis visitorAxis;
	Widget widget;
	RoundBoundaries circle;

	// displayDriver
	Adafruit_GFX *gfx = new File_GFX(640, 480, "prova.bmp");
	displayDriver.begin(gfx);

	// dataset
	dataset.begin(dataArrayY, dataArrayValue, 11);
	dataSpline.begin(&dataset, 100);
	dataHist.begin(&dataSpline, 20);

	//todo create a factory that get gfx + array (+plot style) and instantiate all objects

	// plotter
	visitorBar.begin(displayDriver, colorSchemeHeat);
	visitorLine.begin(displayDriver, colorSchemeHeat);
	visitorAxis.begin(displayDriver, colorSchemeHeat);
	visitorScatter.begin(displayDriver, colorSchemeHeat);

	widget.begin(dataSpline);
	//widget.begin(dataHist);

	circle.begin(displayDriver);
	// circle.beginAngle = M_PI;
	// circle.endAngle = 0; // this way is clockwise
	// circle.innerRadius = circle.outerRadius / 2;

	// plot action
	//widget.accept(&visitorAxis, displayDriver.fullScreen->applyBorder(50, 10, 10, 10));
	//widget.accept(&visitorBar, displayDriver.fullScreen->applyBorder(50, 10, 10, 10));
	//widget.accept(&visitorLine, displayDriver.fullScreen->applyBorder(50, 10, 10, 10));
	//widget.accept(&visitorScatter, displayDriver.fullScreen->applyBorder(50, 10, 10, 10));

	widget.accept(&visitorAxis, &circle);
	widget.accept(&visitorLine, &circle);
	widget.accept(&visitorBar, &circle);

	//flush to file
	((File_GFX *)gfx)->flush();

	return 0;
}