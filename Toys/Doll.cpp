#include "Doll.h"

Doll::Doll(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string sobriquet,
	bool isMale,
	bool isHuman) :
	Toy("Doll", price, sex, fromWhatAge, howMuchCanPlay, size, material),
	sobriquet(sobriquet), isMale(isMale), isHuman(isHuman)
{}

Doll::Doll() :Toy("Doll")
{
	std::cout << "sobriquet = "; std::cin >> this->sobriquet;

	std::string isMale_;
	std::cout << "isMale = "; std::cin >> isMale_;
	this->isMale = isMale_ == "true" ? true : false;

	std::string isHuman_;
	std::cout << "isHuman = "; std::cin >> isHuman_;
	this->isHuman = isHuman_ == "true" ? true : false;
}

Doll::Doll(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string characteristics) :
	Toy("Doll", price, sex, fromWhatAge, howMuchCanPlay, size, material)
{
	std::vector<std::string> doll_characteristics = splitString_(characteristics, ',');
	this->sobriquet = doll_characteristics[0];
	this->isMale = doll_characteristics[1] == "true" ? true : false;
	this->isHuman = doll_characteristics[2] == "true" ? true : false;
}