// Ducks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

using namespace std;

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};
class WaltzDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm Dancing Waltz" << endl;
	}
};
class  MinuetDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm Dancing Minuet!!" << endl;
	}
};
class  DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class Flyable :public IFlyBehavior
{
public:

	void Fly() override
	{
		FlyMethod();
		++m_flightCounter;
		cout << "it's my " << GetFlightCount() << " flight" << endl;
	}



	virtual void FlyMethod()
	{
		cout << "I'm flying!!" << endl;
	}

private:

	size_t GetFlightCount()
	{
		return m_flightCounter;
	}

	size_t m_flightCounter = 0;
};

class FlyWithWings :public Flyable
{
public:

	void FlyMethod() override
	{
		cout << m_flyMethodName.c_str() << endl;

	}
private:

	const string m_flyMethodName = "I'm flying with wings!!";

	size_t flightCount = 0;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior> && flyBehavior, unique_ptr<IQuackBehavior> && quackBehavior, 
		unique_ptr<IDanceBehavior> && danceBehavior)
		: m_quackBehavior(move(quackBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(move(flyBehavior));
		SetDanceBehavior(move(danceBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	virtual void Dance()
	{
		m_danseBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior> && flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	void SetDanceBehavior(unique_ptr<IDanceBehavior> && danceBehavior)
	{
		assert(danceBehavior);
		m_danseBehavior = move(danceBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() {};
private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danseBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<WaltzDance>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<MinuetDance>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck & duck)
{
	duck.Quack();
	duck.Dance();
	duck.Fly();
	DrawDuck(duck);
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);
}
