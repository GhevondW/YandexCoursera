//
//  main.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/21/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#include "NetBase.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;
using namespace nbase;

#define PORT "54000"
#define BACKLOG 10
#define MAX_BUFFER_SIZE 1024

int main()
{
    //address creation
    addrinfo hint = CreatePassiveAddrInfoHint(AF_INET);
    addrinfo* info{nullptr};
    
    if(getaddrinfo(nullptr,
                   PORT,
                   &hint,
                   &info) == -1)
    {
        perror("Error getaddrinfo");
        exit(EXIT_FAILURE);
    }
    
    PrintAddrInfo(info);
    
    //Createing socket file descriptop
    int server_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if(server_fd == -1){
        perror("Error socket descriptor creation");
        exit(EXIT_FAILURE);
    }
    
#if 0 //TODO
    // Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
#endif
    
    //Socket binding with port
    
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (const sockaddr*)info->ai_addr, info->ai_addrlen) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    //set listening parameters
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    //accept
    int client_socket{-1};
    sockaddr_storage client_address;
    socklen_t client_addr_len = sizeof(client_address);
    memset(&client_address, 0, client_addr_len);
    
    client_socket = accept(server_fd, (sockaddr*)&client_address, &client_addr_len);
    if (client_socket < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    char buffer[MAX_BUFFER_SIZE];
    long result_bytes{0};
    result_bytes = read( client_socket, buffer, MAX_BUFFER_SIZE);
    printf("%s\n",buffer );
    
    char res[] = "Good!!!";
    send(client_socket , res , strlen(res) , 0 );
    printf("Hello message sent\n");
    
    freeaddrinfo(info);
    return 0;
}
