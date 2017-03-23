#pragma once
#include "Shape.h"
class CTriangle :
	public CAbstractShape
{
public:
	CTriangle(Vec2 const& vertex1, Vec2 const& vertex2, Vec2 const& vertex3);
	~CTriangle();

	void Draw(ICanvas & canvas) const override;
	Vec2 Getvertex1() const;
	Vec2 Getvertex2() const;
	Vec2 Getvertex3() const;

private:
	Vec2 m_vertex1;
	Vec2 m_vertex2;
	Vec2 m_vertex3;
};

