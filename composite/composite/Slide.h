#pragma once
#include "Canvas.h"
#include "IShapesCollection.h"
#include <vector>

class CSlide : public IShapesCollection
{
public:
	double GetWidth()const;
	double GetHeight()const;

	IShapePtr GetShape(size_t index)const override;
	void AddShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(const IShapePtr &component) override;
	size_t ShapesCount() const override;

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);

	void Draw(ICanvas & canvas);

private:	
	RGBAColor m_backgroundColor;
	std::vector<IShapePtr> m_shapes;
	
};