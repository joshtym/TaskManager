#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <ctime>
#include "date.h"
#include "json.h"

enum TaskOptions {CREATE, EDIT, DELETE};

class Task
{
public:
   Task();
   Task(int);
   ~Task();
   void updateTask(nlohmann::json);
   nlohmann::json getData() const;
private:
   std::string getCurrentDate();
   int taskId;
   std::string name;
   std::string description;
   std::string creationDate;
   std::string deadlineDate;
   std::string lastModified;
   int expectedDaysLeft;
   int parentTaskID;
   std::vector<int> childrenTaskIDs;
};

#endif