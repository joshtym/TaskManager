#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "contact.h"
#include <vector>

class AddressBook
{
public:
   AddressBook();
   ~AddressBook();
private:
   std::vector<Contact> contacts;
};

#endif