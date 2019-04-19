#ifndef ARDU_DATAVIS_WIDGET_H
#define ARDU_DATAVIS_WIDGET_H

#include "Display.h"
#include "Data.h"
#include "Geometry.h"

class Widget
{
  public:

	virtual void draw(Driver &driver, Data &data, Line boundaries);
	virtual void draw(Driver &driver, Data &data, Rectangle boundaries);
	virtual void draw(Driver &driver, Data &data, Circle boundaries);

};

#endif //ARDU_DATAVIS_WIDGET_H