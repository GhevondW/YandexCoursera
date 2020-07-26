#include "/home/ghevond/Desktop/CPP/YandexCoursera/Net/Net Base/NetBase.h"
#include <iostream>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

#define PORT "54001"
#define MAX_DATA_LENGTH 100

int main(){
    cout<<"Client"<<endl;

    addrinfo hint = nbase::CreatePassiveAddrInfoHint(AF_INET);
    addrinfo* info{nullptr};

    int getaddr_stat = getaddrinfo(nullptr, PORT, &hint, &info);
    if(getaddr_stat != 0){
        perror("[GETADDRINFO ERROR]");
        exit(1);
    }

    int sock_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if(sock_fd == -1){
        perror("[SOCKET ERROR]");
        exit(1);
    }
    cout<<"[SOCK]"<<sock_fd<<endl;

    if(connect(sock_fd, info->ai_addr, info->ai_addrlen)){
        close(sock_fd);
        perror("[CONNECT ERROR]");
        exit(1);
    }

    if(info == nullptr){
        perror("[FAILED TO CONNECT]");
        close(sock_fd);
        exit(1);
    }

    char s[INET6_ADDRSTRLEN];
    inet_ntop(info->ai_family, ((struct sockaddr *)info->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(info);

    char buff[MAX_DATA_LENGTH];
    int bytes_sent{0};
    if(bytes_sent = recv(sock_fd, buff, MAX_DATA_LENGTH - 1, 0) == -1){
        perror("[RECV ERROR]");
        exit(1);
    }

    buff[MAX_DATA_LENGTH] = '\0';

    printf("client: received ’%s’\n", buff);
    
    close(sock_fd);

    return  0;
}