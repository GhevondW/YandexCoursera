#include <cstdint>
#include <cstdio>

template<typename T>
void bytes_swap(T &element);

int main(int argc, const char * argv[]){
    /*
     Write a template method, that will convert representation of variable in memory from big-endian to little-endian and vice-versa.
     
     Big-endian and little-endian are terms that describe the order in which a sequence of bytes are stored in 
     computer memory. Big-endian is an order in which the "big end" 
     (most significant value in the sequence) is stored first (at the lowest storage address). 
     Little-endian is an order in which the "little end" (least significant value in the sequence) is stored first. 
     For example, in a big-endian computer, the two bytes required for the hexadecimal number 4F52 
     would be stored as 4F52 in storage (if 4F is stored at storage address 1000, for example, 52 will be at address 1001). 
     In a little-endian system, it would be stored as 524F (52 at address 1000, 4F at 1001).
     
     template<typename T>
     void bytes_swap(&T element);
    */
    
    return 0;
}
