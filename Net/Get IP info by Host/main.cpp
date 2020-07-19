//
//  main.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/19/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

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
#include <functional>

using namespace std;

using AddrInfoUniquePtr = std::unique_ptr<addrinfo, function<void(addrinfo*)>>;

addrinfo CreateAddrInfoHint(int family = AF_UNSPEC, int sock_type = SOCK_STREAM)
{
    addrinfo ret;
    memset(&ret, 0, sizeof(ret));
    
    ret.ai_family = family;
    ret.ai_socktype = sock_type;
    
    return ret;
}

void PrintIPInfoByHost(const std::string& host, int port)
{
    addrinfo hint = CreateAddrInfoHint();
    addrinfo* info{nullptr};
    char ipstr[INET6_ADDRSTRLEN];
//    AddrInfoUniquePtr info{nullptr, [](addrinfo* obj){ freeaddrinfo(obj); }};
    
    int status = getaddrinfo(host.c_str(),
                 std::to_string(port).c_str(),
                 &hint,
                 &(info));
    
    if(status != 0){
        std::cerr<<"Eroor Status code = ["<<status<<"]"<<std::endl;
        exit(1);
    }
    
    std::cout<<"Host = "<<host<<std::endl;
    
    addrinfo* tmp = info;
    
    while (tmp != nullptr) {
        
        void *addr;
        string ipver;
        in_port_t port;
        
        if(tmp->ai_family == AF_INET){ //IPv4
            sockaddr_in *ipv4 = (sockaddr_in*)tmp->ai_addr;
            addr = &(ipv4->sin_addr);
            port = ipv4->sin_port;
            ipver = "IPv4";
        }
        else{
            sockaddr_in6 *ipv6 = (sockaddr_in6 *)tmp->ai_addr;
            addr = &(ipv6->sin6_addr);
            port = ipv6->sin6_port;
            ipver = "IPv6";
        }
        
        inet_ntop(tmp->ai_family, addr, ipstr, sizeof(ipstr));
        cout<<ipver.c_str()<<" [ port = "<<port<<" ]:"<<ipstr<<endl;
        
        tmp = tmp->ai_next;
    }
    
    freeaddrinfo(info);
}

int main()
{
    std::cout<<"Hello Net!"<<std::endl;
    
    PrintIPInfoByHost("www.gmail.com", 80);
    
    return 0;
}
