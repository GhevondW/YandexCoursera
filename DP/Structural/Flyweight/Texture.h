#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdlib.h> 
#include <iostream>

enum TYPE
{
    ONE = 0,
    TWO = 1,
    THREE = 2
};

class Texture
{
public:
    Texture(TYPE type = TYPE::ONE);
    Texture(const Texture& other) = delete;
    Texture(Texture&& other);

    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&);

    ~Texture();

    const unsigned char* GetData() const { return _data; }
    void Draw() const 
    {
        std::cout<<"Address:"<<(long long)_data<<", Width:"<<_w<<", Height:"<<_h<<std::endl;
    }

private:
    void _Init();
private:
    unsigned char* _data{nullptr};
    int _w{};
    int _h{};
};

Texture::Texture(TYPE type /*= TYPE::ONE*/)
{
    if(type == TYPE::ONE)
    {
        _w = 10;
        _h = 10;
    }
    else if(type == TYPE::TWO){
        _w = 20;
        _h = 20;
    }
    else{
        _w = 30;
        _h = 30;
    }
    _Init();
}

Texture::~Texture()
{
    free(_data);
}

void Texture::_Init()
{
    _data = (unsigned char*)malloc(_w*_h);
}

Texture::Texture(Texture&& other)
:_data(other._data),
_w(other._w),
_h(other._h)
{
    other._data = nullptr;
    other._w = 0;
    other._h = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    free(_data);
    _data = other._data;
    _w = other._w;
    _h = other._h;

    other._data = nullptr;
    other._w = 0;
    other._h = 0;

    return *this;
}

#endif