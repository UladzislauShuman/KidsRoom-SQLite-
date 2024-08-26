#pragma once
//#include "sqlite3/sqlite3.h"
#include "../DataBase/database.h"
//#include "../All.h"
#include <map>
#include "../sqlite3/sqlite3.h"
#include "../Utils/Utils.h"


#include <typeinfo>
#include <cstdlib>
//#include <cxxabi.h>

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
#include "../Toys/Toy.h"

#include "../Toys/Car.h"
#include "../Toys/Ball.h"
#include "../Toys/Doll.h"
#include "../Toys/Cube.h"

#include "../Toys/Toys.h"

#include "../Toys/ToysRoom.h"

class UserInterface
{
public:
    UserInterface(const std::string path):db(DataBase(path)){}
    UserInterface(const DataBase db_) : db(db_){}
    ~UserInterface() = default;

    void show() const;
private:
    void Add() const;

    void AddCube() const;
    void AddCar() const;
    void AddDoll() const;
    void AddBall() const;

    std::map<std::string, std::function<void(void)>> add = {
        {"Cube", std::bind(&UserInterface::AddCube, this)},
        {"Car", std::bind(&UserInterface::AddCar, this)},
        {"Doll", std::bind(&UserInterface::AddDoll, this)},
        {"Ball", std::bind(&UserInterface::AddBall, this)}
    };
private:
    void Drop() const;
    
    void DropCube() const;
    void DropCar() const;
    void DropDoll() const;
    void DropBall() const;

    std::map<std::string, std::function<void(void)>> drop = {
        {"Cube", std::bind(&UserInterface::DropCube, this)},
        {"Car", std::bind(&UserInterface::DropCar, this)},
        {"Doll", std::bind(&UserInterface::DropDoll, this)},
        {"Ball", std::bind(&UserInterface::DropBall, this)}
    };
private:
    void Select() const;
private:
    DataBase db;
};
