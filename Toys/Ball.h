#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <iterator>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <type_traits>
#include "Toy.h"

#include "../Utils/Utils.h"


class Ball : public Toy
{
private:
	std::string type;
	int sizeType;
	std::string color;
public:
	Ball();
	Ball(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string type,
		int sizeType,
		std::string color);
	Ball(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string characteristics);
	~Ball() override = default;

	virtual std::string GetCharacteristics() const override
	{
		std::stringstream ss;
		ss  << this->type << ", "
			<< this->sizeType << ", "
			<< this->color;
		return ss.str();
	}

	virtual std::ostream& Print(std::ostream& out) const override
	{
		Toy::Print(out);
		out << "type:" << type
			<< ", sizeType: " << sizeType
			<< ", color: " << color
			<< std::endl;
		return out;
	}

	virtual std::istream& Read(std::istream& in) override
	{
		Toy::Read(in);
		in >> type >> sizeType >> color;
		return in;
	}
};
