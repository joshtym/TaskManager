#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <ctime>
#include "date.h"
#include "json.h"

class Task
{
public:
   Task();
   Task(Task*);
   ~Task();
   void updateTask(nlohmann::json);
private:
   void updateDate(int);
   bool isUrgent;
   std::string name;
   std::string description;
   Date creationDate;
   Date deadlineDate;
   Date lastModified;
   int expectedDaysLeft;

   Task* parentTask;
   std::vector<Task*> childrenTasks;
};

#endif