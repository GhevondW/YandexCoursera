#include "Shape.h"
#include "IVisitor.h"

void Rect::Accept(const IVisitor* visitor) const
{
    visitor->VisitCommand(*this);
}

void Circle::Accept(const IVisitor* visitor) const
{
    visitor->VisitCommand(*this);
}

void Ellipse::Accept(const IVisitor* visitor) const
{
    visitor->VisitCommand(*this);
}

void Triangle::Accept(const IVisitor* visitor) const
{
    visitor->VisitCommand(*this);
}