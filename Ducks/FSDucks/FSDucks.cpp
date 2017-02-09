// FSDucks.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <memory>
#include <iostream>
#include <functional>
#include <string>
#include <cassert>


using namespace std;

using Method = function<void()>;

void Print(std::string const& text)
{
	cout << text << endl;
}

namespace FlyMethods
{
	function<void()> GetFlyWithWingsMethod()
	{
		size_t flyCount = 0;
		return [flyCount]()mutable
		{
			string flyInfo = "I fly with wings " + to_string(++flyCount) + " time!";
			Print(flyInfo);
		};
		
	}

	void FlyNoWay()
	{
		Print("I can't fly");
	}
}
namespace QuackMethods
{
	void Qack()
	{
		Print("Quack! I say QUACK!!!");
	}

	void Squeak()
	{
		Print("Squeeeeeeeak!");
	}

	void WithoutSound()
	{
		Print("*silence");
	}
}

namespace DanceMethods
{
	void Waltz()
	{
		Print("I'm Dancing Waltz");
	}

	void Minuet()
	{
		Print("I'm Dancing Waltz");
	}

	void DanceNoWay()
	{
		Print("I do not dance( ");
	}
}

class CDuck
{
public:
	CDuck(Method const& flyBehavior,
		Method const& quackBehavior,
		Method const& danceBehavior)
		: m_flyBehavior(flyBehavior)
		, m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		assert(m_flyBehavior);
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		m_callItself = []() {};
	}
	~CDuck() {};

	void Fly()
	{
		m_flyBehavior();
	}

	void Quack()
	{
		m_quackBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}

	void Display() const
	{
		m_callItself();
	}

protected:
	Method m_callItself;

private:
	Method m_flyBehavior;
	Method m_quackBehavior;
	Method m_danceBehavior;
};




class MallardDuck : public CDuck
{
public:
	MallardDuck()
		: CDuck(FlyMethods::GetFlyWithWingsMethod(), QuackMethods::Qack, DanceMethods::Waltz)
	{
		m_callItself = []() { Print("I'm Mallard Duck!"); };
	}
};

class DeckoyDuck : public CDuck
{
public:
	DeckoyDuck()
		: CDuck(FlyMethods::FlyNoWay, QuackMethods::WithoutSound, DanceMethods::DanceNoWay)
	{
		m_callItself = []() { Print("I'm Deckoy Duck!"); };
	}
};

class RedheadDuck : public CDuck
{
public:
	RedheadDuck()
		: CDuck(FlyMethods::GetFlyWithWingsMethod(), QuackMethods::Qack, DanceMethods::Minuet)
	{
		m_callItself = []() { Print("I'm Redhead Duck!"); };
	}
};

class RubberDuck : public CDuck
{
public:
	RubberDuck()
		: CDuck(FlyMethods::FlyNoWay, QuackMethods::Squeak, DanceMethods::DanceNoWay)
	{
		m_callItself = []() { Print("I'm Rubber Duck!"); };
	}
};

class ModelDuck : public CDuck
{
public:
	ModelDuck()
		: CDuck(FlyMethods::FlyNoWay, QuackMethods::WithoutSound, DanceMethods::DanceNoWay)
	{
		m_callItself = []() { Print("I'm Model Duck!"); };
	}
};

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck & duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Dance();
	duck.Fly();

	Print("!!!!!Stop playing !!!!!");
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
}