#include <iostream>
#include "queue.h"
#include <vector>

using namespace std;

static int counter = 0;

class A
{
public:
	A() { cout << "A ctor" << endl; counter++; };
	~A() { cout << "A dtor" << endl;  counter--; };
	//A(const A& other) { cout << "A copy ctor" << endl; }
	//A(A&& other) { cout << "A move ctor" << endl; }
	//A& operator=(const A& other) { cout << "A copy" << endl; }
	//A& operator=(A&& other) { cout << "A move" << endl; }
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

int main()
{
	//f(A{});


	std::vector<int> v1{ 1,2,3,4,9,10 };
	std::vector<int> v2{ 5,6,7,8,11,12 };

	std::thread t1{RunPush, std::ref(v1)};
	std::thread t2{RunPush, std::ref(v2)};

	std::thread t3{ RunPop };
	std::thread t4{ RunPop };

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}