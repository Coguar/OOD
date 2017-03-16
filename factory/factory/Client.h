#pragma once
#include "PictureDraft.h"

struct IDesigner;
struct IPainter;
struct ICanvas;

class CClient
{
public:
	CClient(IDesigner * designer, IPainter * painter);
	~CClient();

	void TurnToDesigner(std::istream & strm);
	void TurnToPainter(ICanvas * canvas);

private:

	IDesigner * m_pDesigner = nullptr;
	IPainter * m_pPainter = nullptr;

	CPictureDraft m_pictureDraft;
};

