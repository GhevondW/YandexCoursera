//
//  NetBase.h
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/20/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#ifndef NetBase_h
#define NetBase_h

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

namespace nbase {

using AddrInfoUniquePtr = std::unique_ptr<addrinfo, std::function<void(addrinfo*)>>;
addrinfo CreateAddrInfoHint(int family = AF_UNSPEC, int sock_type = SOCK_STREAM);
addrinfo CreatePassiveAddrInfoHint(int family = AF_UNSPEC, int sock_type = SOCK_STREAM);
void PrintAddrInfo(const addrinfo*);

}

#endif /* NetBase_h */
