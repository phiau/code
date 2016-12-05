//
// Created by zhenbiao.cai on 2016/12/1.
//
//源码，大部分来自《libevent参考手册（中文版）》
//g++ -I /usr/local/include/ -I /usr/phiau/code/fakegame/ -L /usr/local/lib server_event.cpp ../phiauProto/zone.test.pb.cc -lprotoc -levent 

#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <google/protobuf/message.h>

#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "phiauEvent/PBEventBuffer.h"
#include "phiauEvent/PBMessageManager.h"
#include "phiauComm/PTimeUtils.h"
#include "phiauProto/zone.test.pb.h"
#include "phiauEvent/MessageFuns.h"

using namespace std;
using namespace google::protobuf;

void
echo_read_cb(struct bufferevent *bev, void *ctx)
{
    /* This callback is invoked when there is data to read on bev. */
    struct evbuffer *input = bufferevent_get_input(bev);
    struct evbuffer *output = bufferevent_get_output(bev);

    Message *message = NULL;
    int code = preParsePBPkg(input, &message);
    if(0 > code) {
        evbuffer_add_printf(output, "client send content no pkg\n");
    } else {
        dispatch(code, message, output);
    }
}

void
echo_event_cb(struct bufferevent *bev, short events, void *ctx)
{
    if(BEV_EVENT_ERROR & events)
        perror("Error from bufferevent");
    if((BEV_EVENT_EOF | BEV_EVENT_ERROR))
        bufferevent_free(bev);
}

void
accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd,
               struct sockaddr *address, int socklen, void *ctx)
{
    /* We got a new connection! Set up a bufferevent fot it. */
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);
    bufferevent_enable(bev, EV_READ|EV_WRITE);
}

void
accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. Shutting down.\n",
            err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

int main(int argc, char **argv) {

    initAllMessageMap();
    initAllMessageCallBack();

    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;

    int port = 9876;
    if(1 < argc) {
        port = atoi(argv[1]);
    }
    if(1 > port || 65535 < port) {
        puts("Invalid port");
        return 1;
    }
    base = event_base_new();
    if(!base) {
        puts("Couldn't open event base");
        return 1;
    }
    /* Clear the sockaddr before using it, in case there are extra
     * platform-specific fields that can mess us up. */
    memset(&sin, 0, sizeof(sin));
    /* This is an INET address */
    sin.sin_family = AF_INET;
    /* Listen on 0.0.0.0 */
    sin.sin_addr.s_addr = htonl(0);
    /* Listen on the given port. */
    sin.sin_port = htons(port);

    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr*)&sin, sizeof(sin));
    if(!listener) {
        perror("Couldn't create listener");
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_dispatch(base);
    return 0;
}

