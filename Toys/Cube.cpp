#include "Cube.h"

Cube::Cube(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	int amount,
	std::string color,
	bool isPuzzle) :
	Toy("Cube", price, sex, fromWhatAge, howMuchCanPlay, size, material),
	amount(amount), color(color), isPuzzle(isPuzzle)
{}

Cube::Cube() :Toy("Cube")
{
	std::cout << "amount = "; std::cin >> this->amount;
	std::cout << "color = "; std::cin >> this->color;

	std::string isPuzzle_;
	std::cout << "isPuzzle = "; std::cin >> isPuzzle_;
	this->isPuzzle = isPuzzle_ == "true" ? true : false;
}

Cube::Cube(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string characteristics) :
	Toy("Cube", price, sex, fromWhatAge, howMuchCanPlay, size, material)
{
	std::vector<std::string> cube_characteristics = splitString_(characteristics, ',');
	this->amount = std::stoi(cube_characteristics[0]);
	this->color = cube_characteristics[1];
	this->isPuzzle = (bool)(cube_characteristics[2] == "true" ? true : false);
}