#pragma once
#include "ConnectionStorage.h"

#include <set>
#include <map>
#include <functional>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, std::string const& observableName) = 0;
	virtual void SetConnection(boost::signals2::connection const& connection) = 0;
	virtual boost::signals2::connection GetConnection() const = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class CObserver : public IObserver<T>
{
public:
	void SetConnection(boost::signals2::connection const& connection) override
	{
		m_connection = connection;
	}

	boost::signals2::connection GetConnection() const override
	{
		return m_connection;
	}

private:
	boost::signals2::connection m_connection;
};
/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer) override
	{
		auto connection = m_onDataUpdate.connect(boost::bind(&IObserver<T>::Update, &observer, _1, _2));
		observer.SetConnection(connection);
		m_storage += connection;
	}

	void NotifyObservers() override
	{
		m_onDataUpdate(GetChangedData(), GetName());
	}

	void RemoveObserver(ObserverType & observer) override
	{
		observer.GetConnection().disconnect();
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;
	virtual std::string GetName() const = 0;
private:
	boost::signals2::signal<void(T, std::string)> m_onDataUpdate;

	ScopedConnectionsStorage m_storage;
};

