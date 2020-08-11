#include <iostream>
#include <thread>
#include <mutex>
#include "hierarchical_mutex.h"

std::hierarchical_mutex mutex_a(1000);
std::hierarchical_mutex mutex_b(500);

using namespace std;
#define ERROR "ERROR"

void RightLock()
{
    lock_guard<hierarchical_mutex> _locka(mutex_a);
    lock_guard<hierarchical_mutex> _lockb(mutex_b);
}

void WrongLock()
{
    lock_guard<hierarchical_mutex> _lockb(mutex_b);
    lock_guard<hierarchical_mutex> _locka(mutex_a);
}

int main()
{
    printf("H mutex \n");

    try
    {
        RightLock();
    }
    catch(const std::exception& e)
    {
        std::cerr << ERROR << '\n';
    }
    

     try
     {
         WrongLock();
     }
     catch(const std::exception& e)
     {
         std::cerr << ERROR << '\n';
     }

    return 0;
}