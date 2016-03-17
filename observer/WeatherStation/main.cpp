#include "WeatherData.h"

int main()
{
	CWeatherData wd("outside stantion");

	CWeatherData wd1("inside stantion");


	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	CStatsDisplay statsDisplay1;
	wd.RegisterObserver(statsDisplay);
	wd1.RegisterObserver(statsDisplay);


	wd.SetMeasurements(3, 0.7, 760);
	wd1.SetMeasurements(5, 0.76, 740);

	wd.SetMeasurements(4, 0.8, 761);
	wd1.SetMeasurements(11, 0.4, 780);

	wd.RemoveObserver(statsDisplay);
	wd1.RemoveObserver(statsDisplay1);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}