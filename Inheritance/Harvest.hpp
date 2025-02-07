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

	// ����� ���������� � ����������� ���������� � ����������� 
	// ������ ����� ������ ������� inline �������
	double Volume()const;

	// ���������� ������ � �������������� ������������ � �����������
	// ��������� ����� ����� ��� inline ������� ��� ���������
	double Weigth()const { return weigth_; }

	std::string Name()const;

	friend std::ostream &operator<<(std::ostream &out, const Harvest &obj);

private:
	std::string name_;
	double		volume_;
	double		weigth_;
};



#endif // !HARVEST_HPP

