#pragma once
#include "IParagraph.h"
#include "IHistory.h"

class Paragraph 
	: public IParagraph
	, public std::enable_shared_from_this<IParagraph>
{
public:
	Paragraph(const std::string& text, IHistory& history);
	~Paragraph();

	std::string GetText()const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	IHistory& m_history;
};

