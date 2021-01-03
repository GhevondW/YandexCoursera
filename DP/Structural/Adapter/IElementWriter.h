#ifndef _IELEMENT_WRITER_H_
#define _IELEMENT_WRITER_H_

#include "Element.h"
#include <string>
#include <fstream>

class IElementWriter
{
public:
    IElementWriter() = default;
	IElementWriter(const std::string&);
	virtual ~IElementWriter() = default;

	virtual void AcceptElement(const Element&) = 0;
	virtual void Close() = 0;

    const std::string& GetPath() const { return _path; }

protected:
	std::ofstream _file{};
    std::string _path{};
};

IElementWriter::IElementWriter(const std::string& path)
:_path(path)
{
    _file.open(_path);
}

#endif