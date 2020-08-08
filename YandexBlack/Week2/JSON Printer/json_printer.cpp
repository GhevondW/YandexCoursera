#include "test_runner.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <cstring>
#include <experimental/string_view>

#define TEST_TRIGGER 0

using string_view = std::experimental::string_view;

void PrintJsonString(std::ostream& out, string_view str) {
    // реализуйте фукнцию
    out<<'"'<<str<<'"'<<endl;
}

using ArrayContext = void;  // Ð—Ð°Ð¼ÐµÐ½Ð¸Ñ‚Ðµ ÑÑ‚Ð¾ Ð¾Ð±ÑŠÑÐ²Ð»ÐµÐ½Ð¸Ðµ Ð½Ð° Ð¾Ð¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð¸Ðµ Ñ‚Ð¸Ð¿Ð° ArrayContext
ArrayContext PrintJsonArray(std::ostream& out) {
  // реализуйте фукнцию
}

using ObjectContext = void;  // Ð—Ð°Ð¼ÐµÐ½Ð¸Ñ‚Ðµ ÑÑ‚Ð¾ Ð¾Ð±ÑŠÑÐ²Ð»ÐµÐ½Ð¸Ðµ Ð½Ð° Ð¾Ð¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð¸Ðµ Ñ‚Ð¸Ð¿Ð° ObjectContext
ObjectContext PrintJsonObject(std::ostream& out) {
  // реализуйте фукнцию
}

#if TEST_TRIGGER

void TestArray() {
  std::ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json
      .Number(5)
      .Number(6)
      .BeginArray()
        .Number(7)
      .EndArray()
      .Number(8)
      .String("bingo!");
  }

  ASSERT_EQUAL(output.str(), R"([5,6,[7],8,"bingo!"])");
}

void TestObject() {
  std::ostringstream output;

  {
    auto json = PrintJsonObject(output);
    json
      .Key("id1").Number(1234)
      .Key("id2").Boolean(false)
      .Key("").Null()
      .Key("\"").String("\\");
  }

  ASSERT_EQUAL(output.str(), R"({"id1":1234,"id2":false,"":null,"\"":"\\"})");
}

void TestAutoClose() {
  std::ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json.BeginArray().BeginObject();
  }

  ASSERT_EQUAL(output.str(), R"([[{}]])");
}

#endif

int main() {
    TestRunner tr;

#if TEST_TRIGGER

  RUN_TEST(tr, TestArray);
  RUN_TEST(tr, TestObject);
  RUN_TEST(tr, TestAutoClose);

#endif

    PrintJsonString(std::cout, "Hello, \"world\"");

    return 0;
}