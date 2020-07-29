#if 1
#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;


#define SORT_BY(field) [](const AirlineTicket& lhs, const AirlineTicket& rhs) { return lhs.field < rhs.field; }
    

bool operator==(const Date& first, const Date& second)
{
    return first.year == second.year && first.month == second.month && first.day == second.day;
}

bool operator==(const Time& first, const Time& second)
{
    return first.hours == second.hours && first.minutes == second.minutes;
}

bool operator<(const Date& first, const Date& second)
{
    if (first.year < second.year)
        return true;
    else if (first.year == second.year)
    {
        if (first.month < second.month)
            return true;
        else if (first.month == second.month)
        {
            if (first.day < second.day)
                return true;
        }
    }
    return false;
}

bool operator<(const Time& first, const Time& second)
{
    if(first == second) return false;
    if(first.hours > second.hours) return false;
    if(first.minutes > second.minutes) return false;
    return true;
}

ostream& operator<<(ostream& stream, const Date& date)
{
    stream<<date.year<< ":" <<date.month<<":"<<date.day;
    return stream;
}

void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
#endif
