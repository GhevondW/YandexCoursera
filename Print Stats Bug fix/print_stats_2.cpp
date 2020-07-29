#if 1
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

template <typename Iter>
std::optional<string> FindMostPopularName(IteratorRange<Iter> range) {
  if (range.begin() == range.end()) {
    return std::nullopt;
  } else {
    sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
      return lhs.name < rhs.name;
    });
    const string* most_popular_name = &range.begin()->name;
    int count = 1;
    for (auto i = range.begin(); i != range.end(); ) {
      auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
        return p.name == i->name;
      });
      const auto cur_name_count = std::distance(i, same_name_end);
      if (
        cur_name_count > count ||
        (cur_name_count == count && i->name < *most_popular_name)
      ) {
        count = cur_name_count;
        most_popular_name = &i->name;
      }
      i = same_name_end;
    }
    return *most_popular_name;
  }
}

struct StatsData {
  std::optional<string> _maleName;
  std::optional<string> _femaleName;
  vector<int> _cumulativeWealth;
  vector<Person> _sortedAge;
};

StatsData BuildStatsData(vector<Person> people) {
  StatsData result;

  
    IteratorRange males{
      begin(people),
      partition(begin(people), end(people), [](const Person& p) {
        return p.is_male;
      })
    };
    IteratorRange females{males.end(), end(people)};

    result._maleName = FindMostPopularName(males);
    result._femaleName = FindMostPopularName(females);
  

  
    sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs) {
      return lhs.income > rhs.income;
    });

    auto& wealth = result._cumulativeWealth;
    wealth.resize(people.size());
    if (!people.empty()) {
      wealth[0] = people[0].income;
      for (size_t i = 1; i < people.size(); ++i) {
        wealth[i] = wealth[i - 1] + people[i].income;
      }
    }
  

  sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
  });
  result._sortedAge = std::move(people);

  return result;
}

int main() {
    
  const StatsData stats = BuildStatsData(ReadPeople(cin));

  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      auto adult_begin = lower_bound(
        begin(stats._sortedAge),
        end(stats._sortedAge),
        adult_age,
        [](const Person& lhs, int age) {
          return lhs.age < age;
        }
      );

      cout << "There are " << std::distance(adult_begin, end(stats._sortedAge))
           << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      cin >> count;
      cout << "Top-" << count << " people have total income "
           << stats._cumulativeWealth[count - 1] << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      cin >>gender;
      const auto& most_popular_name = gender == 'M' ? stats._maleName
                                                    : stats._femaleName;
      if (most_popular_name) {
        cout << "Most popular name among people of gender " << gender << " is "
             << *most_popular_name << '\n';
      } else {
        cout << "No people of gender " << gender << '\n';
      }
    }
  }
}
#endif
