#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <iterator>
#include <sstream>
#include "Toy.h"

#include "../Utils/Utils.h"
class Car:public Toy
{
private:
	std::string model;
	std::string bodyType;
	std::string color;
	bool isRadio;
public:
	Car();
	Car(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string model,
		std::string bodyType,
		std::string color,
		bool isRadio);
	Car(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string characteristics);
	~Car() override = default;

	virtual std::string GetCharacteristics() const override
	{
		std::stringstream ss;
		ss  << this->model << ", "
			<< this->bodyType << ", "
			<< this->color << ", "
			<< this->isRadio? "true" : "false";
		return ss.str();
	}
	virtual std::ostream& Print(std::ostream& out) const override
	{
		Toy::Print(out);
		out << "model: " << model
			<< ", bodyType: " << bodyType
			<< ", color: " << color
			<< ", isRadio: " << (isRadio ? "true" : "false")
			<< std::endl;
		return out;
	}

	virtual std::istream& Read(std::istream& in) override
	{
		Toy::Read(in);
		in >> model >> bodyType >> color >> isRadio;
		return in;
	}
};
