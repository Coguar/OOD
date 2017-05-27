#include "stdafx.h"
#include "Slide.h"
#include <algorithm>


double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

IShapePtr CSlide::GetShapeAtIndex(size_t index)
{
	if (m_shapes.size() > index)
	{
		return m_shapes[index];
	}
	return nullptr;
}

void CSlide::InsertShape(const IShapePtr &shape, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(shape);
	}
	else if (position >= m_shapes.size())
	{
		throw std::invalid_argument("Shape position out of range");
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::invalid_argument("Shape index out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);

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
