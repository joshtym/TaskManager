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
   Task(Task*);
   ~Task();
   void updateTask(nlohmann::json, TaskOptions);
private:
   void updateDate(int);
   bool isUrgent;
   std::string name;
   std::string description;
   Date creationDate;
   Date deadlineDate;
   Date lastModified;
   int expectedDaysLeft;
   int parentTaskID;

   Task* parentTask;
   std::vector<Task*> childrenTasks;
};

#endif