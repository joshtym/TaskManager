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

   currSqlFlag = sqlite3_open(fileName.c_str(), &db);
   if (currSqlFlag)
   {
      std::cout << "Cannot open database. SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
      return -1;
   }

   sqlStatement = "CREATE TABLE IF NOT EXISTS TASKS (taskID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name VARCHAR(128), parentID INT UNSIGNED, description TEXT NOT NULL, creationDate DATETIME NOT NULL, dateModified DATETIME NOT NULL, deadlineDate DATETIME NOT NULL);";
   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), NULL, 0, &errMsg);
   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to create database. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   mode = 0;
   /// TODO: Load in all the tasks into memory
   sqlStatement = "SELECT * FROM TASKS";
   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), callbackHandler, this, &errMsg);
   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to load tasks. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   mode = 1;
   sqlStatement = "SELECT max(taskID) FROM TASKS;";
   currSqlFlag = sqlite3_exec(db, sqlStatement.c_str(), callbackHandler, this, &errMsg);
   if (currSqlFlag != SQLITE_OK)
   {
      std::cout << "Failed to create database. SQL ERROR: " << errMsg << std::endl;
      return -1;
   }

   sqlite3_close(db);
   return 0;
}

void DataHandler::addTask(Task tk)
{
   loadedTasks[currentId++] = tk;
   nlohmann::json data = tk.getData();

   std::string sqlStatement;
   sqlStatement = "INSERT INTO TASKS VALUES (name, parentID, description, creationDate, dateModified, deadlineDate) VALUES (";
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

   std::string sqlStatement = "DELETE FROM TASKS WHERE taskID = " + std::to_string(id);
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
