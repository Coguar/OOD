#include "stdafx.h"
#include "Paragraph.h"



Paragraph::Paragraph(const std::string& text, IHistory& history)
	: m_history(history)
	, m_text(text)
{
}


Paragraph::~Paragraph()
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string & text)
{
	m_text = text;
}
