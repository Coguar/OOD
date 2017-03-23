#pragma once

class CPictureDraft;
struct ICanvas;

struct IPainter
{
	virtual ~IPainter() = default;
	virtual void DrawPicture(CPictureDraft const& draft, ICanvas & canvas) = 0;
};