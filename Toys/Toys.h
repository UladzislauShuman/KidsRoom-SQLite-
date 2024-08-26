#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <memory>
#include <iterator>
#include <functional>
#include <sstream>
#include <cctype>

#include "Toy.h"
#include "Car.h"
#include "Ball.h"
#include "Doll.h"
#include "Cube.h"

#include "../Utils/Utils.h"

class Toys 
{
public:
	std::vector<std::shared_ptr<Toy>> info;
	~Toys() = default;
	Toys() = default;

	//Sort functions
	void SortByAge()
	{
		std::sort(info.begin(), info.end(),
			[](std::shared_ptr<Toy> a, std::shared_ptr<Toy> b)
			{
				return a->GetAge() < b->GetAge();
			});
	}

	void SortByPrice()
	{
		std::sort(info.begin(), info.end(),
			[](std::shared_ptr<Toy> a, std::shared_ptr<Toy> b)
			{
				return a->GetPrice() < b->GetPrice();
			});
	}

	void SortByHowMuchCanPlay()
	{
		std::sort(info.begin(), info.end(),
			[](std::shared_ptr<Toy> a, std::shared_ptr<Toy> b)
			{
				return a->GetHowMuchCanPlay() < b->GetHowMuchCanPlay();
			});
	}

	void SortByType()
	{
		std::sort(info.begin(),info.end(),
			[](std::shared_ptr<Toy> a, std::shared_ptr<Toy> b)
			{
				return a->GetTypeName() < b->GetTypeName();
			});
	}

	//я решил, что возращать объект будет
	//правильнее, тк тогда я не буду ничего внутри менять объекта
	//мне вроде как это не нужно, но при этом -- вернуть как константу
	
	Toys ChangeListByAge(int age)
	{
		this->SortByAge();
		if (age < this->info[0]->GetAge())
		{
			std::cout << "you are too young,bro" << std::endl;
			return *this;
		}
		if (age < 0) {
			std::cout << "man, you have not already borned" << std::endl;
			return *this;
		}
		Toys temp;
		int i = 0;
		while ((i < this->info.size()) and (this->info[i]->GetAge() <= age))
		{
			temp.info.push_back(this->info[i]);
			i++;
		}
		this->info = temp.info;
		return *this;
	}

	Toys ChangeListByType(std::string line)
	{
		Toys temp;
		this->SortByType();
		int amount;
		std::vector<std::string> typesList = splitString_(line, ' ');
		if (std::find(typesList.begin(),typesList.end(),"All") != typesList.end())
		{
			return *this;
		}
		for (int i = 0; i < typesList.size(); ++i) 
		{
			for (int j = 0; j < this->info.size(); ++j)
			{
				if (this->info[j]->GetTypeName() == typesList[i])
				{
					temp.info.push_back(this->info[j]);
					amount++;
				}
			}
		}
		return temp;
	}

	void Print(std::ostream& out) const
	{
		for (const auto& toy : this->info){
			std::shared_ptr<Toy> toy_(toy);
			out << toy_;
		}
	}

	void Read(std::istream& in)
	{
		std::string type;
		while (in >> type) 
		{
			std::shared_ptr<Toy> toy;
			std::unordered_map<std::string, std::function<void()>> types;
			types["Car"] = [&toy](){toy = std::make_shared<Car>();};
			types["Cube"] = [&toy](){toy = std::make_shared<Cube>();};
			types["Doll"] = [&toy](){toy = std::make_shared<Doll>();};
			types["Ball"] = [&toy](){toy = std::make_shared<Ball>();};
			auto it = types.find(type);
			if (it != types.end())
			{
				it->second();
			}
			else
			{
				std::cout << "No toy" << std::endl;
			}
			
			in >> toy;
			info.push_back(toy);
		}
	}
};

