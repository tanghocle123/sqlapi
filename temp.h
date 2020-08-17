#pragma once
#include "includer.h"

void print_test();
bool table_is_empty(SAConnection& con, const std::string& table_name);
void create_table(SAConnection& con, const std::string& table_name);
void create_database(SAConnection& con, const std::string& db_name, const std::string& user="my_user",const std::string& pw="my_password", const SAClient_t& client =SA_SQLite_Client);

void insert_table(SAConnection& con, const std::string& db_name);
void print_table(SAConnection& con, const std::string& db_name);
