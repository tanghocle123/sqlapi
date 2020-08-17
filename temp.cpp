#include "temp.h"
// https://www.sqlapi.com/ApiDoc/class_s_a_value_read.html
bool table_is_empty(SAConnection& con, const std::string& table_name) {
    SACommand cmd;
    cmd.setConnection(&con);
    try {
        cmd.setCommandText(_TSA(("SELECT * FROM " + table_name).c_str()));
        cmd.Execute(); // Remember to execute after a command
        return 0; // TABLE IS NOT EMPTY
    }
    catch(SAException &x) {
        printf("%s\n", x.ErrText().GetMultiByteChars());
        return 1; // TABLE IS EMPTY
    }
}

void create_table(SAConnection& con, const std::string& table_name) {
    SACommand cmd;

	try {
		cmd.setConnection(&con);
		cmd.setCommandText(_TSA("CREATE TABLE EMPLOYEES (ID number,NAME varchar(20), AGE number);"));
		cmd.Execute();
	}
	catch(SAException &x) {
		con.Rollback();
		printf("%s\n", x.ErrText().GetMultiByteChars());
	}
}

void create_database(SAConnection& con, const std::string& db_name, const std::string& user,const std::string& pw, const SAClient_t& client) {
    try {
		// Create a database and connect
		con.Connect(_TSA(db_name.c_str()),_TSA(user.c_str()), _TSA(pw.c_str()), client);
		std::cout << "Connected" << std::endl;
	}
	catch(SAException &x) {
		con.Rollback();
		printf("%s\n", x.ErrText().GetMultiByteChars());
	}
}

void print_test()
{
    std::cout << "Print test" << std::endl;
}

void insert_table(SAConnection& con, const std::string& db_name) {
    try{
        SACommand cmd(&con, _TSA(("INSERT INTO " + db_name + " (ID,NAME,AGE) VALUES(:1, :2, :3)")).c_str());
        int64_t id;
        int64_t age;
        std::string name;
        while(std::cin >> id >> name >> age)
        {
            if(id==0 || id==-1) break;
            cmd << id << _TSA(name.c_str()) << age;
            cmd.Execute();
        }
    }
	catch(SAException &x) {
		con.Rollback();
		printf("%s\n", x.ErrText().GetMultiByteChars());
	}
}

void print_table(SAConnection& con, const std::string& db_name) {
    try {
        SACommand cmd(&con, _TSA(("SELECT * FROM " + db_name).c_str()));
        cmd.Execute();
        int columns = cmd.FieldCount();
        while(cmd.FetchNext()) {
    		printf("ID: %ld, Name: %s, age: %ld \n",
			cmd.Field(_TSA("ID")).asLong(),
            cmd.Field(_TSA("name")).asString().GetMultiByteChars(),
            // asString - return field value as SAstring
            // GetMultiByteChars - converts SAstring to const char *

            cmd.Field(_TSA("age")).asLong());
        }

    }
    catch(SAException &x) {
		con.Rollback();
		printf("%s\n", x.ErrText().GetMultiByteChars());
	}
}


