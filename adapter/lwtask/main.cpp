#include "stdafx.h"
#include "AppFunc.h"
#include "AppFuncPro.h"

using namespace std;

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app_pro::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app_pro::PaintPictureOnCanvas();
	}
	return 0;
}
