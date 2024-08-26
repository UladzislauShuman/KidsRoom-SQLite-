#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <functional>
#include <iterator>
#include <algorithm>

#include <typeindex>
#include <typeinfo>
#include <cstdlib>
#include <memory>
//#include <cxxabi.h>

std::vector<std::string> splitString_(const std::string& str, char delimiter);

template<class T> std::string obj_type()
{
    /*char const * name = typeid(T).name();
    int status;
    std::unique_ptr<char, void(*)(void*)> res(abi::__cxa_demangle(name, NULL, NULL, &status), std::free);
    return status == 0 ? res.get() : name ;*/
    return std::type_index(typeid(T)).name();
}