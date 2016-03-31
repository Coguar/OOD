#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include <map>
#include <string>

using namespace std;


struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string stantionName;
};

class CDisplay: public IObserver<SWeatherInfo>
{
public:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CSensorData
{
public:

	CSensorData(std::string const& sensorName)
		:m_sensorName(sensorName)
	{
	}

	void UpdateSensor(double const& sensorData)
	{
		if (m_minValue > sensorData)
		{
			m_minValue = sensorData;
		}
		if (m_maxValue < sensorData)
		{
			m_maxValue = sensorData;
		}
		m_accValue += sensorData;
		++m_countAcc;

		std::cout << "Max " << m_sensorName << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_sensorName << " " << m_minValue << std::endl;
		std::cout << "Average " << m_sensorName << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
	std::string m_sensorName;
};

struct SSensorsList
{
	CSensorData m_tempSensor = CSensorData("temperature");
	CSensorData m_humiditySensor = CSensorData("humidity");
	CSensorData m_pressureSensor = CSensorData("pressure");
};
class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	void Update(SWeatherInfo const& data) override
	{
		auto station = m_weatherStantionDic.find(data.stantionName);
		if (station == m_weatherStantionDic.end())
		{
			AddInMap(data.stantionName);
		}
		station = m_weatherStantionDic.find(data.stantionName);

		std::cout << "--------" << data.stantionName.c_str() << "--------" << std::endl;
		station->second.m_tempSensor.UpdateSensor(data.temperature);
		station->second.m_humiditySensor.UpdateSensor(data.humidity);
		station->second.m_pressureSensor.UpdateSensor(data.pressure);
	}
private:

	std::map<std::string, SSensorsList> m_weatherStantionDic ;

	void AddInMap(std::string const& key)
	{
		m_weatherStantionDic.insert(std::pair<std::string, SSensorsList>(key, SSensorsList()));

	}

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string const& name)
		:m_stantionName(name)
	{
	}
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.stantionName = m_stantionName;
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;

	std::string m_stantionName;
};
