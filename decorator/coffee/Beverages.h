#pragma once

#include "IBeverage.h"
#include <cassert>
#include <map>

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

enum class CoffeType
{
	Double,
	Classic,
};
// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeType typeOfCoffe)
		:CCoffee(typeOfCoffe == CoffeType::Classic ? "Capuccino" : "DoubleCapuccino"),
		m_coffeType(typeOfCoffe)
	{}

	double GetCost() const override 
	{
		return m_coffeType == CoffeType::Classic ? 80 : 120;
	}

private:
	CoffeType m_coffeType;
};


// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeType typeOfCoffe)
		:CCoffee(typeOfCoffe == CoffeType::Classic ? "Latte" : "DoubleLatte"),
		m_coffeType(typeOfCoffe)
	{}

	double GetCost() const override 
	{
		return m_coffeType == CoffeType::Classic ? 90 : 130;
	}

private:
	CoffeType m_coffeType;
};

// Сорт чая
enum class TeaSort
{
	Black,
	Green,
	Red,
	White,
};

const std::map<TeaSort, std::string> TeaMap = {
	{ TeaSort::Black, "Black"}, 
	{ TeaSort::Green, "Green" },
	{ TeaSort::Red, "Red" },
	{ TeaSort::White, "White" }
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaSort sortOfTea)
		:CBeverage(TeaMap.find(sortOfTea)->second + "Tea")
	{
	}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Объем коктеля
enum class MilkShakeVolume
{
	Big,
	Middle,
	Small,

};

const std::map<MilkShakeVolume, std::string> VolumeMap = {
	{ MilkShakeVolume::Big, "Big" },
	{ MilkShakeVolume::Middle, "Middle" },
	{ MilkShakeVolume::Small, "Small" },
};


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkShakeVolume volume)
		:CBeverage(VolumeMap.find(volume)->second + "Milkshake"),
		m_volume(volume)
	{
	}

	double GetCost() const override 
	{ 
		switch (m_volume)
		{
		case MilkShakeVolume::Small: return 50;
		case MilkShakeVolume::Middle: return 60;
		case MilkShakeVolume::Big: return 80;
		}
	}
private:
	MilkShakeVolume m_volume;
};
