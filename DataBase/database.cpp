#include "database.h"

std::vector<std::string> DataBase::all_tables = { "cubes", "cars", "dolls", "balls" };

DataBase::~DataBase()
{
    sqlite3* db = nullptr;
    if (db != nullptr) {
        sqlite3_close(db);
    }
}
DataBase::DataBase(const std::string path_):path(path_)
{
    sqlite3* db;
    if (sqlite3_open(this->path.data(),&db) != SQLITE_OK) {
        std::cout << "problems" << std::endl;
        return;
    }
    sqlite3_close(db);
}

Toys DataBase::GetToys() const
{
    Toys toys;
    
    auto addToy = [&toys](const auto& toy) 
    {
        using T = std::decay_t<decltype(toy)>;
        toys.info.push_back(std::make_shared<T>(std::move(toy)));
    };

    for (const auto& car: this->GetItems<Car>()) {addToy(car);}
    for (const auto& ball: this->GetItems<Ball>()) {addToy(ball);}
    for (const auto& cube: this->GetItems<Cube>()) {addToy(cube);}
    for (const auto& doll: this->GetItems<Doll>()) {addToy(doll);}

    return toys;
}

void DataBase::PrintSorted(const std::string order_by) const
{
    sqlite3* db;
    std::string request = 
    "SELECT * FROM cubes " 
    "UNION ALL " 
    "SELECT * FROM cars " 
    "UNION ALL "
    "SELECT * FROM dolls "
    "UNION ALL "
    "SELECT * FROM balls " 
    "ORDER BY " + order_by
    ;

    sqlite3_stmt* result;
    sqlite3_open(this->path.data(),&db);
    if (sqlite3_prepare_v2(db,request.data(),-1,&result,nullptr)){
        std::cout << "GetCubes error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(result) == SQLITE_ROW)
    {
        std::cout   << reinterpret_cast<const char*>(sqlite3_column_text(result, 1)) << " " //std::string typeName 
                    << sqlite3_column_int(result, 2) << " " //int price
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 3)) << " " //std::string sex
                    << sqlite3_column_int(result, 4) << " " //int fromWhatAge
                    << sqlite3_column_int(result, 5) << " " //int howMuchCanPlay
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 6)) << " " //std::string size
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 7)) << " " // std::string material
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 8)) << " " //std::string characteristic 
                    << std::endl;
    }
    sqlite3_finalize(result);
    sqlite3_close(db);
    return;
}
/*
почему всё же не по ссылке?
*/
int DataBase::GetMaxId(const std::string table) const
{
    sqlite3* db;
    if (sqlite3_open(this->path.data(),&db) != SQLITE_OK)
    {
        std::cout << "GetMaxId (open): " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    const std::string request = 
    "SELECT MAX(id) "
    "FROM " + table;

    sqlite3_stmt* result;
    if(sqlite3_prepare_v2(db,request.data(),-1,&result,nullptr))
    {
        std::cout << "GetMaxId (prepare): " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }
    int ans = 0;
    if (sqlite3_step(result) == SQLITE_ROW)
    {
        ans = sqlite3_column_int(result, 0);
    }
    else {
        std::cout << "GetMaxId (table)" << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(result);
    return ans;
}

std::string DataBase::make_from(const std::string tables) const
{
    std::string str_intersection{};
    std::vector<std::string> tables_ = splitString_(tables, ',');
    
    std::sort(this->all_tables.begin(),this->all_tables.end());
    std::sort(tables_.begin(),tables_.end());

    std::vector<std::string> vec_intersection;
    std::set_intersection(this->all_tables.begin(), this->all_tables.end(),
                            tables_.begin(),tables_.end(),
                            std::back_inserter(vec_intersection));
    std::ostringstream oss;
    if (!vec_intersection.empty())
    {
        std::copy(vec_intersection.begin(), vec_intersection.end() - 1, std::ostream_iterator<std::string>(oss, ", "));
        oss << vec_intersection.back();
        str_intersection = oss.str();
    }
    return str_intersection;
}

void DataBase::Select( const std::string tables,
                        std::string where,
                        std::string order_by) const
{
    std::vector<std::string> vec_tables = splitString_(this->make_from(tables),',');
    if (!vec_tables.empty())
    {
        sqlite3* db;
        if (order_by.empty()) {order_by = "id";}
        if (where.empty()) {where = "TRUE";}

        std::string request = "SELECT * FROM " + vec_tables[0] + " WHERE " + where;
        for (int i = 1; i < vec_tables.size(); ++i)
        {
            request += " UNION ALL ";
            request += "SELECT * FROM " + vec_tables[i] + " WHERE " + where;
        }
        request += " ORDER BY " + order_by;

        sqlite3_stmt* result;
        sqlite3_open(this->path.data(),&db);
        if (sqlite3_prepare_v2(db,request.data(),-1,&result,nullptr))
        {
            std::cout << "Select error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        while (sqlite3_step(result) == SQLITE_ROW)
        {
        std::cout   << sqlite3_column_int(result, 0) << " " // int id
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 1)) << " " //std::string typeName 
                    << sqlite3_column_int(result, 2) << " " //int price
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 3)) << " " //std::string sex
                    << sqlite3_column_int(result, 4) << " " //int fromWhatAge
                    << sqlite3_column_int(result, 5) << " " //int howMuchCanPlay
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 6)) << " " //std::string size
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 7)) << " " // std::string material
                    << reinterpret_cast<const char*>(sqlite3_column_text(result, 8)) << " " //std::string characteristic 
                    << std::endl;
        }
        sqlite3_finalize(result);
        sqlite3_close(db);
        return;
    }
    else
    {
        std::cout << "has no tables with these names" << std::endl;
    }
}