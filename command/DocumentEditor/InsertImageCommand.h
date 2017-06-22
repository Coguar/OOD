#pragma once
#include "AbstractCommand.h"
#include "Items.h"
#include "IImage.h"

class InsertImageCommand :
	public AbstractCommand
{

public:
	InsertImageCommand(std::vector<CDocumentItem> & items,ImagePtr const & imagePtr,size_t position);
	~InsertImageCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	ImagePtr m_imagePtr;
	size_t m_position;
	std::vector<CDocumentItem> & m_items;
};

