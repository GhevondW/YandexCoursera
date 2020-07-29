#if 1
#include <string>
#include "test_runner.h"
using namespace std;

#include <list>

class Editor {
 public:
    // � еализуйте конструктор по умолчанию и объявленные методы
    Editor()
    :_text(),
    _postition(_text.begin()),
    _buffer()
    {}
    
    void Left()
    {
        if(_postition != _text.begin()){
            --_postition;
        }
    }
    
    void Right()
    {
        if(_postition != _text.end()){
            ++_postition;
        }
    }
    
    void Insert(char token)
    {
        _postition = _text.insert(_postition, token);
        ++_postition;
    }
    
    void Cut(size_t tokens = 1)
    {
        _buffer.clear();
        auto end = _MoveRight(tokens);
        _buffer.splice(_buffer.begin(), _text, _postition, end);
        _postition = end;
    }
    
    void Copy(size_t tokens = 1)
    {
        _buffer.assign(_postition, _MoveRight(tokens));
    }
    
    void Paste()
    {
        _text.insert(_postition, _buffer.begin(), _buffer.end());
    }
    
    string GetText() const{
        return {_text.begin(), _text.end()};
    }
    
private:
    
    auto _MoveRight(size_t tokens) -> std::list<char>::iterator
    {
        auto c = _postition;
        for (int i = 0; i < tokens; ++i) {
            if(c == _text.end()){
                return c;
            }
            ++c;
        }
        return c;
    }
    
private:
    std::list<char> _text;
    std::list<char>::iterator _postition;
    std::list<char> _buffer;
};

//class Editor {
// public:
//  // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€ Ð¿Ð¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ Ð¸ Ð¾Ð±ÑŠÑÐ²Ð»ÐµÐ½Ð½Ñ‹Ðµ Ð¼ÐµÑ‚Ð¾Ð´Ñ‹
//  Editor();
//  void Left();
//  void Right();
//  void Insert(char token);
//  void Cut(size_t tokens = 1);
//  void Copy(size_t tokens = 1);
//  void Paste();
//  string GetText() const;
//};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
#endif
