#include "stdafx.h"
#include "Slide.h"
#include <algorithm>


double CSlide::GetWidth() const
{
	double width = 0;
	for (auto &shape : m_shapes)
	{
		auto frame = shape->GetFrame();
		width = std::max(width, frame.left + frame.width);
	}
	return width;
}

double CSlide::GetHeight() const
{
	double height = 0;
	for (auto &shape : m_shapes)
	{
		auto frame = shape->GetFrame();
		height = std::max(height, frame.top + frame.height);
	}
	return height;
}

IShapePtr CSlide::GetShape(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::invalid_argument("Shapes index out of range");
	}
	return m_shapes.at(index);
}

void CSlide::AddShape(const IShapePtr & component, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(component);
	}
	else if (position >= m_shapes.size())
	{
		throw std::invalid_argument("Shape position out of range");
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, component);
	}
}

void CSlide::RemoveShape(const IShapePtr & component)
{
	for (auto i = m_shapes.begin(); i != m_shapes.end(); ++i)
	{
		if (*i == component)
		{
			m_shapes.erase(i);
		}
	}
}

size_t CSlide::ShapesCount() const
{
	return m_shapes.size();
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}

void CSlide::Draw(ICanvas & canvas)
{
	canvas.BeginFill(m_backgroundColor);
	canvas.EndFill();
	for (auto &shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
