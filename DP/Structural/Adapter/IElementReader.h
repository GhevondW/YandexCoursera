#ifndef _I_ELEMENT_READER_H_
#define _I_ELEMENT_READER_H_

#include "Element.h"
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string& text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while(std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

struct IElementReader
{
    IElementReader() = default;
    explicit IElementReader(const std::string& path):_path(path){}
    virtual ~IElementReader() = default;

    virtual auto HasNext() const -> bool = 0;
    virtual auto ReadNext() const -> Element = 0;
    virtual auto Reset() -> void = 0;

    auto GetFilePath() const -> const std::string& { return _path; }

protected:
    std::string _path{};
};


#endif