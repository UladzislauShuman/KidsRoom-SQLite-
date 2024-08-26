#include "Toy.h"

Toy::Toy(std::string typeName,
	int price,
	std::string sex,
	int fromWhatAge,
	int howMuchCanPlay,
	std::string size,
	std::string material) :
	typeName(typeName),
	price(price),
	sex(sex),
	fromWhatAge(fromWhatAge),
	howMuchCanPlay(howMuchCanPlay),
	size(size),
	material(material)
{}

Toy::Toy(std::string typeName_)
{
	this->typeName = typeName_;
	std::cout << "typeName = " << this->typeName << std::endl;
	std::cout << "price = "; std::cin >> this->price;
	std::cout << "gender = "; std::cin >> this->sex;
	std::cout << "fromWhatAge = "; std::cin >> this->fromWhatAge;
	std::cout << "howMuchCanPlay = "; std::cin >> this->howMuchCanPlay;
	std::cout << "size = "; std::cin >> this->size;
	std::cout << "material = "; std::cin >> this->material;
}