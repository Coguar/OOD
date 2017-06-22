#pragma once
#include "AbstractCommand.h"
#include "IImage.h"

class ResizeImageCommand :
	public AbstractCommand
{
public:

	ResizeImageCommand(std::shared_ptr<IImage> const & imagePtr, int oldWidth, int oldHeight, int newWidth, int newHeight);
	~ResizeImageCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	struct Size
	{
		Size(int x, int y)
			: x(x)
			, y(y)
		{};
		int x = 0;
		int y = 0;
	};

	std::shared_ptr<IImage> m_imagePtr;
	Size m_newSize;
	Size m_oldsize;
};

