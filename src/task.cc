#include "task.h"

Task::Task()
{
   name = "";
   description = "";
   creationDate = getCurrentDate();
}

Task::Task(int parent)
{
   parentTaskID = parent;
}

Task::~Task()
{
}

void Task::updateTask(nlohmann::json givenData)
{
   lastModified = getCurrentDate();
   taskId = givenData["taskID"];
   name = givenData["name"];
   description = givenData["description"];
   creationDate = givenData["creationDate"];
   deadlineDate = givenData["deadlineDate"];
   parentTaskID = givenData["parentTaskID"];

   childrenTaskIDs.clear();
   for (auto it = givenData["childrenTaskIDs"].begin(); it != givenData["childrenTaskIDs"].end(); ++it)
      childrenTaskIDs.push_back(*it);
}

nlohmann::json Task::getData() const
{
   nlohmann::json data;
   data["taskID"] = taskId;
   data["name"] = name;
   data["description"] = description;
   data["creationDate"] = creationDate;
   data["deadlineDate"] = deadlineDate;
   data["lastModified"] = lastModified;
   data["parentTaskID"] = parentTaskID;
   data["childrenTaskIDs"] = childrenTaskIDs;
   return data;
}

std::string Task::getCurrentDate()
{
   std::string date = "";
   time_t now = time(0);
   tm *ltm = localtime(&now);

   date += std::to_string(ltm->tm_mon + 1);
   date += "/";
   date += std::to_string(ltm->tm_mday);
   date += "/";
   date += std::to_string(ltm->tm_year);

   return date;
}