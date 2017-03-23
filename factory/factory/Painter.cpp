#include "stdafx.h"
#include "PictureDraft.h"
#include "Shape.h"
#include "Painter.h"


CPainter::CPainter()
{
}


CPainter::~CPainter()
{
}

void CPainter::DrawPicture(CPictureDraft const & draft, ICanvas & canvas)
{
	for (auto &it : draft.GetShapesList())
	{
		it->Draw(canvas);
	}
}
