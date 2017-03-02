#include "stdafx.h"
#include "../WeatherStation2017/Observer.h"
#include <memory>
#include <vector>

class TestObserver : public IObserver<int>
{
public:
	TestObserver(int addedValue, std::shared_ptr<std::vector<int>> const& vecPtr)
		: m_vectorPtr(vecPtr)
		, m_addedValue(addedValue)
	{

	}

	void Update(int const& data, std::string const& observableName) override
	{
		m_log.push_back(observableName);
		m_data = data;
		if (m_vectorPtr)
			m_vectorPtr->push_back(m_data + m_addedValue);
	}

	int GetData() const
	{
		return m_data;
	}

	std::vector<std::string> const& GetLog() const
	{
		return m_log;
	}

private:
	int m_data = std::numeric_limits<int>::min();
	int m_addedValue = 0;
	std::shared_ptr<std::vector<int>> m_vectorPtr;
	std::vector<std::string> m_log;
};

class TestObserveble : public CObservable<int>
{
public:
	TestObserveble(std::string const& name)
		: m_name(name)
	{}

	void SetData(int value)
	{
		m_data = value;
		NotifyObservers();
	}

	int GetData() const
	{
		return m_data;
	}

protected:
	int GetChangedData()const override
	{
		return GetData();
	}

	std::string GetName()const override
	{
		return m_name;
	}

private:
	int m_data = 0;
	std::string m_name;
};

struct TempTestSet
{
	TempTestSet()
		: m_dataCollector(std::make_shared<std::vector<int>>())
		, m_observeble(TestObserveble("test"))
	{}
	TestObserveble m_observeble;
	std::shared_ptr<std::vector<int>> m_dataCollector;
};

BOOST_FIXTURE_TEST_SUITE(testing_observable_work_with_observer_priority, TempTestSet);

	BOOST_AUTO_TEST_CASE(when_first_observer_have_higher_priority_)
	{
		TestObserver first(5, m_dataCollector);
		TestObserver second(10, m_dataCollector);
		m_observeble.RegisterObserver(first, 1);
		m_observeble.RegisterObserver(second, 2);
		m_observeble.SetData(10);
		BOOST_CHECK_EQUAL(m_dataCollector->size(), 2);
		BOOST_CHECK(15 == (*m_dataCollector.get())[0]);
		BOOST_CHECK(20 == (*m_dataCollector.get())[1]);
	}

	BOOST_AUTO_TEST_CASE(when_second_observer_have_higher_priority_)
	{
		TestObserver first(5, m_dataCollector);
		TestObserver second(10, m_dataCollector);
		m_observeble.RegisterObserver(first, 3);
		m_observeble.RegisterObserver(second, 2);
		m_observeble.SetData(10);
		BOOST_CHECK_EQUAL(m_dataCollector->size(), 2);
		BOOST_CHECK(20 == (*m_dataCollector.get())[0]);
		BOOST_CHECK(15 == (*m_dataCollector.get())[1]);
	}

	BOOST_AUTO_TEST_CASE(when_priority_of_two_observers_is_equal_then_they_will_be_notified_with_number_of_registration_)
	{
		TestObserver first(5, m_dataCollector);
		TestObserver second(10, m_dataCollector);
		m_observeble.RegisterObserver(first, 2);
		m_observeble.RegisterObserver(second, 2);
		m_observeble.SetData(10);
		BOOST_CHECK_EQUAL(m_dataCollector->size(), 2);
		BOOST_CHECK(15 == (*m_dataCollector.get())[0]);
		BOOST_CHECK(20 == (*m_dataCollector.get())[1]);
	}

	BOOST_AUTO_TEST_CASE(if_observers_was_regisred_without_priority_than_they_will_be_notified_with_number_of_registration_)
	{
		TestObserver first(5, m_dataCollector);
		TestObserver second(10, m_dataCollector);
		m_observeble.RegisterObserver(first);
		m_observeble.RegisterObserver(second);
		m_observeble.SetData(10);
		BOOST_CHECK_EQUAL(m_dataCollector->size(), 2);
		BOOST_CHECK(15 == (*m_dataCollector.get())[0]);
		BOOST_CHECK(20 == (*m_dataCollector.get())[1]);
	}

BOOST_AUTO_TEST_SUITE_END();

struct two_different_wd
{
	two_different_wd()
		: m_first(TestObserveble("first"))
		, m_second(TestObserveble("second"))
		, m_dataCollector(std::make_shared<std::vector<int>>())
	{}
	TestObserveble m_first;
	TestObserveble m_second;
	std::shared_ptr<std::vector<int>> m_dataCollector;
};

BOOST_FIXTURE_TEST_SUITE(testing_observer_when_its_registr_by_two_different_observable_, two_different_wd);

	BOOST_AUTO_TEST_CASE(when_two_different_observable_classes_notify_observer_he_know_which_)
	{
		TestObserver obs(0, m_dataCollector);
		m_first.RegisterObserver(obs);
		m_second.RegisterObserver(obs);
		m_first.SetData(30);
		m_second.SetData(40);
		BOOST_CHECK_EQUAL(m_dataCollector->size(), 2);
		BOOST_CHECK(30 == (*m_dataCollector.get())[0]);
		BOOST_CHECK(40 == (*m_dataCollector.get())[1]);

		BOOST_CHECK(obs.GetLog()[0] == "first");
		BOOST_CHECK(obs.GetLog()[1] == "second");

	}

BOOST_AUTO_TEST_SUITE_END();