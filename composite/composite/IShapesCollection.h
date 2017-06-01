#pragma once
#include "IShape.h"

class IShapesCollection
{
public:
	virtual ~IShapesCollection() = default;

	virtual IShapePtr GetShape(size_t index)const = 0;
	virtual void AddShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveShape(const IShapePtr &component) = 0;
	virtual size_t ShapesCount() const = 0;
};