#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "dataHandler.h"

int main(int argc, char** argv)
{
   std::string fileName;
   std::cout << "Filename?: ";
   while (std::cin >> fileName)
   {
      DataHandler dh;
      dh.loadData(fileName);

      std::cout << "Filename?: ";
   }

   return 0;
}