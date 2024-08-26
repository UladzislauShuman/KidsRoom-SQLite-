#include "Utils.h"

std::vector<std::string> splitString_(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        // ”дал€ем пробелы в начале и конце токена
        token.erase(token.begin(), std::find_if_not(token.begin(), token.end(), isspace));
        token.erase(std::find_if_not(token.rbegin(), token.rend(), isspace).base(), token.end());

        // ƒобавл€ем токен в вектор, если он не пустой
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}