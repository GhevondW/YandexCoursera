#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#include "Server.h"
#include <functional>
#include <memory>
#include <mutex>
#include "GlobalDefines.h"

namespace gnet
{

    class TCPServer;
    template<size_t N>
    class ThreadPool;

    using TPool = ThreadPool<MAX_WORKERS_COUNT>;

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
        int     Send(CSOCKETFD fd, const std::string&) const override;
        int     CloseSocketFd(CSOCKETFD fd) const override;

    private:

        void            _Cleanup() override;
        SOCKETFD        _CreateSocket();
        SOCKETFD        _WaitForConnection(const SOCKETFD fd);

    private:
        TServerCallback                 _callback{nullptr};
        addrinfo*                       _info{nullptr};
        std::unique_ptr<TPool>          _thread_pool{nullptr};
        mutable std::mutex              _lock_close_fd{};
    };
    
} 

#endif