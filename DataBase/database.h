#pragma once
//#include "../All.h"
#include "../sqlite3/sqlite3.h"
#include "../Utils/Utils.h"


#include <typeinfo>
#include <cstdlib>
//#include <cxxabi.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

class DataBase
{
    public:
        DataBase(const std::string);
        ~DataBase();

        template<class T> bool IsInDB(const T&) const;
        template<class T> void AddItem(const T&) const;
        template<class T> void DropItem(const T& item, const int limit = 1) const;
        template<class T> std::vector<T> GetItems(const std::string where = "TRUE",const std::string order_by = "id, toy_type") const;

        Toys GetToys() const;

        void PrintSorted(const std::string order_by) const;
        void Select(const std::string tables,
                    std::string where = "TRUE",
                    std::string order_by = "id") const;
        std::string make_from(const std::string) const;
    private:
        std::string path;
        int GetMaxId(const std::string) const;
        static std::vector<std::string> all_tables;
};

template<class T> bool DataBase::IsInDB(const T& item) const
{
    if constexpr (!std::is_base_of_v<Toy, T>)
    {
        std::cout << "item has incorrect type" << std::endl;
        return false;
    }
    else
    {
        sqlite3* db;
        std::string type = item.GetTypeName();

        if (sqlite3_open(this->path.data(), &db))
        {
            std::cout << "IsInDB (" << type << ") : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return false;
        }
        // в С++20 есть функция std::lower, но тк проект пока написан на C++17
        // то извините
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) {return std::tolower(c); });
        std::stringstream request;
        request << "SELECT COUNT(*) FROM " << type << "s WHERE toy_type = " << "\"" << item.GetTypeName() << "\"" << " AND "
            << "price = " << item.GetPrice() << " AND "
            << "gender = " << "\"" << item.GetGender() << "\"" << " AND "
            << "age = " << item.GetAge() << " AND "
            << "how_much_can_play = " << item.GetHowMuchCanPlay() << " AND "
            << "size = " << "\"" << item.GetSize() << "\"" << " AND "
            << "material = " << "\"" << item.GetMaterial() << "\"" << " AND "
            << type << "_characteristics = " << "\"" << item.GetCharacteristics() << "\"";

        sqlite3_stmt* result;
        if (sqlite3_prepare_v2(db, request.str().data(), -1, &result, nullptr)) {
            std::cout << "IsInDB (prepare): " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return false;
        }

        if (sqlite3_step(result) == SQLITE_ROW)
        {
            int price = sqlite3_column_int(result, 0);
            sqlite3_finalize(result);
            sqlite3_close(db);
            if (price > 0)
                return true;
            else
                return false;
        }
        else
        {
            std::cout << "IsInDB : no data" << std::endl;
            sqlite3_finalize(result);
            sqlite3_close(db);
            return false;
        }
        sqlite3_close(db);
        return false;
    }
    return false;
}
template<class T> void DataBase::AddItem(const T& item) const
{
    if constexpr (!std::is_base_of_v<Toy, T>)
    {
        std::cout << "item has incorrect type" << std::endl;
        return;
    }
    else {
        sqlite3* db;
        std::string type = item.GetTypeName();
        // в С++20 есть функция std::lower, но тк проект пока написан на C++17
        // то извините
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) {return std::tolower(c); });

        if (sqlite3_open(this->path.data(), &db) != SQLITE_OK)
        {
            std::cout << "AddItem " + type + " : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        std::stringstream ss;
        ss << "INSERT INTO " + type + "s VALUES ("
            << this->GetMaxId(type + "s") + 1 << ", "
            << "\"" << item.GetTypeName() << "\""
            << ", " << item.GetPrice() << ", " << "\"" << item.GetGender() << "\""
            << ", " << item.GetAge() << ", " << item.GetHowMuchCanPlay()
            << ", " << "\"" << item.GetSize() << "\"" << ", " << "\"" << item.GetMaterial() << "\""
            << ", \"" << item.GetCharacteristics() << "\");";
        char* errmsg = 0;
        if (sqlite3_exec(db, ss.str().data(), NULL, NULL, &errmsg))
        {
            std::cout << "AddItem " + type + " (SQL error) : " << errmsg << std::endl;
            sqlite3_free(errmsg);
            sqlite3_close(db);
            return;
        }
        sqlite3_close(db);
    }
}
template<class T> void DataBase::DropItem(const T& item, int limit) const
{
    if constexpr (!std::is_base_of_v<Toy, T>)
    {
        std::cout << "item has incorrect type" << std::endl;
        return;
    }
    else
    {
        sqlite3* db = nullptr;
        if (!this->IsInDB(item))
        {
            std::cout << "not in database" << std::endl;
            sqlite3_close(db);
            return;
        }
        std::string type = item.GetTypeName();

        if (sqlite3_open(this->path.data(), &db))
        {
            std::cout << "DropItem (" << type << ") : " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        // в С++20 есть функция std::lower, но тк проект пока написан на C++17
        // то извините
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) {return std::tolower(c); });

        std::stringstream ss;
        ss << "DELETE FROM " << type << "s WHERE "
            << "toy_type = " << "\"" << item.GetTypeName() << "\"" << " AND "
            << "price = " << item.GetPrice() << " AND "
            << "gender = " << "\"" << item.GetGender() << "\"" << " AND "
            << "age = " << item.GetAge() << " AND "
            << "how_much_can_play = " << item.GetHowMuchCanPlay() << " AND "
            << "size = " << "\"" << item.GetSize() << "\"" << " AND "
            << "material = " << "\"" << item.GetMaterial() << "\"" << " AND "
            << type << "_characteristics = " << "\"" << item.GetCharacteristics() << "\""
            << " LIMIT " << limit << ";";

        char* err;
        if (sqlite3_exec(db, ss.str().data(), NULL, NULL, &err) != SQLITE_OK)
        {
            std::cout << "DropItem (request) : " << err << std::endl;
            sqlite3_free(err);
            sqlite3_close(db);
            return;
        }
        sqlite3_close(db);
        std::cout << "was deleted" << std::endl;
    }
}
template<class T> std::vector<T> DataBase::GetItems(const std::string where, const std::string order_by) const
{
    std::vector<T> Items{};
    if constexpr (!std::is_base_of_v<Toy, T>)
    {
        std::cout << "item has incorrect type" << std::endl;
        return Items;
    }
    else
    {
        sqlite3* db;
        std::string type = obj_type<T>();
        // в С++20 есть функция std::lower, но тк проект пока написан на C++17
        // то извините
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) {return std::tolower(c); });

        const std::string request =
            "SELECT * "
            " FROM " + type + "s"
            " WHERE " + where +
            " ORDER BY " + order_by;

        sqlite3_stmt* result;
        sqlite3_open(this->path.data(), &db);
        if (sqlite3_prepare_v2(db, request.data(), -1, &result, nullptr))
        {
            std::cout << "GetItems error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return Items;
        }
        while (sqlite3_step(result) == SQLITE_ROW)
        {
            std::string typeName = reinterpret_cast<const char*>(sqlite3_column_text(result, 1));
            int price = sqlite3_column_int(result, 2);
            std::string sex = reinterpret_cast<const char*>(sqlite3_column_text(result, 3));
            int fromWhatAge = sqlite3_column_int(result, 4);
            int howMuchCanPlay = sqlite3_column_int(result, 5);
            std::string size = reinterpret_cast<const char*>(sqlite3_column_text(result, 6));
            std::string material = reinterpret_cast<const char*>(sqlite3_column_text(result, 7));
            std::string characteristics = reinterpret_cast<const char*>(sqlite3_column_text(result, 8));

            T tempItem(price, sex, fromWhatAge, howMuchCanPlay, size, material, characteristics);
            Items.push_back(tempItem);
        }
        sqlite3_finalize(result);
        return Items;
    }
}