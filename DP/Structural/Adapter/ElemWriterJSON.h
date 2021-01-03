#ifndef _ELEM_WRITTER_JSON_H_
#define _ELEM_WRITTER_JSON_H_

#include "IElementWriter.h"

class ElemWriterJSON : public IElementWriter
{
public:
    ElemWriterJSON(/* args */) = default;
    ElemWriterJSON(const std::string);
    ~ElemWriterJSON() = default;

    void AcceptElement(const Element&) override;
	void Close() override;

};

ElemWriterJSON::ElemWriterJSON(const std::string path)
:IElementWriter(path)
{}

void ElemWriterJSON::AcceptElement(const Element& elem)
{
    if(!_file.is_open()){
        throw "File opening error!!";
    }

    std::string res{""};
    res += elem.GetFirstName();
    res += ",";
    res += elem.GetLastName();
    res += ",";
    res += elem.GetGroupName();
    res += ",";
    res += std::to_string(elem.GetRating());
    res += ",";
    res += std::to_string(elem.GetPublicationsCount());
    res += '\n';

    _file << res;
}

void ElemWriterJSON::Close()
{
    _file.close();
}

#endif