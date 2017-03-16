#pragma once

enum Color
{
	Green = 0,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
};

static const std::map<std::string, Color> COLOR_LIST = {
	{"red", Color::Red},
	{"green", Color::Green},
	{"blue", Color::Blue},
	{"yellow", Color::Yellow},
	{"pink", Color::Pink},
	{"black", Color::Black},
};

static const std::map<Color, std::string> STR_COLOR_LIST = {
	{ Color::Red, "red" },
	{ Color::Green, "Green" },
	{ Color::Blue, "Blue" },
	{ Color::Yellow, "Yellow" },
	{ Color::Pink, "Pink" },
	{ Color::Black, "Black" },
};