#include "Style.h"

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

bool operator==(const CStyle & left, const CStyle & right)
{
	return (left.m_color == right.m_color && left.m_isEnable == right.m_isEnable);
}

bool operator!=(const CStyle & left, const CStyle & right)
{
	return !(left == right);
}
