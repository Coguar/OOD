#pragma once
#include "ShapeFactoryInterface.h"

class CShapeFactory :
	public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory();

	std::shared_ptr<CAbstractShape> CreateShape(std::string const& descriptionShape) override;

private:
	Color GetColor(std::string const& color);

	std::shared_ptr<CAbstractShape> CreateRectangle(std::istream & descr);
	std::shared_ptr<CAbstractShape> CreateEllipse(std::istream & descr);
	std::shared_ptr<CAbstractShape> CreateTriangle(std::istream & descr);
};

