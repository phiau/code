//
// Created by zhenbiao.cai on 2016/11/21.
// socket 服务端，用线程来处理客户端的请求
//

#include "net.h"

void sock_thread(void *psockfd) {
    char buf[10] = {0};  //客户单发送的数据如果太大，将会被分成几次接收
    int recvSize;
    int sockfd = *(int *)psockfd;
    while(0 < (recvSize = read(sockfd, buf, 10))) {
        printf("recv a msg from socket %d\n,msg:%s\n", sockfd, buf);
        write(sockfd, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(0 == recvSize) {
        printf("socket %d closed\n", sockfd);
    } else if(0 > recvSize) {
        perror("recv error\n");
    }
}

int main(int argc, char **argv) {
    int listenfd = socket_bind("127.0.0.1", 8787);
    listen(listenfd, 5);
    struct sockaddr_in cliaddr;
    socklen_t cliaddlen;
    while (1) {
        int clifd = accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddlen);
        if(0 > clifd) {
            perror("accept error");
            exit(1);
        }
        printf("accept a new socket %d\n", clifd);
        pthread_t thread;
        if(0 > pthread_create(&thread, NULL, &sock_thread, (void *)&clifd)) {
            perror("could not create thread");
            exit(1);
        }
    }
    return 0;
}
