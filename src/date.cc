#include "date.h"

Date::Date(int yr, int mon, int day)
{
   yyyy = yr;
   mm = mon;
   dd = day;
}

bool Date::validDate(int yr, int mon, int day)
{
   return yr >= BASE_YEAR && mon >= 1 && mon <= 12 && 
      day > 0 && day <= daysIn(mon, yr);
}

bool Date::isValid() const
{
   return validDate(yyyy, mm, dd);
}

dayName Date::dayOfWeek() const
{
   int a = (14 - mm) / 12;
   int y = yyyy - a;
   int m = mm + 12 * a - 2;
   return (dayName)((dd + y + y/4 - y/100 + y/400 + 31 * m / 12) % 7);
}

bool Date::operator==(const Date &d) const
{
   return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
}

bool Date::operator<(const Date &d) const
{
   return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
      (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
}

bool Date::leapYear(int y)
{
   return (y % 400 ==0 || (y % 4 == 0 && y % 100 != 0));
}

int Date::daysIn(int m, int y)
{
   switch (m)
   {
      case 4  :
      case 6  :
      case 9  :
      case 11 :
         return 30;
      case 2  :
        if (leapYear(y))
           return 29;
        else
           return 28;
      default :
         return 31;
   }
}

void Date::addDay(int n)
{
   dd += n;
   while (dd > daysIn(mm,yyyy))
   {
      dd -= daysIn(mm,yyyy);
      if (++mm > 12)
      {
         mm = 1;
         yyyy++;
      }
   }
   
   while (dd < 1)
   {
      if (--mm < 1)
      {
         mm = 12;
         yyyy--;
      }
      dd += daysIn(mm,yyyy); 
   }
}

void Date::addMonth(int n)
{
   mm += n;
   while (mm > 12)
   {
      mm -= 12;
      yyyy++;
   }
   
   while (mm < 1)
   {
      mm += 12;
      yyyy--;
   }
   
   if (dd > daysIn(mm,yyyy))
      dd = daysIn(mm,yyyy);
}

void Date::addYear(int n)
{
   yyyy += n;
   if (!leapYear(yyyy) && mm == 2 && dd == 29)
      dd = 28;
}

int Date::daysFromStart() const
{
   int c = 0;
   Date d(BASE_YEAR, 1, 1);
   Date d2(d);

   d2.addYear(1);
   while (d2 < *this)
   {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
   }

   d2 = d;
   d2.addMonth(1);
   while (d2 < *this)
   {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
   }
   while (d <= *this)
   {
      d.addDay();
      c++;
   }
   return c;
}

istream& operator>>(istream &is, Date &d)
{
  char c;
  return is >> d.yyyy >> c >> d.mm >> c >> d.dd;
}

// print date in yyyy/mm/dd format
ostream& operator<< (ostream &os, const Date &d)
{
   char t = os.fill('0');
   os << d.yyyy << '/' << setw(2) << d.mm << '/' << setw(2) << d.dd;
   os.fill(t);
   return os;
}