#include "stdafx.h"
#include "NaiveGumBallMachine.h"

namespace naive
{
CGumballMachine::CGumballMachine(unsigned count)
	: m_count(count)
	, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	, m_quarterCount(0)
{
}

void CGumballMachine::InsertQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
		cout << "You inserted a quarter\n";
		++m_quarterCount;
		m_state = State::HasQuarter;
		break;
	case State::HasQuarter:
		if (m_quarterCount >= MAX_QUARTER)
		{
			cout << "You can't insert another quarter\n";
			break;
		}
		++m_quarterCount;
		break;
	case State::Sold:
		cout << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void CGumballMachine::EjectQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::HasQuarter:
		cout << "Quarter returned\n";
		m_quarterCount = 0;
		m_state = State::NoQuarter;
		break;
	case State::NoQuarter:
		cout << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
		cout << "Sorry you already turned the crank\n";
		break;
	case State::SoldOut:
		if (m_quarterCount > 0)
		{
			cout << "Quarter returned\n";
			m_quarterCount = 0;
			break;
		}
		cout << "You can't eject, you haven't inserted a quarter yet\n";
		break;
	}
}

void CGumballMachine::TurnCrank()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		cout << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		cout << "You turned...\n";
		m_state = State::Sold;
		Dispense();
		break;
	case State::Sold:
		cout << "Turning twice doesn't get you another gumball\n";
		break;
	}
}

void CGumballMachine::Refill(unsigned numBalls)
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
	case State::NoQuarter:
	case State::HasQuarter:
		break;
	case State::Sold:
		cout << "You can't refill in this moment\n";
		return;
	}
	m_count = numBalls;
	if (m_count == 0)
	{
		m_state = State::SoldOut;
	}
	else if (m_quarterCount > 0)
	{
		m_state = State::HasQuarter;
	}
	else
	{
		m_state = State::NoQuarter;
	}
}

std::string CGumballMachine::ToString()const
{
	std::string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Credit: %3% quarer%4%
Machine is %5%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % (m_quarterCount != 1 ? "s" : "") % state).str();
}

void CGumballMachine::Dispense()
{
	using namespace std;
	--m_quarterCount;
	switch (m_state)
	{
	case State::Sold:
		cout << "A gumball comes rolling out the slot\n";
		--m_count;
		if (m_count == 0)
		{
			cout << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
			break;
		}
		if (m_quarterCount == 0)
		{
			m_state = State::NoQuarter;
			break;
		}
		m_state = State::HasQuarter;
		break;
	case State::NoQuarter:
		cout << "You need to pay first\n";
		break;
	case State::SoldOut:
	case State::HasQuarter:
		cout << "No gumball dispensed\n";
		break;
	}
}
}