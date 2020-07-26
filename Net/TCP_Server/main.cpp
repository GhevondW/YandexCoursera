#include <iostream>
#include "TCPServer.h"

using namespace std;
using namespace gnet;

void Resp(ConstServerPtr serv, int client_fd, const std::string& msg){
    serv->Send(client_fd, msg);
}

int main(){

    cout<<"...... TCP Server ......"<<endl;

    gnet::TCPServer server{"localhost", "54001", Resp};

    if(server.Init()){
        server.Run();
    }

    return 0;
}