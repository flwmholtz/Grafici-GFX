#ifndef GRAFICI_GFX_PLOTTER_HEATMAP_H
#define GRAFICI_GFX_PLOTTER_HEATMAP_H

#include "../Grafici.h"
#include "../Plotter.h"

namespace Plotter
{

class Heatmap : public Base
{
  public:
	void plot(const Display &display, const DataSets::DataSet &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{

		Range<size_t> column_range{ 0, MAP_COLUMNS };
		Range<size_t> row_range{ 0, MAP_ROWS };
		Range<float> value_range{ static_cast<float>(data.length()), 0 };

		/* Auto range */
		if (HEATMAP_AUTORANGE)
		{
			for (size_t column = 0; column < MAP_COLUMNS; ++column)
			{
				for (size_t row = 0; row < MAP_ROWS; ++row)
				{
					Range<DataNorm> x{ static_cast<DataNorm>(column_range.normalize(column)), static_cast<DataNorm>(column_range.normalize(column + 1)) };
					Range<DataNorm> y{ static_cast<DataNorm>(row_range.normalize(row)), static_cast<DataNorm>(row_range.normalize(row + 1)) };
					value_range.update(process_cell(x, y, data));
				}
			}
		}
		else
		{
			value_range = { 0.0, 1.0 };
		}

		for (size_t column = 0; column < MAP_COLUMNS; ++column)
		{
			for (size_t row = 0; row < MAP_ROWS; ++row)
			{
				Range<DataNorm> x{ static_cast<DataNorm>(column_range.normalize(column)), static_cast<DataNorm>(column_range.normalize(column + 1)) };
				Range<DataNorm> y{ static_cast<DataNorm>(row_range.normalize(row)), static_cast<DataNorm>(row_range.normalize(row + 1)) };
				draw_block(display, boundary, colorMap, x, y, value_range.normalize(process_cell(x, y, data)));
			}
		}
	}

  protected:
	virtual float process_cell(Range<DataNorm> x, Range<DataNorm> y, const DataSets::DataSet &data) const
	{
		float cell_value = 0;
		for (auto it = data.begin(); it != data.end(); it++)
		{
			auto dataPoint = *it;
			float dx = pow(dataPoint.x() - x.mid(), 2);
			float dy = pow(dataPoint.y() - y.mid(), 2);
			float distance = sqrt(dx + dy);
			merge_distance(cell_value, distance);
		}
		return cell_value;
	}

	virtual void merge_distance(float &cell_value, float distance) const
	{
		cell_value = graficiMax<float>(cell_value, 0.5 / (distance + 0.5));
	}

	virtual void draw_block(const Display &display,
	                        const Boundary &boundary,
	                        const ColorMap &colorMap,
	                        Range<DataNorm> x,
	                        Range<DataNorm> y,
	                        DataNorm c) const
	{
		display.fillRect(boundary.project({ x.low(), y.low() }),
		                 boundary.project({ x.high(), y.low() }),
		                 boundary.project({ x.low(), y.high() }),
		                 boundary.project({ x.high(), y.high() }),
		                 colorMap.project(c));
	}
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_HEATMAP_H
