#if 1
#include "test_runner.h"
#include "profile.h"
#include <execution>

#include <map>
#include <string>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other)
    {
        auto current = other.word_frequences.begin();
        while (current != end(other.word_frequences)) {
            if(word_frequences.count(current->first))
            {
                word_frequences[current->first] += current->second;
            }
            else{
                word_frequences[current->first] += current->second;
            }
            ++current;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    return {};
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    return {};
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
//  RUN_TEST(tr, TestBasic);
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    ExploreKeyWordsSingleThread(key_words, ss);
}
#endif
