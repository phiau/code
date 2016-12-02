//
// Created by zhenbiao.cai on 2016/12/2.
// g++ -I /usr/local/include/ -L /usr/local/lib TestPreParsePBPkg.cpp lm.helloworld.pb.cc -lprotoc -levent

#include <event2/buffer.h>
#include <google/protobuf/message.h>
#include "phiauProto/lm.helloworld.pb.h"
#include "phiauEvent/PBEventBuffer.h"
#include "phiauPkg/PackPBBuffer.h"
#include "phiauEvent/PBMessageManager.h"

using namespace std;
using namespace google::protobuf;

int main(int argc, char **argv)
{
    addMessageMap(1, lm::helloworld::descriptor()->full_name());
    struct evbuffer *buf = evbuffer_new();

    lm::helloworld helloworld;
    helloworld.set_id(201);
    helloworld.set_str("hello world");

    int playerId = 101;
    short code = 1;

    short packLen;
    char *byte = packPBBuffer(playerId, code, (Message*)(&helloworld), &packLen);

    evbuffer_add(buf, byte, packLen);
    preParsePBPkg(buf);

    evbuffer_free(buf);
}
