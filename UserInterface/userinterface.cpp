#include "userinterface.h"

void UserInterface::show() const
{
    std::cout << "what do you want to do?" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Add\nDrop\nSelect\n";
    std::cout << "-----------------------" << std::endl;
    std::string choice;
    std::cout << "your choice : ";
    std::cin >> choice;

    if (choice == "Add")
    {
        this->Add();
    }
    else if (choice == "Drop")
    {
        this->Drop();
    }
    else if (choice == "Select")
    {
        this->Select();
    }
    else
    {
        std::cout << "incorrect choice\n(you can write only\n Add, Drop, Select)" << std::endl;
        this->show();
    }
}

void UserInterface::Add() const
{
    std::cout << "whar do you want to add?" << std::endl;
    std::cout << "what we have:\nCube\nCar\nBall\nDoll\n";
    std::cout << ">> ";
    std::string typeName;
    std::cin >> typeName;

    if (this->add.find(typeName) != add.end())
    {
        (add.find(typeName)->second)();
    }
    else
    {
        std::cout << "incorrect typeName\n(you can write only\n Car, Cube, Doll, Ball)" << std::endl;
        this->Add();
    }
    this->show();
}

void UserInterface::AddCube() const
{
    Cube cube = Cube();
    this->db.AddItem(cube);
}
void UserInterface::AddCar() const
{
    Car car = Car();
    this->db.AddItem(car);
}
void UserInterface::AddDoll() const
{
    Doll doll = Doll();
    this->db.AddItem(doll);
}
void UserInterface::AddBall() const
{
    Ball ball = Ball();
    this->db.AddItem(ball);
}

void UserInterface::Drop() const
{
    std::cout << "whar do you want to drop?" << std::endl;
    std::cout << "what we have:\nCube\nCar\nBall\nDoll\n";
    std::cout << "typeName = : ";
    std::string typeName;
    std::cin >> typeName;

    if (this->drop.find(typeName) != drop.end())
    {
        std::cout << "Do you want to see a list of " << typeName << " ?(yes/no)" << std::endl;
        std::string ans; std::cin >> ans;
        if (ans == "yes")
        {
            std::string type = typeName;
            std::transform(type.begin(), type.end(), type.begin(),
                [](unsigned char c) {return std::tolower(c); });
            type += "s";
            this->db.Select(type);
        }
        (drop.find(typeName)->second)();
    }
    else
    {
        std::cout << "incorrect typeName\n(you can write only\n Car, Cube, Doll, Ball)" << std::endl;
        this->Drop();
    }
    this->show();
}

void UserInterface::DropCube() const
{
    Cube cube = Cube();
    this->db.DropItem(cube, 1);
}
void UserInterface::DropCar() const
{
    Car car = Car();
    this->db.DropItem(car, 1);
}
void UserInterface::DropDoll() const
{
    Doll doll = Doll();
    this->db.DropItem(doll, 1);
}
void UserInterface::DropBall() const
{
    Ball ball = Ball();
    this->db.DropItem(ball, 1);
}

void UserInterface::Select() const
{
    std::cout << "write names of tables separated by commas" << std::endl;
    std::cin.ignore();
    std::string tables;
    std::getline(std::cin, tables);

    std::cout << "where " << std::endl;
    std::string where;
    std::getline(std::cin, where);

    std::cout << "order by " << std::endl;
    std::string order_by;
    std::getline(std::cin, order_by);

    this->db.Select(tables, where, order_by);
    this->show();
}