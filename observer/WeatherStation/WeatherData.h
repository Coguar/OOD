#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include <map>

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
	void UpdateSensor(double const& sensorData, std::string sensorName)
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

		std::cout << "Max " << sensorName.c_str() << " " << m_maxValue << std::endl;
		std::cout << "Min " << sensorName.c_str() << " " << m_minValue << std::endl;
		std::cout << "Average " << sensorName.c_str() << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;

};

struct SSensorsList
{
	CSensorData m_tempSensor;
	CSensorData m_humiditySensor;
	CSensorData m_pressureSensor;
};
class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	void Update(SWeatherInfo const& data) override
	{
		auto stantion = m_WeatherStantionDic.find(data.stantionName);
		if (stantion == m_WeatherStantionDic.end())
		{
			AddInMap(data.stantionName);
		}
		stantion = m_WeatherStantionDic.find(data.stantionName);

			std::cout << "--------" << data.stantionName.c_str() << "--------" << std::endl;
			stantion->second.m_tempSensor.UpdateSensor(data.temperature, "temperature");
			stantion->second.m_humiditySensor.UpdateSensor(data.humidity, "humidity");
			stantion->second.m_pressureSensor.UpdateSensor(data.pressure, "pressure");
	}
private:

	std::map<std::string, SSensorsList> m_WeatherStantionDic ;

	void AddInMap(std::string key)
	{
		m_WeatherStantionDic.insert(std::pair<std::string, SSensorsList>(key, SSensorsList()));

	}

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string name)
	{
		m_stantionName = name;
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
