#if 0
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;


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
    if (first.hours < second.hours)
        return true;
    else if (first.hours == second.hours)
    {
        if (first.minutes < second.minutes)
            return true;
    }
    return false;
}

ostream& operator<<(ostream& stream, const Date& date)
{
    stream<<date.year<< ":" <<date.month<<":"<<date.day;
    return stream;
}

ostream& operator<<(ostream& stream, const Time& time)
{
    stream<<time.hours<< ":" <<time.minutes;
    return stream;
}

//it = updates.find("price");
//if (it != updates.end()) {
//  istringstream is(it->second);
//  is >> ticket.price;
//}

istream& operator>>(istream& stream, Date& date)
{
    stream >> date.year;
    date.year = std::abs(date.year);
    stream >> date.month;
    date.month = std::abs(date.month);
    stream >> date.day;
    date.day = std::abs(date.day);
    return stream;
}

istream& operator>>(istream& stream, Time& time)
{
    string tmp;
    stream >> tmp;
    
    std::stringstream ss(tmp);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, ':'))
    {
       splittedStrings.push_back(item);
    }
    
    time.hours = std::stoi(splittedStrings[0]);
    time.minutes = std::stoi(splittedStrings[1]);
    
    return stream;
}

#define UPDATE_FIELD(ticket, field, values) \
if(values.find(#field) != values.end()){   \
    istringstream is(values.find(#field)->second);          \
    is >> ticket.field;\
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
    
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
#endif
