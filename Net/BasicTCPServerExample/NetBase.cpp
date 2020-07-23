//
//  NetBase.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/20/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#include "NetBase.h"

using namespace std;

namespace nbase {

addrinfo CreateAddrInfoHint(int family /*= AF_UNSPEC*/, int sock_type /*= SOCK_STREAM*/)
{
    addrinfo ret;
    memset(&ret, 0, sizeof(ret));
    
    ret.ai_family = family;
    ret.ai_socktype = sock_type;
    
    return ret;
}

addrinfo CreatePassiveAddrInfoHint(int family /*= AF_UNSPEC*/, int sock_type /*= SOCK_STREAM*/)
{
    addrinfo ret;
    memset(&ret, 0, sizeof(ret));
    
    ret.ai_family = family;
    ret.ai_socktype = sock_type;
    ret.ai_flags = AI_PASSIVE;
    
    return ret;
}

void PrintAddrInfo(const addrinfo* info)
{
    if(info == nullptr) throw std::invalid_argument{"info is nullptr"};
    
    char ipstr[INET6_ADDRSTRLEN];
    char sport[INET6_ADDRSTRLEN];
//    std::cout<<"Host = "<<info->ai_canonname<<std::endl;
    std::cout<<"-------------------Print Addrinfo-----------------------"<<endl;
    
    const addrinfo* tmp = info;
    
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
    
}

}

