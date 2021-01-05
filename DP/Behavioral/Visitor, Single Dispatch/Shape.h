#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

struct IVisitor;

enum Color
{
    RED,
    GREEN,
    BLUE
};

class Shape
{
public:
    Shape(/* args */) = default;
    Shape(int x, int y, Color color)
    :_x(x),
    _y(y),
    _color(color)
    {}
    virtual ~Shape() = default;

    virtual void Draw() const = 0;
    virtual void Move(int x, int y) = 0;
    virtual void Accept(const IVisitor* visitor) const = 0;

private:
    int _x{};
    int _y{};
    Color _color{};
};

class Rect : public Shape
{
private:
    /* data */
public:
    Rect(/* args */) = default;
    Rect(int x, int y, Color c): Shape(x, y, c){};
    ~Rect() = default;

    void Draw() const override
    {
        std::cout<<"[Rect] Draw"<<std::endl;
    }

    void Move(int x, int y) override
    {
        std::cout<<"[Rect] Move"<<std::endl;
    }

    void Accept(const IVisitor* visitor) const override;
};

class Circle : public Shape
{
private:
    /* data */
public:
    Circle(/* args */) = default;
    Circle(int x, int y, Color c): Shape(x, y, c){};
    ~Circle() = default;

    void Draw() const override
    {
        std::cout<<"[Circle] Draw"<<std::endl;
    }

    void Move(int x, int y) override
    {
        std::cout<<"[Circle] Move"<<std::endl;
    }

    void Accept(const IVisitor* visitor) const override;
};

class Ellipse : public Shape
{
private:
    /* data */
public:
    Ellipse(/* args */) = default;
    Ellipse(int x, int y, Color c): Shape(x, y, c){};
    ~Ellipse() = default;

    void Draw() const override
    {
        std::cout<<"[Ellipse] Draw"<<std::endl;
    }

    void Move(int x, int y) override
    {
        std::cout<<"[Ellipse] Move"<<std::endl;
    }

    void Accept(const IVisitor* visitor) const override;
};

class Triangle : public Shape
{
private:
    /* data */
public:
    Triangle(/* args */) = default;
    Triangle(int x, int y, Color c): Shape(x, y, c){};
    ~Triangle() = default;

    void Draw() const override
    {
        std::cout<<"[Triangle] Draw"<<std::endl;
    }

    void Move(int x, int y) override
    {
        std::cout<<"[Triangle] Move"<<std::endl;
    }

    void Accept(const IVisitor* visitor) const override;
};

#endif