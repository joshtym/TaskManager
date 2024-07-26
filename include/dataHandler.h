#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <sqlite3.h>
#include <string>
#include "addressBook.h"
#include "task.h"
#include "json.h"

class DataHandler
{
public:
   DataHandler();
   ~DataHandler();
   int loadData(std::string);
   void addTask(Task);
   void editTask(nlohmann::json);
   void deleteTask(int);
   int getCurrentId() const;
   Task getTask(int) const;
   int saveTasks();
   int classCallback(int, char**, char**);
private:
   sqlite3 *db;
   int currSqlFlag;
   int currentId;
   int mode;
   AddressBook contacts;
   std::string currFile;
   std::vector<int> parentTasks;
   std::map<int, Task> loadedTasks;
   std::vector<std::string> statementsToUpdate;
};

#endif