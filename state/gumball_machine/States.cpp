#include "stdafx.h"
#include "States.h"
#include "IGumballMachine.h"
#include <iostream>

/////////Sold State////////

CSoldState::CSoldState(IGumballMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{
}
void CSoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}
void CSoldState::EjectQuarter()
{
	std::cout << "Sorry you already turned the crank\n";
}
void CSoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball\n";
}
void CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		std::cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else if(m_gumballMachine.GetInsertedQuarterCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
}
void CSoldState::Refill(unsigned /*ballsCount*/)
{
	std::cout << "You can't refill, the machine is sold\n";
}
std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}


////////// SoldOut State /////////////////

CSoldOutState::CSoldOutState(IGumballMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{}

void CSoldOutState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}
void CSoldOutState::EjectQuarter()
{
	std::cout << "You can't eject, you haven't inserted a quarter yet\n";
}
void CSoldOutState::TurnCrank()
{
	std::cout << "You turned but there's no gumballs\n";
}
void CSoldOutState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}
void CSoldOutState::Refill(unsigned ballsCount)
{
	std::cout << "Now balls count is " << ballsCount << std::endl;
	if (ballsCount == 0)
	{
		return;
	}
	if (m_gumballMachine.GetInsertedQuarterCount() != 0)
	{
		m_gumballMachine.SetHasQuarterState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}
std::string CSoldOutState::ToString() const
{
	return "sold out";
}


///////////////////Has Quarter State /////////////////

CHasQuarterState::CHasQuarterState(IGumballMachine & gumballMachine)
	:m_gumballMachine(gumballMachine)
{}

void CHasQuarterState::InsertQuarter()
{
	auto count = m_gumballMachine.GetInsertedQuarterCount();
	if (count < m_gumballMachine.GetMaxQuarterCount())
	{
		m_gumballMachine.AddQuarter();
		return;
	}
	std::cout << "You can't insert another quarter\n";
}
void CHasQuarterState::EjectQuarter()
{
	std::cout << "Quarter returned\n";
	m_gumballMachine.SetNoQuarterState();
}
void CHasQuarterState::TurnCrank()
{
	std::cout << "You turned...\n";
	m_gumballMachine.SetSoldState();
}
void CHasQuarterState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}
void CHasQuarterState::Refill(unsigned ballsCount)
{
	if (ballsCount == 0)
	{
		m_gumballMachine.SetSoldOutState();
	}
	std::cout << "Now balls count is " << ballsCount << std::endl;
}
std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}

///////////////// No Quarter State //////////////////

CNoQuarterState::CNoQuarterState(IGumballMachine & gumballMachine)
	: m_gumballMachine(gumballMachine)
{}

void CNoQuarterState::InsertQuarter()
{
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.AddQuarter();
	m_gumballMachine.SetHasQuarterState();
}
void CNoQuarterState::EjectQuarter()
{
	std::cout << "You haven't inserted a quarter\n";
}
void CNoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}
void CNoQuarterState::Dispense()
{
	std::cout << "You need to pay first\n";
}
void CNoQuarterState::Refill(unsigned ballsCount)
{
	if (ballsCount == 0)
	{
		m_gumballMachine.SetSoldOutState();
	}
	std::cout << "Now balls count is " << ballsCount << std::endl;
}
std::string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}