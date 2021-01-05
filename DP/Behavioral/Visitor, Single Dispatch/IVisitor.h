#ifndef _IVISITOR_H_
#define _IVISITOR_H_

#include "Shape.h"

struct IVisitor
{
    IVisitor() = default;
    virtual ~IVisitor() = default;

    virtual void VisitCommand(const Rect& rect) const = 0;
    virtual void VisitCommand(const Circle& rect) const = 0;
    virtual void VisitCommand(const Ellipse& rect) const = 0;
    virtual void VisitCommand(const Triangle& rect) const = 0;
};

class XMLVisitor : public IVisitor
{
private:
    /* data */
public:
    XMLVisitor(/* args */) = default;
    ~XMLVisitor() = default;

    void VisitCommand(const Rect& rect) const override
    {
        std::cout<<"XML Visitor: Rect"<<std::endl;
    }
    void VisitCommand(const Circle& rect) const override
    {
        std::cout<<"XML Visitor: Circle"<<std::endl;
    }
    void VisitCommand(const Ellipse& rect) const override
    {
        std::cout<<"XML Visitor: Ellipse"<<std::endl;
    }
    void VisitCommand(const Triangle& rect) const override
    {
        std::cout<<"XML Visitor: Triangle"<<std::endl;
    }
};




#endif