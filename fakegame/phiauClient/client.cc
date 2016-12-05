#include "phiauEvent/MessageFuns.h"
#include "phiauProto/zone.test.pb.h"
#include "phiauCommTest/SocketBufferEvent.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9876);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    initAllMessageMap();
    initAllMessageCallBack();

    struct event_base *base = event_base_new();
    if (!base) {
        return -1;
    }

    struct bufferevent *bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, echo_read_cb, echo_write_cb, NULL, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    event_base_dispatch(base);

    free(ev);
    free(bev);
    free(base);
    close(sockfd);
    return 0;
}
