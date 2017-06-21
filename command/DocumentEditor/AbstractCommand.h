#pragma once
#include "ICommand.h"

class AbstractCommand :
	public ICommand
{
public:
	virtual ~AbstractCommand() = default;

	void Execute() final;
	void Unexecute() final;
private:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

	bool m_isExrcuted = false;
};

