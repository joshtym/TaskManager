#ifndef CONTACT_H
#define CONTACT_H

class Contact
{
public:
   Contact();
   ~Contact();
private:
   std::string firstName;
   std::string middleName;
   std::string lastName;
   std::string streetAddress;
   std::string city;
   std::string stateProvince;
   std::string country;
   std::string email;
   int phoneNumber;
};

#endif