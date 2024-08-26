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

class Cube : public Toy
{
private:
	int amount;
	std::string color;
	bool isPuzzle;
public:
	Cube();
	Cube(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		int amount,
		std::string color,
		bool isPuzzle);
	Cube(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string characteristics
	);
	~Cube() override = default;
	
	virtual std::string GetCharacteristics() const override
	{
		std::stringstream ss;
		ss  << this->amount << ", "
			<< this->color << ", "
			<< this->isPuzzle ? "true" : "false";
		return ss.str();
	}

	virtual std::ostream& Print(std::ostream& out) const override
	{
		Toy::Print(out);
		out << ", amount: "<< amount
			<< ", color: " << color
			<< (isPuzzle ? ", Puzzle" : ", not Puzzle")
			<< std::endl;
		return out;
	}

	virtual std::istream& Read(std::istream& in) override
	{
		Toy::Read(in);
		in >> amount >> color >> isPuzzle;
		return in;
	}
};
