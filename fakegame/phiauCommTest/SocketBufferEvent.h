//
// Created by zhenbiao.cai on 2016/12/5.
//

#ifndef LIBEVENT_SOCKETBUFFEREVENT_H
#define LIBEVENT_SOCKETBUFFEREVENT_H

#include "phiauProto/zone.test.pb.h"
#include "phiauEvent/PBEventBuffer.h"
#include "phiauEvent/PBMessageManager.h"
#include "phiauComm/PTimeUtils.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <google/protobuf/message.h>
using namespace google::protobuf;

void echo_read_cb(struct bufferevent *bev, void *ctx) {
    struct evbuffer *input = bufferevent_get_input(bev);
    struct evbuffer *output = bufferevent_get_output(bev);

    Message *message = NULL;
    int code = preParsePBPkg(input, &message);
    if(0 > code) {
        evbuffer_add_printf(output, "-----------no pkg\n");
    } else {
        dispatch(code, message, output);
    }
}

void echo_write_cb(struct bufferevent *bev, void *ctx) {
#ifdef IS_CLIENT
    struct evbuffer *input = bufferevent_get_input(bev);
    struct evbuffer *output = bufferevent_get_output(bev);

    static char isFirstWrite = 1;
    if(isFirstWrite) {
        isFirstWrite = 0;
        zone::test::Request request;
        request.set_code(1);
        request.set_count(1);
        request.set_time(p_now());
        prePackPBPkg(output, 101, 1, (Message*)(&request));
    }
#endif
}

#endif //LIBEVENT_SOCKETBUFFEREVENT_H
