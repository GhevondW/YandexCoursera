#include <iostream>
#include <list>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

std::list<int>  gList;
std::mutex      gMutex;

void AddToList(int value)
{
    std::lock_guard<std::mutex> lock(gMutex);
    gList.push_back(value);
}

bool Find(int value)
{
    lock_guard<mutex> lock(gMutex);
    return std::find(begin(gList), end(gList), value) != end(gList);
}

int main(){
    cout<<"Hello world"<<endl;
    return 0;
}