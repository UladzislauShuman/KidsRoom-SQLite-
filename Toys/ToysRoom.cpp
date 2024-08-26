#include "ToysRoom.h"

void ToysRoom::createRoom(Toys& list)
{
	this->toys = list.info;
}

void ToysRoom::createByPrice(double maxPrice, Toys& toy)
{
	bool flag = true;
	toy.SortByPrice();
	if (maxPrice < toy.info[0]->GetPrice()) {
		std::cout << "that's not enough" << std::endl;
		return;
	}
	while (maxPrice > 0 && flag)
	{
		std::for_each(toy.info.begin(), toy.info.end(), [&maxPrice, &flag, this, toy]
		(std::shared_ptr<Toy> toy_)
			{
				if (toy_->GetPrice() <= maxPrice)
				{
					maxPrice -= toy_->GetPrice();
					this->toysCost += toy_->GetPrice();
					this->toys.push_back(toy_);
				}
				else if (maxPrice < toy.info.back()->GetPrice()) {
					flag = false;
				}
			});
	}
}

void ToysRoom::createByPriceAndAge(double maxPrice,double maxAge, Toys& toy)
{
	bool flag = true;
	toy.SortByPrice();
	while (maxPrice > 0 && flag)
	{
		std::for_each(toy.info.begin(), toy.info.end(), [&maxAge,&maxPrice, &flag, this, toy]
		(std::shared_ptr<Toy> toy_)
			{
				if (toy_->GetPrice() <= maxPrice and toy_->GetAge() <= maxAge)
				{
					maxPrice -= toy_->GetPrice();
					this->toysCost += toy_->GetPrice();
					this->toys.push_back(toy_);
				}
				//forget about age
				else if (maxPrice < toy.info.back()->GetPrice()) {
					flag = false;
				}
			});
	}
}

