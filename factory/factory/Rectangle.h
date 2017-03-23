#pragma once
#include "Shape.h"

class CRectangle :
	public CAbstractShape
{
public:
	CRectangle(Vec2 const& topLeft, Vec2 const& size);
	~CRectangle();

	void Draw(ICanvas & canvas) const override;

	Vec2 GetLeftTop() const;
	Vec2 GetRightBottom() const;

private:
	Vec2 m_topLeft;
	Vec2 m_size;
};

