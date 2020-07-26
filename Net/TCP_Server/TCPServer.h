#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#include "Server.h"
#include <functional>

namespace gnet
{

    class TCPServer;

    using ConstServerPtr = const TCPServer* const;
    using TServerCallback = std::function<void(ConstServerPtr, const SOCKETFD, const std::string)>;

    class TCPServer: public ServerBase
    {
    public:
        TCPServer(std::string Host, std::string Port, TServerCallback callback);
        ~TCPServer();
    
        bool    Init() override;
        void    Run() override;
        bool    Restart() override;
        int     Send(const SOCKETFD fd, const std::string& msg) const override;

    private:

        void            _Cleanup() override;
        SOCKETFD        _CreateSocket();
        SOCKETFD        _WaitForConnection(const SOCKETFD fd);

    private:
        TServerCallback _callback{nullptr};
        addrinfo*       _info{nullptr};
    };
    
} 

#endif