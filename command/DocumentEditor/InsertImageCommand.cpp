#include "stdafx.h"
#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(std::vector<CDocumentItem>& items, ImagePtr const & imagePtr, size_t position)
	: m_items(items)
	, m_imagePtr(imagePtr)
	, m_position(position)
{
}

InsertImageCommand::~InsertImageCommand()
{
}

void InsertImageCommand::DoExecute()
{
	m_items.insert(m_items.begin() + m_position, CDocumentItem(m_imagePtr));
}

void InsertImageCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}