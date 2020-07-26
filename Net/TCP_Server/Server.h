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
    using SOCKETFD = int;

    struct ServerBase
    {
    public:

        ServerBase(std::string Host, std::string Port):_Host(Host), _Port(Port){};
        virtual             ~ServerBase(){};

        virtual bool        Init() = 0;
        virtual void        Run() = 0;
        virtual bool        Restart() = 0;
        virtual int         Send(SOCKETFD fd, const std::string&) const = 0;

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