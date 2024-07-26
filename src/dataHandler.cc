#include "dataHandler.h"
#include "json.h"

DataHandler::DataHandler()
{

}

DataHandler::~DataHandler()
{
   
}

int DataHandler::loadData(std::string fileName)
{
   currSqlFlag = sqlite3_open(fileName.c_str(), &db);

   if (currSqlFlag)
   {
      std::cout << "SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
      return -1;
   }

   sqlite3_close(db);
   return 0;
}

