#pragma once
#include <memory>

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};