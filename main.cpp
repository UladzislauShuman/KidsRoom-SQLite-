//#include "All.h"
//#include "sqlite3/sqlite3.h"
#include "UserInterface/userinterface.h"

int main()
{
	UserInterface ui("database/example.db");
	ui.show();
	return 0;
}
