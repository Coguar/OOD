#include "AbstractCommand.h"


void AbstractCommand::Execute()
{
	if (!m_isExrcuted)
	{
		DoExecute();
		m_isExrcuted = true;
	}
}

void AbstractCommand::Unexecute()
{
	if (m_isExrcuted)
	{
		DoUnexecute();
		m_isExrcuted = false;
	}
}
