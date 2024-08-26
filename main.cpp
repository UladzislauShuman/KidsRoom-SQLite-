//#include "All.h"
//#include "sqlite3/sqlite3.h"
#include "UserInterface/userinterface.h"
#include <filesystem>

int main()
{
	std::string current_path = std::filesystem::current_path().parent_path();
	std::cout << current_path + "/database/example.db" << std::endl;
	UserInterface ui(current_path + "/database/example.db");
	ui.show();
	return 0;
}
