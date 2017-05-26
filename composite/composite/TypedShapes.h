#pragma once
#include "Shape.h"

class CRectangle : public Shape
{
public:
	CRectangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CEllipse : public Shape
{
public:
	CEllipse(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CTriangle : public Shape
{
public:
	CTriangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

