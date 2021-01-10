#include <cstdint>
#include <cstdio>
#include <vector>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
}

struct RGBA {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}

int pack(RGB pixel);
int pack(RGBA pixel);

int main(int argc, const char * argv[]){
    /*
     Write a function that will get any of the pixel types defined above (RGBA, RGB) and pack them in integer.
     Such that regardless of platform endianness pixel is written uniformly.
    */
    
    return 0;
}
