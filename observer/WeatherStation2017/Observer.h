#pragma once

#include <set>
#include <map>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, std::string const& observableName) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer) = 0;
	virtual void RegisterObserver(IObserver<T> & observer, size_t priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer) override
	{
		m_observers.emplace(std::numeric_limits<size_t>::max(), &observer);
	}

	void RegisterObserver(IObserver<T> & observer, size_t priority)
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		auto copyObservers = m_observers;
		T data = GetChangedData();
		for (auto & observer : copyObservers)
		{
			observer.second->Update(data, GetName());
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;
	virtual std::string GetName() const = 0;
private:
	std::multimap<size_t, ObserverType*> m_observers;
};
