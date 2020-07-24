#include <iostream>
#include "/home/ghevondw/Desktop/CPP/YandexCoursera/Net/Net Base/NetBase.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "Database.h"


//SYNTAX
// ADD:"value"
// PRINT

using namespace std;

#define PORT "54001"
#define MAX_BUFFER_SIZE 1024
#define BACKLOG 100

int main()
{

    db::Database database{};

    //createing localaddresinfo
    addrinfo hint = nbase::CreatePassiveAddrInfoHint(AF_INET);
    addrinfo* serv_info{nullptr};

    int getaddrstat = getaddrinfo(nullptr, PORT, &hint, &serv_info);

    if(getaddrstat != 0){
        perror("[ERROR GETADDRINFO]");
        exit(EXIT_FAILURE);
    }

    nbase::PrintAddrInfo(serv_info);

    //Create socket
    int serverfd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
    if(serverfd == -1){
        perror("[ERROR CREATE SOCKET DESCRIPTOR]");
        exit(EXIT_FAILURE);
    }

#if 1 //TODO
    // Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("[ERROR SETSOCKOPT]");
        exit(EXIT_FAILURE);
    }
#endif

    //Binding

    if (bind(serverfd, (const sockaddr*)serv_info->ai_addr, serv_info->ai_addrlen) < 0)
    {
        perror("[ERROR BIND]");
        exit(EXIT_FAILURE);
    }
    
    //set listening parameters
    if (listen(serverfd, BACKLOG) < 0)
    {
        perror("[ERROR LISTEN]");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(serv_info);

    int clientfd{-1};
    sockaddr_storage client_address;
    socklen_t client_addr_len = sizeof(client_address);
    memset(&client_address, 0, client_addr_len);
    char s[INET6_ADDRSTRLEN];

    while (true)
    {
        cout<<"Waiting..."<<endl;
        clientfd = accept(serverfd, (sockaddr*)&client_address, &client_addr_len);
        if(clientfd == -1){
            perror("[ERROR ACCEPT]");
            continue;
        }

        // inet_ntop(client_address.ss_family,
        //  get_in_addr((sockaddr*)&client_address),
        //   s, sizeof(s));

        cout<<"...[OK]..."<<endl;

        char buffer[MAX_BUFFER_SIZE];
        long result_bytes{0};
        result_bytes = read(clientfd, buffer, MAX_BUFFER_SIZE);

        std::string request = nbase::GetString(buffer, result_bytes);
        
        database.Handle(db::CreateRequest(request));

        // char res[] = "Good!!!";
        // send(clientfd , res , strlen(res) , 0 );
        // printf("Hello message sent\n");
        close(clientfd);
    }
    return 0;
}