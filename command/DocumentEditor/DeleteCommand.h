#pragma once
#include "AbstractCommand.h"
#include "Items.h"

class DeleteCommand :
	public AbstractCommand
{
public:
	DeleteCommand(size_t position, std::vector<CDocumentItem> & items);
	~DeleteCommand();

	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem> & m_items;
	size_t m_position;
	CDocumentItem m_item;
};

