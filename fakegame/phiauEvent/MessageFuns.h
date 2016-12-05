//
// Created by zhenbiao.cai on 2016/12/2.
//

#ifndef LIBEVENT_MESSAGEFUNS_H
#define LIBEVENT_MESSAGEFUNS_H

#include "PBMessageManager.h"

#include "phiauComm/PTimeUtils.h"
#include "phiauEvent/PBEventBuffer.h"
#include "phiauProto/zone.test.pb.h"
#include "phiauProto/lm.helloworld.pb.h"

#include <stdio.h>
#include <event2/buffer.h>
#include <google/protobuf/message.h>

using namespace std;
using namespace google::protobuf;

//测试函数
void testMessageFun(Message *psmsg, evbuffer* outBev) {
    zone::test::Request *pmsg = (zone::test::Request *) psmsg;
    if (NULL != pmsg) {
        int code = pmsg->code();
        int count = pmsg->count();
        long time = pmsg->time();
        printf("code = %d, count = %d, time = %ld\n", code, count, time);

        pmsg->set_count(count + 1);
        pmsg->set_time(p_now());
        prePackPBPkg(outBev, 101, 1, psmsg);
    } else {
        printf("--testMessageFun NULL\n");
    }
}

void testMessageFun2(Message *psmsg, evbuffer* outBev) {
    lm::helloworld *pmsg = (lm::helloworld *) psmsg;
    if (NULL != pmsg) {
        printf("======testMessageFun2\n");
    } else {
        printf("--testMessageFun2 NULL\n");
    }
}

void initAllMessageMap() {
    addMessageMap(1, zone::test::Request::descriptor()->full_name());
    addMessageMap(2, lm::helloworld::descriptor()->full_name());
}

void initAllMessageCallBack() {
    addMessageFunMap(1, testMessageFun);
    addMessageFunMap(2, testMessageFun2);
}

#endif //LIBEVENT_MESSAGEFUNS_H
