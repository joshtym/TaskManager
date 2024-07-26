#include "dataHandler.h"
#include "json.h"

DataHandler::DataHandler()
{
   loadedTasks.clear();
}

DataHandler::~DataHandler()
{
   loadedTasks.clear();
}

int DataHandler::loadData(std::string fileName)
{
   std::string sqlStatement;
   currFile = fileName;
   char* errMsg;

   currSqlFlag = sqlite3_open(fileName.c_str(), &db);

   if (currSqlFlag)
   {
      std::cout << "Cannot open database. SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
      return -1;
   }

   sqlStatement = "CREATE TABLE IF NOT EXISTS TASKS (taskID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(128), parentID INT UNSIGNED, description TEXT NOT NULL, creationDate DATETIME NOT NULL, dateModified DATETIME NOT NULL);";

   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), NULL, 0, &errMsg);

   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to create database. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   sqlite3_close(db);
   return 0;
}

int DataHandler::addTask(nlohmann::json taskData)
{
   Task tk;
   tk.updateTask(taskData, TaskOptions::CREATE);
   loadedTasks.push_back(tk);

   std::string name = taskData["name"];
   int parentTask = taskData["parentTaskID"];
   std::string parentTaskID = std::to_string(parentTask);
   std::string description = taskData["description"];

   std::string sqlStatement = "INSERT INTO TASKS (name, parentID, description, creationDate, dateModified) VALUES (" + name + ", " + parentTaskID + ", " + description + ", NOW(), NOW());";

   statementsToUpdate.push_back(sqlStatement);

   return 0;
}


