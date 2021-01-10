#include <cstdint>
#include <cstdio>
#include <vector>
#include <iostream>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct RGBA {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};


int pack(RGBA pixel)
{
    int ret = pixel.r; ret <<= 8;
    ret += pixel.g; ret <<= 8;
    ret += pixel.b; ret <<= 8;
    ret += pixel.a;
    // uint8_t* addr = (uint8_t*)&ret;
    // *addr = pixel.r; ++addr;
    // *addr = pixel.g; ++addr;
    // *addr = pixel.b; ++addr;
    // *addr = pixel.a;
    return ret;
}

int pack(RGB pixel)
{
    return pack({pixel.r, pixel.g, pixel.b, 0xff});
}

int main(int argc, const char * argv[]){
    /*
     Write a function that will get any of the pixel types defined above (RGBA, RGB) and pack them in integer.
     Such that regardless of platform endianness pixel is written uniformly.
    */
   RGBA pixel{15,0,0,0};
    std::cout<<pack(pixel)<<std::endl;
    return 0;
}