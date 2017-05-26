#pragma once
#include <cstdint>
#include <limits>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

static const RectD UndefinedRectD = RectD({
		std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity() });