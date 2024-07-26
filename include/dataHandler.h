#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <sqlite3.h>

class DataHandler
{
public:
   DataHandler();
   ~DataHandler();
private:
   sqlite3 *db;
};

#endif