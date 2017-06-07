#pragma once

#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned count);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);

	std::string ToString()const;

private:
	const unsigned MAX_QUARTER = 5;

	void Dispense();

	unsigned m_quarterCount;
	unsigned m_count;	// Количество шариков
	State m_state = State::SoldOut;
};
}