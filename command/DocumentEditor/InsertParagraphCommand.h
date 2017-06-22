#pragma once
#include "AbstractCommand.h"
#include "Items.h"
#include "IDocument.h"

class InsertParagraphCommand :
	public AbstractCommand
{

public:
	InsertParagraphCommand(std::vector<CDocumentItem> & items, ParagraphPtr const & paragraphPtr, size_t position);
	~InsertParagraphCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	ParagraphPtr m_paragraphPtr;
	size_t m_position;
	std::vector<CDocumentItem> & m_items;
};

