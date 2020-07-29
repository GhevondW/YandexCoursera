#include <iostream>
#include "TCPServer.h"
#include "ThreadPool.h"

using namespace std;
using namespace gnet;

void Resp(ConstServerPtr serv, int client_fd, const std::string& msg){
    msg != "END" ? serv->Send(client_fd, msg) : serv->CloseSocketFd(client_fd);
}

int main(){

    cout<<"...... TCP Server ......"<<endl;


    gnet::TCPServer server{"localhost", "54001", Resp};

    if(server.Init()){
        server.Run();
    }

    // gnet::TPool pool{};
    // pool.EnqueueTask(Task1);
    // pool.EnqueueTask(Task2);
    // pool.EnqueueTask(Task3);
    // pool.EnqueueTask(Task4);

    return 0;
}