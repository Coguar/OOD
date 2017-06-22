#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"


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
	m_history.ExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}
