#include "stdafx.h"
#include "History.h"
#include "ICommand.h"

bool History::CanUndo() const
{
	return m_commandID != 0;
}

bool History::CanRedo() const
{
	return m_commandID != m_commands.size();
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_commandID - 1]->Unexecute(); // может выбросить исключение
		--m_commandID;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_commandID]->Execute(); // может выбросить исключение
		++m_commandID;
	}
}

void History::ExecuteCommand(ICommandPtr && command)
{
	if (m_commandID < m_commands.size()) // Ќе происходит расширени€ истории команд
	{
		command->Execute();	// может бросить исключение
		++m_commandID;					// 
		m_commands.resize(m_commandID);	// исключение выброшено не будет, т.к. размер <= текущему
		m_commands.back() = move(command);
	}
	else // будет происходить расширение истории команд
	{
		assert(m_commandID == m_commands.size());
		// резервируем место по добавл€емую команду 
		m_commands.emplace_back(nullptr); // может выбросить исключение, но мы еще ничего не трогали
		try
		{
			command->Execute(); // может выбросить исключение
								// замен€ем команду-заглушку
			m_commands.back() = move(command); // не бросает исключений
			++m_commandID; // теперь можно обновить индекс следующей команды
		}
		catch (...)
		{
			// удал€ем заглушку, т.к. команда не исполнилась
			m_commands.pop_back(); // не бросает исключений
								   // перевыбрасываем пойманное исключение вверх (кем бы оно ни было), 
								   // т.к. команду выполнить не смогли
			throw;
		}
	}
}
