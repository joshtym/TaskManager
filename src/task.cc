#include "task.h"

Task::Task()
{
   parentTask = nullptr;
   isUrgent = false;
   name = "";
   description = "";
   updateDate(0);
   updateDate(1);
}

Task::Task(Task* parent)
{
   parentTask = parent;
}

Task::~Task()
{
   delete parentTask;
   parentTask = nullptr;

   for (std::vector<Task*>::iterator it = childrenTasks.begin(); it != childrenTasks.end(); ++it)
   {
      delete *it;
      *it = nullptr;
   }
}

void Task::updateTask(nlohmann::json givenData)
{
   isUrgent = givenData["isUrgent"];
   name = givenData["name"];
   description = givenData["description"];
   creationDate.yyyy = givenData["creationDate"]["yyyy"];
   creationDate.mm = givenData["creationDate"]["mm"];
   creationDate.dd = givenData["creationDate"]["dd"];
   lastModified.yyyy = givenData["lastModified"]["yyyy"];
   lastModified.mm = givenData["lastModified"]["mm"];
   lastModified.dd = givenData["lastModified"]["dd"];
   deadlineDate.yyyy = givenData["deadlineDate"]["yyyy"];
   deadlineDate.mm = givenData["deadlineDate"]["mm"];
   deadlineDate.dd = givenData["deadlineDate"]["dd"];
   expectedDaysLeft = givenData["expectedDaysLeft"];
}

void Task::updateDate(int whichDate)
{
   time_t now = time(0);
   tm *ltm = localtime(&now);

   if (whichDate)
   {
      creationDate.yyyy = ltm->tm_year;
      creationDate.mm = ltm->tm_mon + 1;
      creationDate.dd = ltm->tm_mday;
   }
   else
   {
      lastModified.yyyy = ltm->tm_year;
      lastModified.mm = ltm->tm_mon + 1;
      lastModified.dd = ltm->tm_mday;
   }
}