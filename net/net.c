//
// Created by zhenbiao.cai on 2016/11/21.
//

#include "net.h"

int socket_bind(const char* ip, int port) {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > listenfd) {
        perror("socket error");
        exit(1);
    }
    struct sockaddr_in svraddr;
    bzero(&svraddr, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    //inet_pton(AF_NET, ip, &svraddr.sin_family);
    inet_pton(AF_INET, ip, &svraddr);
    svraddr.sin_port = htons(port);
    if(0 > bind(listenfd, (struct sockaddr*)&svraddr, sizeof(svraddr))) {
        perror("bind error");
        exit(1);
    }
    return listenfd;
}

