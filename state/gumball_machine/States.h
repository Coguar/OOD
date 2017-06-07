#pragma once
#include "IState.h"

struct IGumballMachine;

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine & gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned ballsCount) override;
	std::string ToString() const override;

private:
	IGumballMachine & m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine & gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned ballsCount) override;
	std::string ToString() const override;
private:
	IGumballMachine & m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine & gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned ballsCount) override;
	std::string ToString() const override;

private:
	IGumballMachine & m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine & gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned ballsCount) override;
	std::string ToString() const override;
private:
	IGumballMachine & m_gumballMachine;
};

