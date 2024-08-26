#include "Ball.h"

Ball::Ball(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,

	std::string type,
	int sizeType,
	std::string color) :
	Toy("Ball", price, sex, fromWhatAge, howMuchCanPlay, size, material),
	type(type), sizeType(sizeType), color(color)
{}

Ball::Ball() :Toy("Ball")
{
	std::cout << "type = "; std::cin >> this->type;
	std::cout << "sizeType = "; std::cin >> this->sizeType;
	std::cout << "color = "; std::cin >> this->color;
}

Ball::Ball(
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material,
	std::string characteristics) :
	Toy("Ball", price, sex, fromWhatAge, howMuchCanPlay, size, material)
{
	std::vector<std::string> ball_characteristics = splitString_(characteristics, ',');
	this->type = ball_characteristics[0];
	this->sizeType = std::stoi(ball_characteristics[1]);
	this->color = ball_characteristics[2];
}