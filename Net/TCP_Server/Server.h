#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <array>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <sys/uio.h>
#include <unistd.h>

namespace gnet
{
    using SOCKETFD  = int;
    using CSOCKETFD = const int;

    struct ServerBase
    {
    public:

        ServerBase(std::string Host, std::string Port):_Host(Host), _Port(Port){};
        virtual             ~ServerBase(){};

        virtual auto        Init() -> bool = 0;
        virtual auto        Run() -> void = 0;
        virtual auto        Restart() -> bool = 0;
        virtual int         Send(CSOCKETFD fd, const std::string&) const = 0;
        virtual auto        CloseSocketFd(CSOCKETFD fd) const -> int = 0;

        const std::string&  GetHost() const { return _Host; }
        const std::string&  GetPort() const { return _Port; }

    private:

        virtual void        _Cleanup() = 0;

    protected:
        const std::string   _Host;
        const std::string   _Port;
    };
}

#endif