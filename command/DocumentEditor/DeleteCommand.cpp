#include "stdafx.h"
#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(size_t position, std::vector<CDocumentItem>& items)
	: m_items(items)
	, m_position(position)
	, m_item(items[position])
{
}

DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void DeleteCommand::DoUnexecute()
{
	m_items.insert(m_items.begin() + m_position, m_item);
}
