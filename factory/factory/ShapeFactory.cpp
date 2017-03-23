#include "stdafx.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "ShapeFactory.h"
#include <sstream>


CShapeFactory::CShapeFactory()
{
}


CShapeFactory::~CShapeFactory()
{
}

std::shared_ptr<CAbstractShape> CShapeFactory::CreateShape(std::string const & descriptionShape)
{
	std::string type;
	std::stringstream descr(descriptionShape);
	descr >> type;

	if (type == "Rectangle")
	{
		return CreateRectangle(descr);
	}
	else if (type == "Ellipse")
	{
		return CreateEllipse(descr);
	}
	else if (type == "Triangle")
	{
		return CreateTriangle(descr);
	}
	else
	{
		throw std::invalid_argument("Unknown type");
	}
	return std::shared_ptr<CAbstractShape>();
}

Color CShapeFactory::GetColor(std::string const & color)
{
	auto element = COLOR_LIST.find(color);
	if (element == COLOR_LIST.end())
	{
		return Color::Black;
	}
	else
	{
		return element->second;
	}
}

std::shared_ptr<CAbstractShape> CShapeFactory::CreateRectangle(std::istream & descr)
{
	Vec2 position(-1.0, -1.0);
	Vec2 size(-1.0, -1.0);
	std::string color;
	descr >> color;
	descr >> position.x >> position.y >> size.x >> size.y;
	if (position.x < 0 || position.y < 0 || size.x < 0 || size.y < 0)
	{
		throw std::invalid_argument("Unclear data");
	}
	auto shape = std::make_shared<CRectangle>(position, size);
	shape->SetColor(GetColor(color));
	return shape;
}

std::shared_ptr<CAbstractShape> CShapeFactory::CreateEllipse(std::istream & descr)
{
	
	Vec2 center(-1.0, -1.0);
	Vec2 radius(-1.0, -1.0);
	std::string color;
	descr >> color;
	descr >> center.x >> center.y >> radius.x >> radius.y;
	if (center.x < 0 || center.y < 0 || radius.x < 0 || radius.y < 0)
	{
		throw std::invalid_argument("Unclear data");
	}
	auto shape = std::make_shared<CEllipse>(center, radius);
	shape->SetColor(GetColor(color));
	return shape;
}

std::shared_ptr<CAbstractShape> CShapeFactory::CreateTriangle(std::istream & descr)
{
	Vec2 v1(-1.0, -1.0);
	Vec2 v2(-1.0, -1.0);
	Vec2 v3(-1.0, -1.0);
	std::string color;

	descr >> color;
	descr >> v1.x >> v1.y >> v2.x >> v2.y >> v3.x >> v3.y;
	if (v1.x < 0 || v1.y < 0 || v2.x < 0 || v2.y < 0 || v3.x < 0 || v3.y < 0)
	{
		throw std::invalid_argument("Unclear data");
	}
	auto shape = std::make_shared<CTriangle>(v1, v2, v3);
	shape->SetColor(GetColor(color));
	return shape;
}
