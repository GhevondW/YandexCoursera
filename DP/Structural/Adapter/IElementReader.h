#ifndef _I_ELEMENT_READER_H_
#define _I_ELEMENT_READER_H_

struct IElementReader
{
    IElementReader() = default;
    virtual ~IElementReader() = default;

    auto HasNext() const -> bool;
    auto ReadNext() const -> void;
};


#endif