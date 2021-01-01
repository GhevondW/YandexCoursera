#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <string>
#include <memory>
#include <utility>
#include <iostream>

//Element represents Student info
class Element;

struct IElemBuilder
{
    virtual ~IElemBuilder() = default;
    virtual IElemBuilder& SetFirstName(const std::string&) = 0;
    virtual IElemBuilder& SetLastName(const std::string&) = 0;
    virtual IElemBuilder& SetGroupName(const std::string&) = 0;
    virtual IElemBuilder& SetRating(size_t) = 0;
    virtual IElemBuilder& SetPubCount(size_t) = 0;
    virtual Element Build() = 0;
    virtual std::shared_ptr<Element> BuildPtr() = 0;
};

class ElemBuilder : public IElemBuilder
{
    friend class Element;
private:
    
    ElemBuilder(/* args */);

public:
    ~ElemBuilder();

    IElemBuilder& SetFirstName(const std::string& fn) override;
    IElemBuilder& SetLastName(const std::string& ln) override;
    IElemBuilder& SetGroupName(const std::string& gn) override;
    IElemBuilder& SetRating(size_t r) override;
    IElemBuilder& SetPubCount(size_t p) override;
    Element Build() override;
    std::shared_ptr<Element> BuildPtr() override;

private:
    Element* _elem{};
};


class Element
{
    friend class ElemBuilder;
public:

    static ElemBuilder Make()
    {
        return ElemBuilder{};
    }

    Element(const Element& other) = default;
    Element(Element&& other) = default;
    Element& operator=(const Element& other) = default;
    Element& operator=(Element&& other) = default;
    ~Element(){}

    auto GetFirstName() const -> const std::string& { return _firstName; }
    auto GetLastName() const -> const std::string& { return _lastName; }
    auto GetGroupName() const -> const std::string& { return _groupName; }
    auto GetRating() const -> const size_t { return _rating; }
    auto GetPublicationsCount() const -> size_t { return _publications; }

    auto Print() const -> void
    {
        std::cout
        <<"[FN]:"
        <<_firstName
        <<", [LN]:"
        <<_lastName
        <<", [GN]:"
        <<_groupName
        <<", [R]:"
        <<_rating
        <<", [P]:"
        <<_publications
        <<std::endl;
    }

private:

    Element(/* args */) = default;

private:
    std::string _firstName{};
    std::string _lastName{};
    std::string _groupName{};
    size_t      _rating{};
    size_t      _publications{};
};

ElemBuilder::ElemBuilder(/* args */)
:_elem(new Element())
{
    
}

ElemBuilder::~ElemBuilder()
{
    if(_elem){
        delete _elem;
        _elem = nullptr;
    }
}

IElemBuilder& ElemBuilder::SetFirstName(const std::string& fn)
{
    _elem->_firstName = fn;
    return *this;
}

IElemBuilder& ElemBuilder::SetLastName(const std::string& ln)
{
    _elem->_lastName = ln;
    return *this;
}

IElemBuilder& ElemBuilder::SetGroupName(const std::string& gn)
{
     _elem->_groupName = gn;
    return *this;
}

IElemBuilder& ElemBuilder::SetRating(size_t r)
{
    _elem->_rating = r;
    return *this;
}

IElemBuilder& ElemBuilder::SetPubCount(size_t p)
{
    _elem->_publications = p;
    return *this;
}

Element ElemBuilder::Build()
{
    Element ret{std::move(*_elem)};
    return ret;
}

std::shared_ptr<Element> ElemBuilder::BuildPtr()
{
    std::shared_ptr<Element> ret(_elem);
    _elem = nullptr;
    return ret;
}

#endif
