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

void CPainter::DrawPicture(CPictureDraft const & draft, ICanvas * canvas)
{
	if (!canvas)
	{
		return;
	}
	for (auto &it : draft.GetShapesList())
	{
		it->Draw(canvas);
	}
}
