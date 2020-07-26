#include "TCPServer.h"
#define BACKLOG 100
#define MAX_BUFFER_SIZE 1024

using namespace gnet;

TCPServer::TCPServer(std::string Host, std::string Port, TServerCallback callback)
:ServerBase(Host, Port),
_callback(callback)
{}

TCPServer::~TCPServer()
{
    _Cleanup();
}
    
bool TCPServer::Init()
{
    freeaddrinfo(_info);
    _info = nullptr;
    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(_Host.c_str(), _Port.c_str(), &hint, &_info);
    if(status != 0){
        freeaddrinfo(_info);
        _info = nullptr;
        return false;
    }

    return true;
}

void TCPServer::Run()
{
    char buff[MAX_BUFFER_SIZE];
    while (true)
    {
        SOCKETFD listening = _CreateSocket();
        if(listening == -1){
            break;
        }

        SOCKETFD client = _WaitForConnection(listening);
        if(client != -1){
            close(listening);
            int bytes_received{};
            do
            {
                memset(buff, 0, MAX_BUFFER_SIZE);
                bytes_received = recv(client, buff, MAX_BUFFER_SIZE, 0);
                if(bytes_received > 0){
                    if(_callback != nullptr){
                        _callback(this, client, std::string(buff, 0, bytes_received));
                    }
                }

            } while (bytes_received > 0);
            close(client);
        }
    }
    
}

bool TCPServer::Restart()
{
    return false;
}

int TCPServer::Send(const SOCKETFD fd, const std::string& msg) const
{
    return send(fd, msg.c_str(), msg.size() - 1, 0);
}

void TCPServer::_Cleanup()
{
    freeaddrinfo(_info);
}

SOCKETFD TCPServer::_CreateSocket()
{
    if(_info != nullptr)
    {
        addrinfo* serv_info = _info;
        int serverfd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
        if(serverfd == -1) return -1;
        int opt = 1;
        if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ return -1; }

        if (bind(serverfd, (const sockaddr*)serv_info->ai_addr, serv_info->ai_addrlen) < 0){ return -1; }

        //set listening parameters
        if (listen(serverfd, BACKLOG) < 0){ return -1; }
        return serverfd;
    }
    return -1;
}

SOCKETFD TCPServer::_WaitForConnection(const SOCKETFD fd)
{
    if(fd != -1){
        return accept(fd, nullptr, nullptr);
    }
    return -1;
}
