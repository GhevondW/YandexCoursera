#ifndef _ELEM_WRITTER_XML_H_
#define _ELEM_WRITTER_XML_H_

#include "IElementWriter.h"

class ElemWriterXML : public IElementWriter
{
public:
    ElemWriterXML(/* args */) = default;
    ElemWriterXML(const std::string);
    ~ElemWriterXML() = default;

    void AcceptElement(const Element&) override;
	void Close() override;

};

ElemWriterXML::ElemWriterXML(const std::string path)
:IElementWriter(path)
{}

void ElemWriterXML::AcceptElement(const Element& elem)
{
    if(!_file.is_open()){
        throw "File opening error!!";
    }

    std::string res{""};
    res += elem.GetFirstName();
    res += "~";
    res += elem.GetLastName();
    res += "~";
    res += elem.GetGroupName();
    res += "~";
    res += std::to_string(elem.GetRating());
    res += "~";
    res += std::to_string(elem.GetPublicationsCount());
    res += '\n';

    _file << res;
}

void ElemWriterXML::Close()
{
    _file.close();
}

#endif