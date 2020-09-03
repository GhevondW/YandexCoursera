#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

namespace
{
    
std::atomic_flag flag = ATOMIC_FLAG_INIT;

} // namespace

//this is a bad mutex example with while loop
//buth this is workable example
class spinlock_mutex
{
public:
    spinlock_mutex()
    :_flag(ATOMIC_FLAG_INIT)
    {}

    void lock()
    {
        while (_flag.test_and_set());
    }

    void unlock()
    {
        _flag.clear();
    }

private:
    std::atomic_flag _flag;
};

spinlock_mutex mtx;

void Run()
{
    static int a = 0;
    mtx.lock();
    for (size_t i = 0; i < 20; i++)
    {
        /* code */
        std::cout<<++a<<std::endl;
    }
    mtx.unlock();
}
/***
 * 
 *
 *  returns the current result and sets the flag to 1
    //test_and_set();
    
    //set the flag to 0 without returning the result
    //clear();
*/
int main()
{
    printf("Atomic Flag\n");

#if 0 //example of atomic flag functional

    cout<<flag.test_and_set()<<endl;
    cout<<flag.test_and_set()<<endl;
    cout<<flag.test_and_set()<<endl;

    // flag.clear();

    cout<<flag.test_and_set()<<endl;

#endif

    std::thread t1{Run};
    std::thread t2{Run};



    t1.join();
    t2.join();
    return 0;
}