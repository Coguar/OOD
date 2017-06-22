#include "stdafx.h"
#include "InsertParagraphCommand.h"



InsertParagraphCommand::InsertParagraphCommand(std::vector<CDocumentItem> & items, ParagraphPtr const & paragraphPtr, size_t position)
	: m_paragraphPtr(paragraphPtr)
	, m_items(items)
	, m_position(position)
{
}

InsertParagraphCommand::~InsertParagraphCommand()
{
}

void InsertParagraphCommand::DoExecute()
{
	m_items.insert(m_items.begin() + m_position, CDocumentItem(m_paragraphPtr));
}

void InsertParagraphCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}