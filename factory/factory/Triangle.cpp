#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle(Vec2 const & vertex1, Vec2 const & vertex2, Vec2 const & vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

CTriangle::~CTriangle() = default;

void CTriangle::Draw(ICanvas * canvas) const
{
	if (canvas)
	{
		canvas->SetColor(GetColor());
		canvas->DrawLine(m_vertex1, m_vertex2);
		canvas->DrawLine(m_vertex2, m_vertex3);
		canvas->DrawLine(m_vertex3, m_vertex1);
	}
}

Vec2 CTriangle::Getvertex1() const
{
	return m_vertex1;
}

Vec2 CTriangle::Getvertex2() const
{
	return m_vertex2;
}

Vec2 CTriangle::Getvertex3() const
{
	return m_vertex3;
}
