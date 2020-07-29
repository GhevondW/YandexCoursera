#if 1
//
//  main.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/20/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//
#include "NetBase.h"
using namespace nbase;


void BindSocketWithHost()
{
    addrinfo hint = CreateAddrInfoHint();
    addrinfo* info;
    
    int getinfo_res = getaddrinfo("google.com",
                                  "3490",
                                  &hint,
                                  &info);
    if(getinfo_res != 0)
    {std::cerr<<"get addr info error = ["<<getinfo_res<<"]"<<std::endl; exit(1);}
    
    PrintAddrInfo(info);
    
    int sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    
    if(bind(sockfd, info->ai_addr, info->ai_addrlen) != 0)
    { std::cerr<<"bind error"<<std::endl; exit(1); }
    
    freeaddrinfo(info);
}

int main()
{
    BindSocketWithHost();
    return 0;
}
#endif
