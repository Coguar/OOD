#include "stdafx.h"
#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(std::shared_ptr<IImage> const & imagePtr, int oldWidth, int oldHeight, int newWidth, int newHeight)
	: m_imagePtr(imagePtr)
	, m_oldsize(Size(oldWidth, oldHeight))
	, m_newSize(Size(newWidth, newHeight))
{
}

ResizeImageCommand::~ResizeImageCommand()
{
}

void ResizeImageCommand::DoExecute()
{
	m_imagePtr->SetSize(m_newSize.x, m_newSize.y);
}

void ResizeImageCommand::DoUnexecute()
{
	m_imagePtr->SetSize(m_oldsize.x, m_oldsize.y);
}
