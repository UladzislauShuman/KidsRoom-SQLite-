#include "Utils.h"

std::vector<std::string> splitString_(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        // ������� ������� � ������ � ����� ������
        token.erase(token.begin(), std::find_if_not(token.begin(), token.end(), isspace));
        token.erase(std::find_if_not(token.rbegin(), token.rend(), isspace).base(), token.end());

        // ��������� ����� � ������, ���� �� �� ������
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}