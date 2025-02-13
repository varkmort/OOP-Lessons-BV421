#pragma once


#include "Plant.hpp"

class AppleTree:public Plant {
public:

	Harvest * DoHarvest()override;
};