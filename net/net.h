//
// Created by zhenbiao.cai on 2016/11/21.
//

#ifndef CODE_NET_H
#define CODE_NET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

int socket_bind(const char* ip, int port);


#endif //CODE_NET_H
