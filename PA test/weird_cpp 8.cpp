#include <cstdint>
#include <cstdio>
#include <iostream>

int counter = 0;

struct A {
    int foo = counter++;
    
    A() {
        std::cout << "I'm A and I was created with foo = " << foo << std::endl;
    }
    
    virtual void printContents() {
        std::cout << "I'm A and I contain foo = " << foo<< std::endl;
    }
};

struct B : A {
    int bar = counter++;
    
    B() {
        std::cout << "I'm B and I was created with bar = " << bar << std::endl;
    }
    
    void printContents() override {
        A::printContents();
        std::cout << "I'm B and I contain bar = " << bar << std::endl;
    }
};

int main(int argc, const char * argv[]){
    /*
        What is incorrect in the code below? How to fix it? Why it produces different results depending on the ordering of b1, b2?
        Some logs were added to help you in this task!
     */
    
    {
        counter = 0;
        B b;
        A a = b;
        a.printContents();
    
        std::cout << std::endl;
    }
    {
        counter = 0;
        B b1;
        B b2;
        A& a_ref = b2;
        a_ref = b1;
        
        a_ref.printContents();
        
        std::cout << std::endl;
    }
    {
        counter = 0;
        B b2;
        B b1;
        A& a_ref = b2;
        a_ref = b1;
        
        a_ref.printContents();
        
        std::cout << std::endl;
    }
    

    return 0;
}
