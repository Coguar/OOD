#pragma once

class CAbstractShape;

struct IShapeFactory
{
	virtual ~IShapeFactory() = default;
	virtual std::shared_ptr<CAbstractShape> CreateShape(std::string const& descriptionShape) = 0;
};