#include "Car.h"

Car::Car(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string model,
	std::string bodyType,
	std::string color,
	bool isRadio) :
	Toy("Car", price, sex, fromWhatAge, howMuchCanPlay, size, material),
	model(model), bodyType(bodyType), color(color), isRadio(isRadio)
{}

Car::Car() :Toy("Car")
{
	std::cout << "model = "; std::cin >> this->model;
	std::cout << "bodyType = "; std::cin >> this->bodyType;
	std::cout << "color = "; std::cin >> this->color;

	std::string isRadio_;
	std::cout << "isRadio = "; std::cin >> isRadio_;
	this->isRadio = isRadio_ == "true" ? true : false;
}

Car::Car(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string characteristics) :
	Toy("Car", price, sex, fromWhatAge, howMuchCanPlay, size, material)
{
	std::vector<std::string> car_characteristics = splitString_(characteristics, ',');
	this->model = car_characteristics[0];
	this->bodyType = car_characteristics[1];
	this->color = car_characteristics[2];
	this->isRadio = car_characteristics[3] == "true" ? true : false;
}