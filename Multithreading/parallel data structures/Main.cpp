#include <iostream>
#include "queue.h"
#include "lookup_table.h"
#include <vector>
#include "list_lookup_table.h"
#include "basic_thread_pool.h"
#include <future>
#include "thread_pool_fw.h"

using namespace std;

static int counter = 0;

class A
{
public:
	A() { cout << "A ctor" << endl; counter++; };
	~A() { cout << "A dtor" << endl;  counter--; };
	A(const A& other) = delete;// { cout << "A copy ctor" << endl; }
	A(A&& other) { cout << "A move ctor" << endl; }
	A& operator=(const A& other) = delete;//{ cout << "A copy" << endl; }
	A& operator=(A&& other) { cout << "A move" << endl; }
};

static const std::vector<int> values = {1,2,3,4,5,6,7,8};
static std::vector<int> pop;
static mutex pop_mutex;
static parallel::queue<int> gQueue;

void RunPush(std::vector<int>& data)
{
	while (true)
	{
		//std::this_thread::sleep_for(chrono::milliseconds(std::rand()%10));
		gQueue.Push(data.front());
		data.erase(data.begin());
		if (data.empty()) return;
	}
}

void RunPop()
{
	while (true)
	{
		auto res = gQueue.TryPop();
		
		std::lock_guard<std::mutex> lg{ pop_mutex };
		if (pop.size() == 12) {
			break;
		}
		if (res) {
			
			pop.push_back(*res);
			cout << std::this_thread::get_id() <<":"<<*res<< endl;
		}
	}
}

parallel::basic_thread_pool pool;


void f()
{
	std::cout << std::this_thread::get_id()<<std::endl;
}

void Run()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%4));
	for (size_t i = 0; i < 20; i++)
	{
		pool.SubmitTask(f);
	}
}


int main()
{

	
	//std::vector<std::thread> threads;

	//for (size_t i = 0; i < 10; i++)
	//{
	//	threads.push_back(std::thread{Run});
	//}

	//for (size_t i = 0; i < threads.size(); i++)
	//{
	//	threads[i].join();
	//}
	//std::cin.get();

	parallel::thread_pool_fw fw;
	fw.Submit([]() {return false; });

}