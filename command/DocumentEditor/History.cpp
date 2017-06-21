#include "stdafx.h"
#include "History.h"

bool History::CanUndo() const
{
	return m_commandID != 0;
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_commandID-- - 1]->Unexecute();
	}
}

bool History::CanRedo() const
{
	return m_commandID < MAX_MEMORIED_COMMANS_COUNT - 1;
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_commandID++]->Execute();
	}
}

void History::ExecuteCommand(ICommandPtr && command)
{
	m_commands.push_back(command);
	command->Execute();
	if (m_commands.size() > MAX_MEMORIED_COMMANS_COUNT)
	{
		m_commands.pop_front();
	}
	else
	{
		++m_commandID;
	}
}
