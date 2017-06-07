#include "stdafx.h"
#include "../gumball_machine/NaiveGumBallMachine.h"
#include "../gumball_machine/GumBallMachineWithDynamicallyCreatedState.h"
#include "../gumball_machine/GumBallMachineWithState.h"
#include <boost/mpl/vector.hpp>

namespace
{
std::string FormatingGBOutput(unsigned ballCount, unsigned quarterCount, std::string state)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Credit: %3% quarer%4%
Machine is %5%
)");
	return (fmt % ballCount % (ballCount != 1 ? "s" : "") % quarterCount % (quarterCount != 1 ? "s" : "") % state).str();
}

const std::string SOLD_OUT = "sold out";
const std::string NO_QUARTER = "waiting for quarter";
const std::string HAS_QUARTER = "waiting for turn of crank";
const std::string SOLD = "delivering a gumball";
}
struct NaiveGumBall
{
	NaiveGumBall()
		: gumballMachine(naive::CGumballMachine(3))
	{};
	naive::CGumballMachine gumballMachine;
};

struct GumBallWithState
{
	GumBallWithState()
		: gumballMachine(with_state::CGumballMachine(3))
	{};
	with_state::CGumballMachine gumballMachine;
};

struct GumBallWithDynamicState
{
	GumBallWithDynamicState()
		: gumballMachine(with_dynamic_state::CGumballMachine(3))
	{};
	with_dynamic_state::CGumballMachine gumballMachine;
};

using Fixtures = boost::mpl::vector<NaiveGumBall, GumBallWithState, GumBallWithDynamicState>;


BOOST_FIXTURE_TEST_SUITE(testing_naive_gumball_machine, NaiveGumBall)

BOOST_FIXTURE_TEST_CASE_TEMPLATE(check_default_state, T, Fixtures, T)
{
	BOOST_CHECK_EQUAL(T::gumballMachine.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_pull_a_quarter, T, Fixtures, T)
{
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
	gumballMachine.InsertQuarter();
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), FormatingGBOutput(3, 1, HAS_QUARTER));
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_try_to_getting_a_ball, T, Fixtures, T)
{
	gumballMachine.TurnCrank();
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
}

BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_try_to_getting_a_quarter, T, Fixtures, T)
{
	gumballMachine.EjectQuarter();
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
}

struct GumBallmachineWithQuarter
{
	GumBallmachineWithQuarter()
		: gumballMachineWithQuarter(naive::CGumballMachine(3))
	{
		gumballMachineWithQuarter.InsertQuarter();
	};
	naive::CGumballMachine gumballMachineWithQuarter;
};

struct GumBallmachineWithStateWithQuarter
{
	GumBallmachineWithStateWithQuarter()
		: gumballMachineWithQuarter(with_state::CGumballMachine(3))
	{
		gumballMachineWithQuarter.InsertQuarter();
	};
	with_state::CGumballMachine gumballMachineWithQuarter;
};

struct GumBallmachineWithDynamicStateWithQuarter
{
	GumBallmachineWithDynamicStateWithQuarter()
		: gumballMachineWithQuarter(with_dynamic_state::CGumballMachine(3))
	{
		gumballMachineWithQuarter.InsertQuarter();
	};
	with_dynamic_state::CGumballMachine gumballMachineWithQuarter;
};

using FixturesWithQuarters = boost::mpl::vector<GumBallmachineWithQuarter, GumBallmachineWithStateWithQuarter, GumBallmachineWithDynamicStateWithQuarter>;


	BOOST_FIXTURE_TEST_SUITE(testing_naive_gumball_machine_when_has_quarter, GumBallmachineWithQuarter)
		BOOST_FIXTURE_TEST_CASE_TEMPLATE(check_that_having_1_quarter, T, FixturesWithQuarters, T)
		{
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 1, HAS_QUARTER));
		}
		
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_getting_a_ball, T, FixturesWithQuarters, T)
		{
			gumballMachineWithQuarter.TurnCrank();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(2, 0, NO_QUARTER));
		}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_getting_a_quarter, T, FixturesWithQuarters, T)
		{
			gumballMachineWithQuarter.EjectQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
		}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_add_4_more_quarters, T, FixturesWithQuarters, T)
		{
			gumballMachineWithQuarter.InsertQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 2, HAS_QUARTER));
			gumballMachineWithQuarter.InsertQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 3, HAS_QUARTER));
			gumballMachineWithQuarter.InsertQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 4, HAS_QUARTER));
			gumballMachineWithQuarter.InsertQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 5, HAS_QUARTER));
			gumballMachineWithQuarter.InsertQuarter();
			BOOST_CHECK_EQUAL(gumballMachineWithQuarter.ToString(), FormatingGBOutput(3, 5, HAS_QUARTER));
		}

	BOOST_AUTO_TEST_SUITE_END()


struct GumBallMachineWhenQuartersMoreThenBalls
{
		GumBallMachineWhenQuartersMoreThenBalls()
			: gumballMachineWithMaxQuarter(naive::CGumballMachine(3))
		{
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
		};
		naive::CGumballMachine gumballMachineWithMaxQuarter;
};

	struct GumBallMachineWhenQuartersMoreThenBalls_WS
	{
		GumBallMachineWhenQuartersMoreThenBalls_WS()
			: gumballMachineWithMaxQuarter(with_state::CGumballMachine(3))
		{
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
		};
		with_state::CGumballMachine gumballMachineWithMaxQuarter;
	};

	struct GumBallMachineWhenQuartersMoreThenBalls_WDS
	{
		GumBallMachineWhenQuartersMoreThenBalls_WDS()
			: gumballMachineWithMaxQuarter(with_dynamic_state::CGumballMachine(3))
		{
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
			gumballMachineWithMaxQuarter.InsertQuarter();
		};
		with_dynamic_state::CGumballMachine gumballMachineWithMaxQuarter;
	};

	using FixturesWithMaxQuarters = boost::mpl::vector<GumBallMachineWhenQuartersMoreThenBalls, GumBallMachineWhenQuartersMoreThenBalls_WS, GumBallMachineWhenQuartersMoreThenBalls_WDS>;


	BOOST_FIXTURE_TEST_SUITE(testing_naive_gumball_machine_when_has_max_quarters, GumBallMachineWhenQuartersMoreThenBalls)

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(check_start_state, T, FixturesWithMaxQuarters, T)
	{
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(3, 5, HAS_QUARTER));
	}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(cannot_add_quarter, T, FixturesWithMaxQuarters, T)
	{
		gumballMachineWithMaxQuarter.InsertQuarter();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(3, 5, HAS_QUARTER));
	}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_get_5_quarters, T, FixturesWithMaxQuarters, T)
	{
		gumballMachineWithMaxQuarter.EjectQuarter();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(3, 0, NO_QUARTER));
	}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_getting_3_balls_and_2_quarters, T, FixturesWithMaxQuarters, T)
	{
		gumballMachineWithMaxQuarter.TurnCrank();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(2, 4, HAS_QUARTER));
		gumballMachineWithMaxQuarter.TurnCrank();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(1, 3, HAS_QUARTER));
		gumballMachineWithMaxQuarter.TurnCrank();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(0, 2, SOLD_OUT));
		gumballMachineWithMaxQuarter.TurnCrank();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(0, 2, SOLD_OUT));
		gumballMachineWithMaxQuarter.EjectQuarter();
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(0, 0, SOLD_OUT));
	}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_refill_GM, T, FixturesWithMaxQuarters, T)
	{
		gumballMachineWithMaxQuarter.Refill(2);
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(2, 5, HAS_QUARTER));
	}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_refill_to_0_and_back, T, FixturesWithMaxQuarters, T)
	{
		gumballMachineWithMaxQuarter.Refill(0);
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(0, 5, SOLD_OUT));
		gumballMachineWithMaxQuarter.Refill(5);
		BOOST_CHECK_EQUAL(gumballMachineWithMaxQuarter.ToString(), FormatingGBOutput(5, 5, HAS_QUARTER));
	}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()