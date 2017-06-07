#include "stdafx.h"
#include "GumBallMachineWithDynamicallyCreatedState.h"
#include <boost/format.hpp>


namespace with_dynamic_state
{
CGumballMachine::CGumballMachine(unsigned numBalls)
	: m_count(numBalls)
{

	if (m_count > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}
void CGumballMachine::EjectQuarter()
{
	m_currentState->EjectQuarter();
	m_quartersCount = 0;
}
void CGumballMachine::InsertQuarter()
{
	m_currentState->InsertQuarter();
}
void CGumballMachine::TurnCrank()
{
	m_currentState->TurnCrank();
	m_currentState->Dispense();
}

void CGumballMachine::Refill(unsigned numBalls)
{
	m_count = numBalls;
	m_currentState->Refill(numBalls);
}

std::string CGumballMachine::ToString()const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Credit: %3% quarer%4%
Machine is %5%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % m_currentState->ToString()).str();
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_count;
}
void CGumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		std::cout << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}
void CGumballMachine::SetSoldOutState()
{
	m_currentState.reset(new CSoldOutState(*this));
}
void CGumballMachine::SetNoQuarterState()
{
	m_currentState.reset(new CNoQuarterState(*this));
}
void CGumballMachine::SetSoldState()
{
	m_currentState.reset(new CSoldState(*this));
	--m_quartersCount;
}
void CGumballMachine::SetHasQuarterState()
{
	m_currentState.reset(new CHasQuarterState(*this));
}
unsigned CGumballMachine::GetMaxQuarterCount()
{
	return MAX_QUARTERS;
}
unsigned CGumballMachine::GetInsertedQuarterCount()
{
	return m_quartersCount;
}
void CGumballMachine::AddQuarter()
{
	++m_quartersCount;
}
}
