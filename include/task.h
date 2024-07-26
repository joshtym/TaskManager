#ifndef TASK_H
#define TASK_H

#include <string>
#include "date.h"
#include <vector>

class Task
{
public:
   Task();
   Task(Task*);
   ~Task();
private:
   bool isUrgent;
   std::string name;
   std::string description;
   Date creationDate;
   Date deadlineDate;
   int expectedDaysLeft;

   Task* parentTask;
   std::vector<Task*> childrenTasks;
};

#endif