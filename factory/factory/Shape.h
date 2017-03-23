#pragma once
#include "CanvasInterface.h"

class CAbstractShape
{
public:
	CAbstractShape();
	virtual ~CAbstractShape();

	void SetColor(Color color);
	Color GetColor() const;
	virtual void Draw(ICanvas & canvas) const; 

private:
	Color m_color;
};

