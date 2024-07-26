#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "dataHandler.h"

int main(int argc, char** argv)
{
   DataHandler dh;
   dh.loadData("test.tskmgr");
   return 0;
}