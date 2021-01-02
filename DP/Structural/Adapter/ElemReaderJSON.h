#ifndef _ELEM_READER_JSON_H_
#define _ELEM_READER_JSON_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "IElementReader.h"

class ElemReaderJSON : public IElementReader
{
    using Iter = std::vector<std::string>::iterator;
public:
    ElemReaderJSON(/* args */) = default;
    explicit ElemReaderJSON(const std::string& path);

    ~ElemReaderJSON() = default;

    auto HasNext() const -> bool override;
    auto ReadNext() const -> Element override;
    auto Reset() -> void override;

private:
    std::vector<std::string> _data{};
    mutable Iter             _current{};
};

ElemReaderJSON::ElemReaderJSON(const std::string& path)
:IElementReader(path),
_data(),
_current(_data.end())
{
    using namespace std;

    std::ifstream in(_path);

    if(!in) {
        throw "File open Error!!";
    }

    std::string str;
    while (std::getline(in, str)) {
        _data.push_back(std::move(str));
    }

    in.close();

    _current = _data.begin();
}

auto ElemReaderJSON::HasNext() const -> bool
{
    return _current != std::end(_data);
}

auto ElemReaderJSON::ReadNext() const -> Element
{
    const std::string& ref = *_current;

    auto spl = split(ref, ',');
    ++_current;
    return Element::Make()
    .SetFirstName(spl[0])
    .SetLastName(spl[1])
    .SetGroupName(spl[2])
    .SetRating(std::stoi(spl[3]))
    .SetPubCount(std::stoi(spl[4]))
    .Build();
}

auto ElemReaderJSON::Reset() -> void
{

}

#endif