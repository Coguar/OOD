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
	return m_components.size();
}

IShapePtr CSlide::GetShapeAtIndex(size_t index)
{
	if (m_components.size() > index)
	{
		return m_components[index];
	}
	return nullptr;
}

void CSlide::InsertShape(const IShapePtr &shape, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_components.push_back(shape);
	}
	else if (position >= m_components.size())
	{
		throw std::invalid_argument("Shape position out of range");
	}
	else
	{
		m_components.insert(m_components.begin() + position, shape);
	}
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_components.size())
	{
		throw std::invalid_argument("Shape index out of range");
	}
	m_components.erase(m_components.begin() + index);

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
	for (auto &shape : m_components)
	{
		shape->Draw(canvas);
	}
}
