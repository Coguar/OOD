#include "WeatherData.h"
#include <memory>
int main()
{
	CWeatherData wd("outside stantion");

	CWeatherData wd1("inside stantion");


	std::shared_ptr<CDisplay> display = std::make_shared<CDisplay>();
	wd.RegisterObserver(*display, 1);

	std::shared_ptr<CStatsDisplay> statsDisplay = std::make_shared<CStatsDisplay>();

	wd.RegisterObserver(*statsDisplay, 3);
	wd1.RegisterObserver(*statsDisplay, 2);


	wd.SetMeasurements(3, 0.7, 760);
	wd1.SetMeasurements(5, 0.76, 740);

	wd.SetMeasurements(4, 0.8, 761);
	wd1.SetMeasurements(11, 0.4, 780);

	wd.RemoveObserver(*statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}