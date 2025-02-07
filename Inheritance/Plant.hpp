#pragma once

#ifndef PLANT_HPP
#define PLANT_HPP

#include <iostream>
#include <string>
#include <random>

#include "Harvest.hpp"


class Plant {
public:
	Plant();
	Plant(std::string name,double height, Harvest prot)
		:name_(name),
		height_(height),
		prototype_(prot)
	{
		static std::mt19937 gen{ std::random_device()() };
		static std::uniform_int_distribution<int> provider(10, 99);
		harvest_ = provider(gen);
	}

	virtual ~Plant() = default;

	virtual Harvest *DoHarvest();


private:
	std::string name_;
	double height_;
	int harvest_;
	Harvest prototype_;
};


#endif // !PLANT_HPP

