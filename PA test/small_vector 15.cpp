#include <cassert>
#include <cstdint>

int main(int argc, const char * argv[]){
    /*
     SmallVector is a vector optimized for small arrays. This optimization comes from NOT performing heap allocations for a limited number of elements, instead it stores them on the stack.
     In the event that you add more elements than are described to be allocated using automatic storage it will fall back to the behavior of std::vector and allocate larger and larger arrays.
     */
    
    
    SmallVector<int, 10> smallVector;
    static_assert(sizeof(int) * 10 <= sizeof(smallVector)); // Small vector should have enough room in itself for elements.
    
    for(int i = 0; i < 10; i++)
    {
        smallVector.push_back(i);
        
        // Check that element i is on the stack
        assert((size_t)(void*)&smallVector <= (size_t)&smallVector[i] && (size_t)&smallVector[i] <= ((size_t)&smallVector) + sizeof(smallVector));
    }
    
    // No heap allocations have been performed up to this point.
    
    smallVector.push_back(10); // Only 10 spaces for non heap allocated elements, so the push_back above causes a heap allocation.
    
    for(int i = 0; i < 11; i++)
    {
        // Check that element is right
        assert(i == smallVector[i]);
        
        // Check that element i is NOT on the stack
        assert(!((size_t)(void*)&smallVector < (size_t)&smallVector[i] && (size_t)&smallVector[i] < ((size_t)&smallVector) + sizeof(smallVector)));
    }
    
    /*
     Your implementation is required to support two simple operations, just a push_back and an index operator.
     It should get number of elements which are stored on the stack in the second template parameter.
     
     template <typename T, std::size_t NumberOfElementsOnStack>
     class SmallVector {
        // ....
        public:
        void push_back(const T &element) { ... }
        const T& operator[](size_t index) const { ... }
     };
     */
    
    return 0;
}
