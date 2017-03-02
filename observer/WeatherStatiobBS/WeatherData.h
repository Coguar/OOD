#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

namespace windCalculator
{
	std::string GetDirectionByAngle(double angle)
	{
		auto a = angle > 0 ? angle : 360.0 + angle;
		int sector = int(a / 22.5);
		if (sector >= 15 || sector == 0)
		{
			return "North";
		}
		else if (sector > 0 && sector < 3)
		{
			return "Northeast";
		}
		else if (sector > 2 && sector < 5)
		{
			return "East";
		}
		else if (sector > 4 && sector < 7)
		{
			return "Southeast";
		}
		else if (sector > 6 && sector < 9)
		{
			return "South";
		}
		else if (sector > 8 && sector < 11)
		{
			return "Southwest";
		}
		else if (sector > 10 && sector < 13)
		{
			return "West";
		}
		else if (sector > 12 && sector < 15)
		{
			return "Northwest";
		}
		else
		{
			return "North";
		}
	}
}

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CDisplay: public CObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, std::string const& observableName) override
	{
		std::cout << std::endl << "Info from " << observableName << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << windCalculator::GetDirectionByAngle(data.windDirection) << std::endl;
		std::cout << "----------------" << std::endl << std::endl;
	}
};

struct ISensor
{
	virtual ~ISensor() = default;
	virtual void Update(double const& newValue) = 0;
	virtual void Display() = 0;
};

class CSensor
{
public:
	CSensor(std::string const& sensorName)
		: m_sensorName(sensorName)
	{
	}
	virtual ~CSensor() = default;
	virtual void Update(double const& newValue)
	{
		m_minValue = std::min(newValue, m_minValue);
		m_maxValue = std::max(newValue, m_maxValue);
		m_accMeasurements += newValue;
		++m_countAcc;
	}

	void Display()
	{
		std::cout << "Max " << m_sensorName << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_sensorName << " " << m_minValue << std::endl;
		std::cout << "Average " << m_sensorName << " " << (m_accMeasurements / m_countAcc) << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
	}

private:
	std::string m_sensorName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accMeasurements = 0;
	unsigned m_countAcc = 0;
};

class CWindDirSensor : public ISensor
{
public:
	void Update(double const& newValue) override
	{
		double dir = newValue;
		while (dir >= 360.0)
			dir -= 360.0;
		auto rad = dir * (M_PI / 180.0);
		m_xPos += std::cos(rad);
		m_yPos += std::sin(rad);
	}

	void Display()
	{
		auto angle = std::atan2(m_yPos, m_xPos)*(180 / M_PI);
		std::cout << "Average wind direction is " << windCalculator::GetDirectionByAngle(angle) << std::endl;
	}

private:
	double m_xPos = 0;
	double m_yPos = 0;
};

class CStatsDisplay : public CObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_tempSensor("Temperature")
		, m_himiditySensor("Himidity")
		, m_pressureSensor("Pressure")
		, m_windSpeedSensor("Wind speed")
	{}
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, std::string const& observableName) override
	{
		m_tempSensor.Update(data.temperature);
		m_himiditySensor.Update(data.humidity);
		m_pressureSensor.Update(data.pressure);
		m_windSpeedSensor.Update(data.windSpeed);
		m_windDirSensor.Update(data.windDirection);

		std::cout << std::endl << "Info from " << observableName << std::endl;
		m_tempSensor.Display();
		m_himiditySensor.Display();
		m_pressureSensor.Display();
		m_windSpeedSensor.Display();
		m_windDirSensor.Display();
		std::cout << std::endl;
	}

	CSensor m_tempSensor;
	CSensor m_himiditySensor;
	CSensor m_pressureSensor;
	CSensor m_windSpeedSensor;
	CWindDirSensor m_windDirSensor;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string const& name)
		: m_name(name)
	{}

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

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindDir() const
	{
		return m_windDir;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDir = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDir();
		return info;
	}

	std::string GetName() const override
	{
		return m_name;
	}

private:
	std::string m_name;

	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
	double m_windSpeed = 0.0;
	double m_windDir = 0.0;
};
