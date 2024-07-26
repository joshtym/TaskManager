#ifndef DATE_H
#define DATE_H

//
// Date class
//
// This is an implementation of some common functionalities for dates.
// It can represent dates from Jan 1, 1753 to after (dates before that
// time are complicated...).
//

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype>

using namespace std;
using namespace std::rel_ops;

// Enumerated type for names of the days of the week
enum dayName {SUN,MON,TUE,WED,THU,FRI,SAT};

struct Date
{
   int yyyy;
   int mm;
   int dd;
   
   // no dates before 1753
   static int const BASE_YEAR = 1753;
   
   // Is a date valid
   static bool validDate(int yr, int mon, int day);
   
   bool isValid() const;
   
   /*
    * Constructor to create a specific date.  If the date is invalid,
    * the behaviour is undefined
   */
   Date(int yr = 1970, int mon = 1, int day = 1);
   
   // Returns the day of the week for this
   dayName dayOfWeek() const;
   
   // comparison operators
   bool operator==(const Date &d) const;
   bool operator<(const Date &d) const;
   
   // Returns true if yr is a leap year
   static bool leapYear(int y);
   
   // number of days in this month
   static int daysIn(int m, int y);

   /*
    * Increment by day, month, or year
    *
    * Use negative argument to decrement
    *
    * If adding a month / year results in a date before BASE_YEAR,
    * the result is undefined
    *
    * If adding a month / year results in an invalid date (Feb 29
    * on a non-leap year, Feb 31, Jun 31, etc.), the results are
    * automatically "rounded down" to the last valid date
   */
   
   // add n days to the date: complexity is about n/30 iterations
   void addDay(int n = 1);
   
   // add n months to the date: complexity is about n/12 iterations
   void addMonth(int n = 1);
   
   // add n years to the date
   void addYear(int n = 1);
   
   // number of days since 1753/01/01, including the current date
   int daysFromStart() const;

   
   // Reads a date in yyyy/mm/dd format, assumes date is valid and in the
   // right format
   friend istream& operator>>(istream &is, Date &d);
   friend ostream& operator<<(ostream &os, const Date &d);
};

#endif


