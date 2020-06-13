#if 0
#include "test_runner.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target)
    {
        std::string s{source};
        std::string t{target};
        auto f = _words.insert(s);
        auto b = _words.insert(t);
        _f[*f.first] = *b.first;
        _b[*b.first] = *f.first;
    }
    
    string_view TranslateForward(string_view source) const
    {
        auto f = _f.find(source);
        if(f != _f.end()){
            return f->second;
        }
        return "";
    }
    
    string_view TranslateBackward(string_view target) const
    {
        auto f = _b.find(target);
        if(f != _b.end()){
            return f->second;
        }
        return "";
    }

private:
    std::set<std::string> _words;
    std::map<std::string_view, std::string_view> _f;
    std::map<std::string_view, std::string_view> _b;
};


void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
#endif
