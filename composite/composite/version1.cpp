#include "stdafx.h"
#include "version1.h"
#include <algorithm>

namespace version1
{

CStyle::CStyle()
	: m_isEnable(false)
	, m_color(0)
{
}

bool CStyle::IsEnabled() const
{
	return m_isEnable;
}

void CStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

RGBAColor CStyle::GetColor() const
{
	return m_color;
}

void CStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

RectD CShape::GetFrame()
{
	return m_frame;
}

void CShape::SetFrame(const RectD & rect)
{
	m_frame = rect;
}

CStyle CShape::GetLineStyle() const
{
	return m_lineStyle;
}

void CShape::SetLineStyle(const CStyle & style)
{
	m_lineStyle = style;
}

CStyle CShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CShape::SetFillStyle(const CStyle & style)
{
	m_fillStyle = style;
}

CRectangle::CRectangle(const RectD & rect)
{
	SetFrame(rect);
}

void CRectangle::Draw(ICanvas & canvas)
{
	auto fillStyle = GetFillStyle();
	auto lineStyle = GetLineStyle();

	if (fillStyle.IsEnabled())
	{
		canvas.BeginFill(fillStyle.GetColor());
	}
	if (lineStyle.IsEnabled())
	{
		canvas.SetLineColor(lineStyle.GetColor());
	}
	auto rect = GetFrame();

	canvas.MoveTo(rect.left, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top);

	if (fillStyle.IsEnabled())
	{
		canvas.EndFill();
	}
}

CEllipse::CEllipse(const RectD & rect)
{
	SetFrame(rect);
}

void CEllipse::Draw(ICanvas & canvas)
{
	auto fillStyle = GetFillStyle();
	auto lineStyle = GetLineStyle();

	if (fillStyle.IsEnabled())
	{
		canvas.BeginFill(fillStyle.GetColor());
	}
	if (lineStyle.IsEnabled())
	{
		canvas.SetLineColor(lineStyle.GetColor());
	}
	auto rect = GetFrame();

	canvas.DrawEllipse(rect.left, rect.top, rect.width, rect.height);

	if (fillStyle.IsEnabled())
	{
		canvas.EndFill();
	}
}


CTriangle::CTriangle(const RectD & rect)
{
	SetFrame(rect);
}

void CTriangle::Draw(ICanvas & canvas)
{
	auto fillStyle = GetFillStyle();
	auto lineStyle = GetLineStyle();

	if (fillStyle.IsEnabled())
	{
		canvas.BeginFill(fillStyle.GetColor());
	}
	if (lineStyle.IsEnabled())
	{
		canvas.SetLineColor(lineStyle.GetColor());
	}
	auto rect = GetFrame();

	canvas.MoveTo(rect.left + rect.width / 2.0, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top + rect.height);
	canvas.LineTo(rect.left + rect.width / 2.0, rect.top);

	if (fillStyle.IsEnabled())
	{
		canvas.EndFill();
	}
}

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

std::shared_ptr<CShape> CSlide::GetShapeAtIndex(size_t index)
{
	try
	{
		return m_shapes[index];
	}
	catch (...)
	{

	}
	return nullptr;
}

void CSlide::InsertShape(const std::shared_ptr<CShape>& shape, size_t position)
{
	if (position >= m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index < m_shapes.size())
	{
		m_shapes.erase(m_shapes.begin() + index);
	}
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

void CSlide::UpdateFrame()
{
	if (m_shapes.empty())
	{
		return;
	}
	double rightBottomX = 0;
	double rightBottomY = 0;

	std::for_each(m_shapes.begin(), m_shapes.end(), [&](std::shared_ptr<CShape> const& shape) {
		auto frame = shape->GetFrame();
		rightBottomX = std::max(rightBottomX, frame.left + frame.width);
		rightBottomY = std::max(rightBottomY, frame.top + frame.height);
	});

	m_width = rightBottomX;
	m_height = rightBottomY;
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<CShape> CGroup::GetShapeAtIndex(size_t index)
{
	try
	{
		return m_shapes[index];
	}
	catch (...)
	{

	}
	return nullptr;
}

void CGroup::InsertShape(const std::shared_ptr<CShape>& shape, size_t position)
{
	if (position >= m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
	UpdateFrame();
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	if (index < m_shapes.size())
	{
		m_shapes.erase(m_shapes.begin() + index);
		UpdateFrame();
	}
}

void CGroup::Draw(ICanvas & canvas)
{
	for (auto &shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CGroup::UpdateFrame()
{
	if (m_shapes.empty())
	{
		return;
	}
	double topLeftX = m_shapes.at(0)->GetFrame().left;
	double topLeftY = m_shapes.at(0)->GetFrame().top;
	double rightBottomX = 0;
	double rightBottomY = 0;

	std::for_each(m_shapes.begin(), m_shapes.end(), [&](std::shared_ptr<CShape> const& shape) {
		auto frame = shape->GetFrame();
		topLeftX = std::min(topLeftX, frame.left);
		topLeftY = std::min(topLeftY, frame.top);
		rightBottomX = std::max(rightBottomX, frame.left + frame.width);
		rightBottomY = std::max(rightBottomY, frame.top + frame.height);
	});

	SetFrame({ topLeftX ,topLeftY ,rightBottomX ,rightBottomY });
}

}