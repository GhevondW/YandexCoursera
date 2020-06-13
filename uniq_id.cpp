#if 0
#include <string>
#include <vector>
using namespace std;

#define UNIQ_ID_TOP_TOP(line) var##line
#define UNIQ_ID_TOP(line) UNIQ_ID_TOP_TOP(line)
#define UNIQ_ID UNIQ_ID_TOP(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
#endif
