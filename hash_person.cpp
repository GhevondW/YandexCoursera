#include "test_runner.h"
#include <limits>
#include <random>
#include <unordered_set>

using namespace std;

struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
      return city == other.city && street == other.street && building == other.building;
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
      return name == other.name && height == other.height && weight == other.weight && address == other.address;
  }
};

    
    
struct AddressHasher {
    const size_t coef = 2'946'901;
    size_t operator() (const Address& address) const
    {
        size_t a = _hash_string(address.city);
        size_t b = _hash_string(address.street);
        size_t c = _hash_int(address.building);
        return (a*coef*coef + b*coef + c);
    }
private:
    std::hash<std::string> _hash_string;
    std::hash<int> _hash_int;
};

struct PersonHasher {
    const size_t coef = 2'946'901;
    size_t operator() (const Person& person) const
    {
        size_t a = _hash_string(person.name);
        size_t b = _hash_int(person.height);
        size_t c = _hash_double(person.weight);
        size_t d = _hash_address(person.address);
        return (a*coef*coef*coef + b*coef*coef + c*coef + d);
    }
private:
    AddressHasher _hash_address;
    std::hash<std::string> _hash_string;
    std::hash<int> _hash_int;
    std::hash<double> _hash_double;
};

// ÑÐ³ÐµÐ½ÐµÑ€Ð¸Ñ€Ð¾Ð²Ð°Ð½Ñ‹ ÐºÐ¾Ð¼Ð°Ð½Ð´Ð¾Ð¹:
// $ sort -R /usr/share/dict/propernames | head -n 100
//
// http://www.freebsd.org/cgi/cvsweb.cgi/~checkout~/src/share/dict/propernames
const vector<string> WORDS = {
  "Kieran", "Jong", "Jisheng", "Vickie", "Adam", "Simon", "Lance",
  "Everett", "Bryan", "Timothy", "Daren", "Emmett", "Edwin", "List",
  "Sharon", "Trying", "Dan", "Saad", "Kamiya", "Nikolai", "Del",
  "Casper", "Arthur", "Mac", "Rajesh", "Belinda", "Robin", "Lenora",
  "Carisa", "Penny", "Sabrina", "Ofer", "Suzanne", "Pria", "Magnus",
  "Ralph", "Cathrin", "Phill", "Alex", "Reinhard", "Marsh", "Tandy",
  "Mongo", "Matthieu", "Sundaresan", "Piotr", "Ramneek", "Lynne", "Erwin",
  "Edgar", "Srikanth", "Kimberly", "Jingbai", "Lui", "Jussi", "Wilmer",
  "Stuart", "Grant", "Hotta", "Stan", "Samir", "Ramadoss", "Narendra",
  "Gill", "Jeff", "Raul", "Ken", "Rahul", "Max", "Agatha",
  "Elizabeth", "Tai", "Ellen", "Matt", "Ian", "Toerless", "Naomi",
  "Rodent", "Terrance", "Ethan", "Florian", "Rik", "Stanislaw", "Mott",
  "Charlie", "Marguerite", "Hitoshi", "Panacea", "Dieter", "Randell", "Earle",
  "Rajiv", "Ted", "Mann", "Bobbie", "Pat", "Olivier", "Harmon",
  "Raman", "Justin"
};

void TestSmoke() {
  vector<Person> points = {
    {"John", 180, 82.5, {"London", "Baker St", 221}},
    {"Sherlock", 190, 75.3, {"London", "Baker St", 221}},
  };

  unordered_set<Person, PersonHasher> point_set;
  for (const auto& point : points) {
    point_set.insert(point);
  }

  ASSERT_EQUAL(points.size(), point_set.size());
  for (const auto& point : points) {
    ASSERT_EQUAL(point_set.count(point), static_cast<size_t>(1));
  }
}

void TestPurity() {
  Person person = {"John", 180, 82.5, {"London", "Baker St", 221}};
  PersonHasher hasher;

  auto hash = hasher(person);
  for (size_t t = 0; t < 100; ++t) {
    ASSERT_EQUAL(hasher(person), hash);
  }
};

void TestDistribution() {
  auto seed = 42;
  mt19937 gen(seed);

  uniform_int_distribution<int> height_dist(150, 200);
  uniform_int_distribution<int> weight_dist(100, 240);  // [50, 120]
  uniform_int_distribution<int> building_dist(1, 300);
  uniform_int_distribution<int> word_dist(0, WORDS.size() - 1);

  PersonHasher hasher;

  // Ð²Ñ‹Ð±Ð¸Ñ€Ð°ÐµÐ¼ Ñ‡Ð¸ÑÐ»Ð¾ Ð±Ð°ÐºÐµÑ‚Ð¾Ð² Ð½Ðµ Ð¾Ñ‡ÐµÐ½ÑŒ Ð±Ð¾Ð»ÑŒÑˆÐ¸Ð¼ Ð¿Ñ€Ð¾ÑÑ‚Ñ‹Ð¼ Ñ‡Ð¸ÑÐ»Ð¾Ð¼
  // (unordered_set, unordered_map Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÑŽÑ‚ Ð¿Ñ€Ð¾ÑÑ‚Ñ‹Ðµ Ñ‡Ð¸ÑÐ»Ð° Ð±Ð°ÐºÐµÑ‚Ð¾Ð²
  // Ð² Ñ€ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸ÑÑ… GCC Ð¸ Clang, Ð´Ð»Ñ Ð½ÐµÐ¿Ñ€Ð¾ÑÑ‚Ñ‹Ñ… Ñ‡Ð¸ÑÐµÐ» Ð±Ð°ÐºÐµÑ‚Ð¾Ð²
  // Ð²Ð¾Ð·Ð½Ð¸ÐºÐ°ÑŽÑ‚ ÑÐ»Ð¾Ð¶Ð½Ð¾ÑÑ‚Ð¸ ÑÐ¾ ÑÑ‚Ð°Ð½Ð´Ð°Ñ€Ñ‚Ð½Ð¾Ð¹ Ñ…ÐµÑˆ-Ñ„ÑƒÐ½ÐºÑ†Ð¸ÐµÐ¹ Ð² ÑÑ‚Ð¸Ñ… Ñ€ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸ÑÑ…)
  const size_t num_buckets = 2053;

  // Ð¼Ñ‹ Ñ…Ð¾Ñ‚Ð¸Ð¼, Ñ‡Ñ‚Ð¾Ð±Ñ‹ Ñ‡Ð¸ÑÐ»Ð¾ Ñ‚Ð¾Ñ‡ÐµÐº Ð² Ð±Ð°ÐºÐµÑ‚Ð°Ñ… Ð±Ñ‹Ð»Ð¾ ~100'000
  const size_t perfect_bucket_size = 50;
  const size_t num_points = num_buckets * perfect_bucket_size;
  vector<size_t> buckets(num_buckets);
  for (size_t t = 0; t < num_points; ++t) {
    Person person;
    person.name = WORDS[word_dist(gen)];
    person.height = height_dist(gen);
    person.weight = weight_dist(gen) * 0.5;
    person.address.city = WORDS[word_dist(gen)];
    person.address.street = WORDS[word_dist(gen)];
    person.address.building = building_dist(gen);
    ++buckets[hasher(person) % num_buckets];
  }

  // Ð¡Ñ‚Ð°Ñ‚Ð¸ÑÑ‚Ð¸ÐºÐ° ÐŸÐ¸Ñ€ÑÐ¾Ð½Ð°:
  // https://en.wikipedia.org/wiki/Pearson's_chi-squared_test
  //
  // Ð§Ð¸ÑÐ»ÐµÐ½Ð½Ð¾Ð¹ Ð¼ÐµÑ€Ð¾Ð¹ Ñ€Ð°Ð²Ð½Ð¾Ð¼ÐµÑ€Ð½Ð¾ÑÑ‚Ð¸ Ñ€Ð°ÑÐ¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð¸Ñ Ñ‚Ð°ÐºÐ¶Ðµ Ð¼Ð¾Ð¶ÐµÑ‚ Ð²Ñ‹ÑÑ‚ÑƒÐ¿Ð°Ñ‚ÑŒ
  // ÑÐ½Ñ‚Ñ€Ð¾Ð¿Ð¸Ñ, Ð½Ð¾ Ð´Ð»Ñ ÐµÐµ Ð¿Ð¾Ñ€Ð¾Ð³Ð¾Ð² Ð½ÐµÑ‚ Ñ…Ð¾Ñ€Ð¾ÑˆÐµÐ¹ ÑÑ‚Ð°Ñ‚Ð¸ÑÑ‚Ð¸Ñ‡ÐµÑÐºÐ¾Ð¹ Ð¸Ð½Ñ‚ÐµÑ€Ð¿Ñ€ÐµÑ‚Ð°Ñ†Ð¸Ð¸
  double pearson_stat = 0;
  for (auto bucket_size : buckets) {
    size_t size_diff = bucket_size - perfect_bucket_size;
    pearson_stat +=
        size_diff * size_diff / static_cast<double>(perfect_bucket_size);
  }

  // Ð¿Ñ€Ð¾Ð²ÐµÑ€ÑÐµÐ¼ Ñ€Ð°Ð²Ð½Ð¾Ð¼ÐµÑ€Ð½Ð¾ÑÑ‚ÑŒ Ñ€Ð°ÑÐ¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð¸Ñ Ð¼ÐµÑ‚Ð¾Ð´Ð¾Ð¼ ÑÐ¾Ð³Ð»Ð°ÑÐ¸Ñ ÐŸÐ¸Ñ€ÑÐ¾Ð½Ð°
  // ÑÐ¾ ÑÑ‚Ð°Ñ‚Ð¸ÑÑ‚Ð¸Ñ‡ÐµÑÐºÐ¾Ð¹ Ð·Ð½Ð°Ñ‡Ð¸Ð¼Ð¾ÑÑ‚ÑŒÑŽ 0.95:
  //
  // ÐµÑÐ»Ð¸ Ð¿Ð¾Ð´ÑÑ‚Ð°Ð²Ð¸Ñ‚ÑŒ Ð²Ð¼ÐµÑÑ‚Ð¾ ++buckets[hasher(person) % num_buckets]
  // Ð²Ñ‹Ñ€Ð°Ð¶ÐµÐ½Ð¸Ðµ ++buckets[gen() % num_buckets], Ñ‚Ð¾ Ñ Ð²ÐµÑ€Ð¾ÑÑ‚Ð½Ð¾ÑÑ‚ÑŒÑŽ 95%
  // ASSERT Ð½Ð¸Ð¶Ðµ Ð¾Ñ‚Ñ€Ð°Ð±Ð¾Ñ‚Ð°ÐµÑ‚ ÑƒÑÐ¿ÐµÑˆÐ½Ð¾,
  //
  // Ñ‚.Ðº. ÑÑ‚Ð°Ñ‚Ð¸ÑÑ‚Ð¸ÐºÐ° ÐŸÐ¸Ñ€ÑÐ¾Ð½Ð° Ð¿Ñ€Ð¸Ð±Ð»Ð¸Ð·Ð¸Ñ‚ÐµÐ»ÑŒÐ½Ð¾ Ñ€Ð°ÑÐ¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð° Ð¿Ð¾ chi^2
  // Ñ Ñ‡Ð¸ÑÐ»Ð¾Ð¼ ÑÑ‚ÐµÐ¿ÐµÐ½ÐµÐ¹ ÑÐ²Ð¾Ð±Ð¾Ð´Ñ‹, Ñ€Ð°Ð²Ð½Ñ‹Ð¼ num_buckets - 1,
  // Ð¸ 95 Ð¿Ñ€Ð¾Ñ†ÐµÐ½Ñ‚Ð¸Ð»ÑŒ ÑÑ‚Ð¾Ð³Ð¾ Ñ€Ð°ÑÐ¿Ñ€ÐµÐ´ÐµÐ»ÐµÐ½Ð¸Ñ Ñ€Ð°Ð²ÐµÐ½:
  // >>> scipy.stats.chi2.ppf(0.95, 2052)
  const double critical_value = 2158.4981036918693;
  ASSERT(pearson_stat < critical_value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestPurity);
  RUN_TEST(tr, TestDistribution);

  return 0;
}
