#pragma once
#include <iostream>
#include "IGumballMachine.h"
#include "States.h"

namespace with_state
{
class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls);
	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	std::string ToString()const;

	void Refill(unsigned numBalls);

	unsigned GetMaxQuarterCount() override;
	unsigned GetInsertedQuarterCount() override;
	void AddQuarter() override;
private:
	unsigned GetBallCount() const override;

	void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

private:
	const unsigned MAX_QUARTERS = 5;

	unsigned m_count = 0;
	unsigned m_quartersCount = 0;

	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState * m_state;
	
};

}
