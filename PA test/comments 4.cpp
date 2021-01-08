#include <cstdint>
#include <cstdio>
#include <algorithm>

void copy_string_without_comments(const char* source, char *dest, std::size_t length);

int main(int argc, const char * argv[]){
    /*
      Write C style comment filtering method, which will remove comments starting with // like in C/C++.
      copy_string_without_comments(const char* source, char *dest, size_t length);
     */
    
    char dest[256];
    const char* test = "This is string\nWith //comment\nAnd multiline text";
    
    copy_string_without_comments(test, dest, sizeof(dest));
    
    printf("Before: %s\n", test);
    printf("After: %s\n", dest);
    
    assert(strcmp(dest, "This is string\nWith \nAnd multiline text") == 0);
    
    return 0;
}
