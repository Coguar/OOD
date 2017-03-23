#include "stdafx.h"
#include "DesignerInterface.h"
#include "PainterInterface.h"
#include "Shape.h"
#include "Client.h"

CClient::CClient(IDesigner & designer, IPainter & painter)
	: m_pDesigner(designer)
	, m_pPainter(painter)
{
}

CClient::~CClient() = default;

void CClient::TurnToDesigner(std::istream & strm)
{
		m_pictureDraft = m_pDesigner.CreateDraft(strm);
}

void CClient::TurnToPainter(ICanvas & canvas)
{
		m_pPainter.DrawPicture(m_pictureDraft, canvas);
}
