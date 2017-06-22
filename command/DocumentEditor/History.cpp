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
		m_commands[m_commandID - 1]->Unexecute(); // ����� ��������� ����������
		--m_commandID;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_commandID]->Execute(); // ����� ��������� ����������
		++m_commandID;
	}
}

void History::ExecuteCommand(ICommandPtr && command)
{
	if (m_commandID < m_commands.size()) // �� ���������� ���������� ������� ������
	{
		command->Execute();	// ����� ������� ����������
		++m_commandID;					// 
		m_commands.resize(m_commandID);	// ���������� ��������� �� �����, �.�. ������ <= ��������
		m_commands.back() = move(command);
	}
	else // ����� ����������� ���������� ������� ������
	{
		assert(m_commandID == m_commands.size());
		// ����������� ����� �� ����������� ������� 
		m_commands.emplace_back(nullptr); // ����� ��������� ����������, �� �� ��� ������ �� �������
		try
		{
			command->Execute(); // ����� ��������� ����������
								// �������� �������-��������
			m_commands.back() = move(command); // �� ������� ����������
			++m_commandID; // ������ ����� �������� ������ ��������� �������
		}
		catch (...)
		{
			// ������� ��������, �.�. ������� �� �����������
			m_commands.pop_back(); // �� ������� ����������
								   // ��������������� ��������� ���������� ����� (��� �� ��� �� ����), 
								   // �.�. ������� ��������� �� ������
			throw;
		}
	}
}
