#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <string>
#include <utility>
#include <iostream>

#include "EditorMemento.h"

class Editor
{
private:
    std::string _text{};
    size_t      _x{};
    size_t      _y{};
    size_t      _selectionWidth{};
public:
    Editor(/* args */) = default;
    ~Editor() = default;

    const std::string& GetText() const { return _text; }
    size_t GetX() const { return _x; }
    size_t GetY() const { return _y; }
    size_t GetSelectionWidth() const { return _selectionWidth; }

    void SetText(const std::string& text) { _text = text; }
    void SetX(size_t x) { _x = x; }
    void SetY(size_t y) { _y = y; }
    void SetSelectionWidth(size_t val) { _selectionWidth = val; }

    void Print() const
    {
        std::cout<<"Text:"<<_text<<", "
        <<"X:"<<_x<<", "
        <<"Y:"<<_y<<", "
        <<"SW:"<<_selectionWidth<<std::endl;
    }

    EditorMemento Save()
    {
        return EditorMemento{this, _text, _x, _y, _selectionWidth};
    }

};

#endif