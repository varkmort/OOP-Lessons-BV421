#include "Plant.hpp"


Plant::Plant():Plant("Apple",7.1,Harvest("Pear",0.11,0.11))
{}

Harvest * Plant::DoHarvest()
{
	if (harvest_ > 0) {
		harvest_ -= 1;
		return new Harvest(prototype_);
	}
	else {
		return nullptr;
	}
}
