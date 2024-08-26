#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <iterator>
#include <variant>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <cctype>
#include <type_traits>
#include "Toy.h"

#include "../Utils/Utils.h"
class Doll :public Toy
{
private:
	std::string sobriquet;
	bool isMale;
	bool isHuman;
public:
	Doll();
	Doll(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string sobriquet,
		bool isMale,
		bool isHuman);
	Doll(
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material,
		
		std::string characteristics);
	~Doll() override = default;

	virtual std::string GetCharacteristics() const override
	{
		std::stringstream ss;
		ss  << this->sobriquet << ", "
			<< (this->isMale ? "true" : "false") << ", "
			<< this->isHuman ? "true" : "false";
		return ss.str();
	}
	
	virtual std::ostream& Print(std::ostream& out) const override
	{
		Toy::Print(out);
		out << ", sobriquet: " << sobriquet
			<< ", " << (isMale ? "Male" : "Female")
			<< ", " << (isHuman ? "human" : "no human") 
			<< std::endl;
		return out;
	}

	virtual std::istream& Read(std::istream& in) override
	{
		Toy::Read(in);
		in >> sobriquet >> isMale >> isHuman;
		return in;
	}

};

