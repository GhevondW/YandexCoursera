//
//  main.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/20/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#include "NetBase.h"

using namespace std;
using namespace nbase;

void ConnectToHost(std::string host)
{
    addrinfo hint = CreateAddrInfoHint();
    hint.ai_protocol = 6;
    addrinfo* info{nullptr};
    
    int status = getaddrinfo(host.c_str(),
                            "3940",
                             &hint,
                             &info);
    
    if(status != 0) throw "getaddrinfo error";
    
    PrintAddrInfo(info);
    
    int socket_descriptor = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    
    int connect_stat = connect(socket_descriptor, info->ai_addr, info->ai_addrlen);
    if(connect_stat != 0) throw "connect error";
    
    freeaddrinfo(info);
}

int main(){
    
    ConnectToHost("google.com");
    
    return 0;
}
