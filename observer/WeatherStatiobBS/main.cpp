// WeatherStatiobBS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData wd("FirstRussianWD");

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 3, 270);
	wd.SetMeasurements(4, 0.8, 761, 4, 90);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 4, 180);
	wd.SetMeasurements(-10, 0.8, 761, 4, 220);
	return 0;
}

