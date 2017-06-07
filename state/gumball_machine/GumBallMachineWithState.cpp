#include "stdafx.h"
#include "GumBallMachineWithState.h"
#include <boost/format.hpp>

namespace with_state
{
CGumballMachine::CGumballMachine(unsigned numBalls)
	: m_soldState(*this)
	, m_soldOutState(*this)
	, m_noQuarterState(*this)
	, m_hasQuarterState(*this)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
{
	if (m_count > 0)
	{
		m_state = &m_noQuarterState;
	}
}
void CGumballMachine::EjectQuarter()
{
	m_state->EjectQuarter();
	m_quartersCount = 0;
}
void CGumballMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}
void CGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}

void CGumballMachine::Refill(unsigned numBalls)
{
	m_count = numBalls;
	m_state->Refill(numBalls);
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
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % m_state->ToString()).str();
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
	m_state = &m_soldOutState;
}
void CGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}
void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
	--m_quartersCount;
}
void CGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
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