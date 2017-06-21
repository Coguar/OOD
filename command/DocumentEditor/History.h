#pragma once
#include "IHistory.h"

class History :
	public IHistory
{
public:
	History() = default;
	~History() = default;



	bool CanUndo()const override;
	void Undo() override;

	bool CanRedo()const override;
	void Redo() override;

	void ExecuteCommand(ICommandPtr && command) override;

private:

	const size_t MAX_MEMORIED_COMMANS_COUNT = 10;

	std::deque<ICommandPtr> m_commands;

	size_t m_commandID = 0;
};

