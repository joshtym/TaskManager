#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <sqlite3.h>
#include <string>
#include "addressBook.h"
#include "task.h"

class DataHandler
{
public:
   DataHandler();
   ~DataHandler();
   int loadData(std::string);
private:
   sqlite3 *db;
   int currSqlFlag;
   AddressBook contacts;
   std::string currFile;
   std::vector<Task> loadedTasks;
   std::vector<std::string> statementsToUpdate;
};

#endif