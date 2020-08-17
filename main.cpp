#include <iostream>
#include <stdio.h>
#include "temp.h"
void YN(bool b) {
	if(b==true) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;
}

int main() {

	SAConnection con;
	create_database(con,"my_db");
	std::string table_name = "EMPLOYEES";
	create_table(con,table_name);
	insert_table(con,table_name);
	print_table(con,table_name);
	
	return 0;
}