#include "TypedShapes.h"


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