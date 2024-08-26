#pragma once
//#include "All.h"

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


class Toy
{
private:
	char typeLetter;
	std::string typeName;
	int price;
	std::string sex;
	int fromWhatAge;
	int howMuchCanPlay;
	std::string size;
	std::string material;
public:
	virtual ~Toy() = default;
	Toy() = default;
	Toy(std::string);
	Toy(std::string typeName,
		int price,
		std::string sex,
		int fromWhatAge,
		int howMuchCanPlay,
		std::string size,
		std::string material);
		
	[[nodiscard]] int GetAge() const { return this->fromWhatAge;}
	[[nodiscard]] int GetPrice() const { return this->price;}
	[[nodiscard]] int GetHowMuchCanPlay() const { return this->howMuchCanPlay; }
	[[nodiscard]] std::string GetTypeName() const { return this->typeName; }
	[[nodiscard]] std::string GetSize() const { return this->size;}
	[[nodiscard]] std::string GetGender() const {return this->sex;}
	[[nodiscard]] std::string GetMaterial() const {return this->material;}
	virtual std::string GetCharacteristics() const {return "No characteristics";}

	void SetTypeLetter(char& type) { this->typeLetter = type; }

	virtual std::ostream& Print(std::ostream& out) const
	{
		out << "typeName: " << typeName
			<< ", price: " << price <<" BYN"
			<< ", sex: " << sex
			<< ", from what age:" << fromWhatAge
			<< ", how much can play: " << (howMuchCanPlay >= 0? std::to_string(howMuchCanPlay):"it's doesn't matter")
			<< ", size: " << size
			<< ", material: " << material;
		return out;
	}

	virtual std::istream& Read(std::istream& in)
	{
		in >>typeName >> price >> sex >> fromWhatAge >> howMuchCanPlay >> size >> material;
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out,
		std::shared_ptr<Toy> toy)
	{
		toy->Print(out);
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in,
		std::shared_ptr<Toy> toy)
	{
		toy->Read(in);
		return in;
	}
};
