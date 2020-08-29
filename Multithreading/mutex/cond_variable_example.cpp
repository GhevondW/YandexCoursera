#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <atomic>

class IO
{
public:
    IO() = default;
    ~IO() = default;
    
public:

    void Run()
    {

        _stop = false;

        _input = std::thread(&IO::_Input, this);
        _processing = std::thread(&IO::_Processing, this);
        

        _input.join();
        _processing.join();
    }

private:

    void _Input()
    {
        std::cout<<"[Input]"<<std::endl;
        std::string data;
        while (true)
        {
            std::cout<<"Waiting Input..."<<std::endl;
            std::getline(std::cin, data);
            if(data == "END")
            {
                _stop = true;
                _cond.notify_one();
                break;
            }

            {
                std::lock_guard<std::mutex> lock(_data_lock);
                _data.push(data);
                _cond.notify_one();
            }
        }
        
    }

    bool _CondCheck()
    {
        return !_data.empty() || _stop;
    }

    void _DoProcessing(std::string data)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout<<"****Processor["<<data<<"]****"<<std::endl;
    }

    void _Processing()
    {
        while(true){
            std::cout<<"[Processing]"<<std::endl;
            std::unique_lock<std::mutex> lock{_data_lock};
            std::cout<<"Waiting Data..."<<std::endl;
            
            _cond.wait(lock,[this](){
                return this->_CondCheck();
            });

            std::cout<<"there is a Data..."<<std::endl;

            if(_stop){
                std::cout<<"End Processing"<<std::endl;
                break;
            }

            std::string data = _data.front();
            _data.pop();
            lock.unlock();

            _DoProcessing(std::move(data));
        }
    }

private:
    std::queue<std::string> _data;
    std::thread             _input;
    std::thread             _processing;
    std::mutex              _data_lock;
    std::condition_variable _cond;
    std::atomic<bool>       _stop;
};

int main(){

    IO io{};

    io.Run();

    return 0;
}