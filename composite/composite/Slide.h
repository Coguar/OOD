#pragma once
#include "Canvas.h"
#include "IShape.h"
#include <vector>

class CSlide
{
public:
	double GetWidth()const;
	double GetHeight()const;

	size_t GetShapesCount()const;
	IShapePtr GetShapeAtIndex(size_t index);
	void InsertShape(const IShapePtr &shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);

	void Draw(ICanvas & canvas);

private:
	double m_width = 0;
	double m_height = 0;
	
	RGBAColor m_backgroundColor;
	std::vector<IShapePtr> m_shapes;
	
};