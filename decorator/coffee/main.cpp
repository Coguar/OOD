#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [] (IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Функция, которая возвращает функцию, конструирующую произвольную добавку.
Аргументы функции MakeCondiment захватываются возвращаемой функцией и передаются
конструктору указанной добавки следом за декорируемым напитком

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - типы прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
function<unique_ptr<Condiment>(IBeveragePtr&&)> MakeCondiment(const Args&...args)
{
	// Возвращаем унарную функцию, создающую и возвращающую декоратор, оборачивающий
	// напиток, переданный ей в качестве аргумента
	return [=](IBeveragePtr && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(move(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для оборачивания напитка декоратором.

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage = 
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage = 
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

IBeveragePtr operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
IBeveragePtr operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename CondimentFactory>
IBeveragePtr operator << (IBeveragePtr && lhs, const CondimentFactory & factory)
{
	return factory(move(lhs));
}


int main()
{
	{
		// Наливаем чашечку латте
		auto latte = make_unique<CLatte>(CoffeType::Double);
		// добавляем корицы
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage =
			make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
				make_unique<CIceCubes>(				//   под нею - кубики льда
					make_unique<CLemon>(			//	   еще ниже лимон
						make_unique<CCinnamon>(		//       слоем ниже - корица
							make_unique<CLatte>(CoffeType::Classic)),	//         в самом сердце - Латте
						2),							//     2 дольки лимона
					2, IceCubeType::Dry),			//   2 кубика сухого льда
				2);									// 2 грамма шоколадной крошки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// Аналог предыдущего решения с добавкой синтаксического сахара
	// обеспечиваемого операторами << и функцией MakeCondiment
	{
		auto beverage =
			make_unique<CLatte>(CoffeType::Double)			// Наливаем чашечку латте,
			<< MakeCondiment<CCinnamon>()					// оборачиваем корицей,
			<< MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
			<< MakeCondiment<CChocolateCrumbs>(2)			// посыпаем шоколадной крошкой
			<< MakeCondiment<CChocolateSlices>(12)			// заказываем шоколадки	
			<< MakeCondiment<CLiquor>(LiquorType::Nuts)		// добавляем ликер	
			<< MakeCondiment<CCream>();						// сливки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = 
			make_unique<CMilkshake>(MilkShakeVolume::Big)// Наливаем молочный коктейль
			<< MakeCondiment<CSyrup>(SyrupType::Chocolate)	// заливаем кленовым сиропом
			<< MakeCondiment<CCoconutFlakes>(100);		// посыпаем кокосовой стружкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}
}
