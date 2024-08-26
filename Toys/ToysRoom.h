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
#include "Car.h"
#include "Ball.h"
#include "Doll.h"
#include "Cube.h"
#include "Toys.h"

class ToysRoom
{
public:
	std::vector<std::shared_ptr<Toy>> toys;
	double toysCost;

	ToysRoom() = default;
	~ToysRoom() = default;

	[[nodiscard]] double GetCost()
	{
		return toysCost;
	}
	void createRoom(Toys& list);
	void createByPrice(double maxPrice, Toys& toy);
	void createByPriceAndAge(double maxPrice, double maxAge, Toys& toy);
	//void createByType(std::string line, Toys& base);
	
	void Print(std::ostream& out)
	{
		for (const auto& toy : this->toys){
			std::shared_ptr<Toy> toy_(toy);
			out << toy_;
		}
	}

};

