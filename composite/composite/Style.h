#pragma once
#include "CommonTypes.h"
#include <boost\optional.hpp>

class CStyle;
using OptionalStyle = boost::optional<CStyle>;

class CStyle
{
public:
	CStyle();

	bool IsEnabled()const;
	void Enable(bool enable);

	RGBAColor GetColor()const;
	void SetColor(RGBAColor color);

	friend bool operator==(const CStyle& left, const CStyle& right);
private:
	bool m_isEnable;
	RGBAColor m_color;
};