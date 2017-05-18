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

RectD Component::GetFrame() const
{
	return m_frame;
}

void Component::SetFrame(const RectD & rect)
{
	m_frame = rect;
}

StyleVariant Component::GetLineStyle() const
{
	return m_lineStyle;
}

void Component::SetLineStyle(const CStyle & style)
{
	m_lineStyle = style;
}

StyleVariant Component::GetFillStyle() const
{
	return m_fillStyle;
}

void Component::SetFillStyle(const CStyle & style)
{
	m_fillStyle = style;
}

CRectangle::CRectangle(const RectD & rect)
{
	SetFrame(rect);
}

void CRectangle::Draw(ICanvas & canvas)
{
	auto fillStyle = boost::get<CStyle>(&GetFillStyle());
	auto lineStyle = boost::get<CStyle>(&GetLineStyle());

	if (fillStyle && fillStyle->IsEnabled())
	{
		canvas.BeginFill(fillStyle->GetColor());
	}
	if (lineStyle && lineStyle->IsEnabled())
	{
		canvas.SetLineColor(lineStyle->GetColor());
	}
	auto rect = GetFrame();

	canvas.MoveTo(rect.left, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top);

	if (fillStyle && fillStyle->IsEnabled())
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
	auto fillStyle = boost::get<CStyle>(&GetFillStyle());
	auto lineStyle = boost::get<CStyle>(&GetLineStyle());

	if (fillStyle && fillStyle->IsEnabled())
	{
		canvas.BeginFill(fillStyle->GetColor());
	}
	if (lineStyle && lineStyle->IsEnabled())
	{
		canvas.SetLineColor(lineStyle->GetColor());
	}
	auto rect = GetFrame();

	canvas.DrawEllipse(rect.left, rect.top, rect.width, rect.height);

	if (fillStyle && fillStyle->IsEnabled())
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
	auto fillStyle = boost::get<CStyle>(&GetFillStyle());
	auto lineStyle = boost::get<CStyle>(&GetLineStyle());

	if (fillStyle && fillStyle->IsEnabled())
	{
		canvas.BeginFill(fillStyle->GetColor());
	}
	if (lineStyle && lineStyle->IsEnabled())
	{
		canvas.SetLineColor(lineStyle->GetColor());
	}
	auto rect = GetFrame();

	canvas.MoveTo(rect.left + rect.width / 2.0, rect.top);
	canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
	canvas.LineTo(rect.left, rect.top + rect.height);
	canvas.LineTo(rect.left + rect.width / 2.0, rect.top);

	if (fillStyle && fillStyle->IsEnabled())
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
	return m_components.size();
}

IComponent* CSlide::GetShapeAtIndex(size_t index)
{
	if (m_components.size() > index)
	{
		return m_components[index];
	}
	return nullptr;
}

void CSlide::InsertShape(IComponent* shape, size_t position)
{
	if (position >= m_components.size())
	{
		m_components.push_back(shape);
	}
	else
	{
		m_components.insert(m_components.begin() + position, shape);
	}
	UpdateFrame();
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index < m_components.size())
	{
		m_components.erase(m_components.begin() + index);
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
	for (auto &shape : m_components)
	{
		shape->Draw(canvas);
	}
}

void CSlide::UpdateFrame()
{
	if (m_components.empty())
	{
		return;
	}
	double rightBottomX = 0;
	double rightBottomY = 0;

	std::for_each(m_components.begin(), m_components.end(), [&](IComponent* shape) {
		auto frame = shape->GetFrame();
		rightBottomX = std::max(rightBottomX, frame.left + frame.width);
		rightBottomY = std::max(rightBottomY, frame.top + frame.height);
	});

	m_width = rightBottomX;
	m_height = rightBottomY;
}

void Composite::Draw(ICanvas & canvas)
{
	for (auto &component : m_components)
	{
		component->Draw(canvas);
	}
}

StyleVariant Composite::GetLineStyle() const
{
	if (m_components.empty())
	{
		return StyleType::UnacceptableStyle;
	}
	auto firstElementStyle = m_components.front()->GetLineStyle();
	for (auto &component : m_components)
	{
		if (!(component->GetLineStyle() == firstElementStyle))
		{
			return StyleType::UnacceptableStyle;
		}
	}
	return firstElementStyle;
}

void Composite::SetLineStyle(const CStyle & style)
{
	for (auto& component : m_components)
	{
		component->SetLineStyle(style);
	}
}

StyleVariant Composite::GetFillStyle() const
{
	if (m_components.empty())
	{
		return StyleType::UnacceptableStyle;
	}
	auto firstElementStyle = m_components.front()->GetFillStyle();
	for (auto &component : m_components)
	{
		if (!(component->GetFillStyle() == firstElementStyle))
		{
			return StyleType::UnacceptableStyle;
		}
	}
	return firstElementStyle;
}

void Composite::SetFillStyle(const CStyle & style)
{
	for (auto& component : m_components)
	{
		component->SetFillStyle(style);
	}
}

void Composite::UpdateFrame()
{
	if (m_components.empty())
	{
		return;
	}
	double topLeftX = m_components.at(0)->GetFrame().left;
	double topLeftY = m_components.at(0)->GetFrame().top;
	double rightBottomX = 0;
	double rightBottomY = 0;

	std::for_each(m_components.begin(), m_components.end(), [&](IComponent* shape) {
		auto frame = shape->GetFrame();
		topLeftX = std::min(topLeftX, frame.left);
		topLeftY = std::min(topLeftY, frame.top);
		rightBottomX = std::max(rightBottomX, frame.left + frame.width);
		rightBottomY = std::max(rightBottomY, frame.top + frame.height);
	});

	SetFrame({ topLeftX ,topLeftY ,rightBottomX ,rightBottomY });
}

IComponent * Component::GetComponent(size_t index) const
{
	return nullptr;
}

void Component::AddComponent(IComponent * component, size_t position)
{
}

void Component::RemoveComponent(IComponent * component)
{
}

Composite * Component::GetComposite()
{
	return nullptr;
}

IComponent * Composite::GetComponent(size_t index) const
{
	if (index < m_components.size())
	{
		return m_components[index];
	}
	return nullptr;
}

void Composite::AddComponent(IComponent * component, size_t position)
{
	if (position >= m_components.size())
	{
		m_components.push_back(component);
	}
	else
	{
		m_components.insert(m_components.begin() + position, component);
	}
	UpdateFrame();
}

void Composite::RemoveComponent(IComponent * component)
{
	auto it = std::find(m_components.begin(), m_components.end(), component);
	if (it != m_components.end())
	{
		m_components.erase(it);
	}
	UpdateFrame();
}

Composite * Composite::GetComposite()
{
	return this;
}

bool operator==(const CStyle & left, const CStyle & right)
{
	if (left.m_color == right.m_color && left.m_isEnable == right.m_isEnable)
	{
		return true;
	}
	return false;
}

}