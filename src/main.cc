#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   std::cout << "MAke it here?" << std::endl;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char** argv)
{
   sqlite3 *db;
   int sqlFlag;
   std::string sql;
   char* zErrMsg = 0;

   sqlFlag = sqlite3_open("test.tskmgr", &db);

   if (sqlFlag)
      std::cerr << "Couldn't open database with error: " << sqlite3_errmsg(db) << std::endl;
   else
      std::cerr << "Successfully opened database" << std::endl;
   

   sql = "CREATE TABLE COMPANY(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL, AGE INT NOT NULL, ADDRESS CHAR(50), SALARY REAL);";

   sqlFlag = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if (sqlFlag)
   {
      std::cerr << "SQL Error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
   }
   else
      std::cerr << "Table created successfully" << std::endl;;

   sqlite3_close(db);
   
   return 0;
}