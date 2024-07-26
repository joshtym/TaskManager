#include "dataHandler.h"
#include "json.h"

static int callbackHandler(void* count, int argc, char** argv, char** azColName)
{
   DataHandler* dh = reinterpret_cast<DataHandler*>(count);
   return dh->classCallback(argc, argv, azColName);
}

DataHandler::DataHandler()
{
   loadedTasks.clear();
   currentId = 0;
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

   // currSqlFlag = sqlite3_open(fileName.c_str(), &db);
   // if (currSqlFlag)
   // {
   //    std::cout << "Cannot open database. SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
   //    return -1;
   // }

   createTables(fileName);

   currSqlFlag = sqlite3_open(fileName.c_str(), &db);
   mode = 0;
   // TODO: Load in all the tasks into memory

   sqlStatement = "SELECT * FROM Tasks;";
   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), callbackHandler, this, &errMsg);
   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to load tasks. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   mode = 1;
   sqlStatement = "SELECT max(taskID) FROM Tasks;";
   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), callbackHandler, this, &errMsg);
   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to create database. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   sqlite3_close(db);
   return 0;
}

void DataHandler::createTables(std::string fileName)
{
   std::string sqlStmt;
   char* errMsg;

   // TODO: Add in error checking using a predefined exception class
   sqlite3_open(fileName.c_str(), &db);

   sqlStmt = "CREATE TABLE IF NOT EXISTS Tasks (taskID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
   "name VARCHAR(128), priority INT UNSIGNED, timeExpected INT UNSIGNED, parentID INT UNSIGNED, description TEXT NOT NULL,"
   " creationDate DATETIME NOT NULL, dateModified DATETIME NOT NULL, deadlineDate DATETIME NOT NULL);";

   sqlite3_exec(db, sqlStmt.c_str(), NULL, 0, &errMsg);

   sqlStmt = "CREATE TABLE IF NOT EXISTS EventLog (eventLogID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, taskID INT UNSIGNED, "
   "description TEXT NOT NULL, TimeStarted DATETIME, timePutIn INT UNSIGNED, creationDate DATETIME NOT NULL, dateModified DATETIME NOT NULL, "
   "FOREIGN KEY(taskID) REFERENCES Tasks(taskID));";

   sqlite3_exec(db, sqlStmt.c_str(), NULL, 0, &errMsg);

   sqlStmt = "CREATE TABLE IF NOT EXISTS Contacts (contactID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
   "FirstName VARCHAR(128), LastName VARCHAR(128), Email VARCHAR(128), PhoneNumber VARCHAR(128));";

   sqlite3_exec(db, sqlStmt.c_str(), NULL, 0, &errMsg);

   // TODO: Create Address book

   sqlite3_close(db);
}

void DataHandler::addTask(Task tk)
{
   loadedTasks[currentId++] = tk;
   nlohmann::json data = tk.getData();

   std::string sqlStatement;
   sqlStatement = "INSERT INTO Tasks VALUES (name, parentID, description, creationDate, dateModified, deadlineDate) VALUES (";
   sqlStatement += data["name"];
   sqlStatement += ", ";
   sqlStatement += data["parentID"];
   sqlStatement += ", ";
   sqlStatement += data["description"];
   sqlStatement += ", ";
   sqlStatement += data["creationDate"];
   sqlStatement += ", ";
   sqlStatement += data["dateModified"];
   sqlStatement += ", ";
   sqlStatement += data["deadlineDate"];
   sqlStatement += ", ";

   statementsToUpdate.push_back(sqlStatement);
}

void DataHandler::deleteTask(int id)
{
   auto it = loadedTasks.find(id);
   loadedTasks.erase(it);

   std::string sqlStatement = "DELETE FROM Tasks WHERE taskID = " + std::to_string(id);
   statementsToUpdate.push_back(sqlStatement);
}

int DataHandler::getCurrentId() const
{
   return currentId;
}

Task DataHandler::getTask(int id) const
{
   auto it = loadedTasks.find(id);
   return it->second;
}

int DataHandler::saveTasks()
{
   char* errMsg;

   for (int i = 0; i < statementsToUpdate.size(); ++i)
   {
      currSqlFlag = sqlite3_exec(db, statementsToUpdate[i].c_str(), NULL, 0, &errMsg);

      if (currSqlFlag != SQLITE_OK)
      {
         std::cout << "Failed to save data. SQL ERROR: " << errMsg << std::endl;
         return -1;
      }
   }
   return 0;
}

int DataHandler::classCallback(int argc, char** argv, char** errMsg)
{
   if (mode)
      currentId = atoi(argv[0]);
   else
   {
      nlohmann::json data;
      data["name"] = argv[1];
      data["parentId"] = atoi(argv[2]);
      data["description"] = argv[3];
      data["creationTime"] = argv[4];
      data["dateModified"] = argv[5];
      data["deadlineDate"] = argv[6];

      Task tk;
      tk.updateTask(data);
      loadedTasks[atoi(argv[0])] = tk;
   }

   return 0;
}
