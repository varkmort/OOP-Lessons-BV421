#pragma once

#ifndef HARVEST_HPP
#define HARVEST_HPP

#include <iostream>
#include <string>

class Harvest {
public:
	Harvest(std::string name,double volume, double weigth)
		:name_(name),
		volume_(volume),
		weigth_(weigth)
	{}

	virtual ~Harvest() = default;

	// така€ реализаци€ с разделением объ€влени€ и определени€ 
	// лишает метод класса статуса inline функции
	double Volume()const;

	// реализаци€ метода с одновренменным определением и объ€влением
	// оставл€ет такой метод как inline функцию дл€ программы
	double Weigth()const { return weigth_; }

	std::string Name()const;

	friend std::ostream &operator<<(std::ostream &out, const Harvest &obj);

private:
	std::string name_;
	double		volume_;
	double		weigth_;
};



#endif // !HARVEST_HPP

