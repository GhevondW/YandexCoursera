#ifndef _ELEM_READER_XML_H_
#define _ELEM_READER_XML_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "IElementReader.h"

class ElemReaderXML : public IElementReader
{
    using Iter = std::vector<std::string>::iterator;
public:
    ElemReaderXML(/* args */) = default;
    explicit ElemReaderXML(const std::string& path);

    ~ElemReaderXML() = default;

    auto HasNext() const -> bool override;
    auto ReadNext() const -> Element override;
    auto Reset() -> void override;

private:
    std::vector<std::string> _data{};
    mutable Iter             _current{};
};

ElemReaderXML::ElemReaderXML(const std::string& path)
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

auto ElemReaderXML::HasNext() const -> bool
{
    return _current != std::end(_data);
}

auto ElemReaderXML::ReadNext() const -> Element
{
    const std::string& ref = *_current;

    auto spl = split(ref, '~');
    ++_current;
    return Element::Make()
    .SetFirstName(spl[0])
    .SetLastName(spl[1])
    .SetGroupName(spl[2])
    .SetRating(std::stoi(spl[3]))
    .SetPubCount(std::stoi(spl[4]))
    .Build();
}

auto ElemReaderXML::Reset() -> void
{

}

#endif