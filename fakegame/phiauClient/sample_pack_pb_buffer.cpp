//
// Created by zhenbiao.cai on 2016/11/29.
//
//export LD_LIBRARY_PATH=/usr/local/lib
//g++ sample_pack_pb_buffer.cpp lm.helloworld.pb.cc -I /usr/local/include/ -L /usr/local/lib -lprotoc -g
#include <string>
#include <google/protobuf/message.h>
#include "phiauProto/lm.helloworld.pb.h"
#include "phiauPkg/PackBuffer.h"
#include "phiauPkg/PackPBBuffer.h"
#include "phiauEvent/PBMessageManager.h"

using namespace std;
using namespace google::protobuf;

//测试函数
void loginMessageFun(Message *psmsg) {
    lm::helloworld *pmsg = (lm::helloworld*) psmsg;
    if(NULL!= pmsg) {
        printf("--%s\n", pmsg->str().c_str());
    } else {
        printf("--\n");
    }
}

int main(int argc, char **argv)
{
    addMessageMap(1, lm::helloworld::descriptor()->full_name());
    addMessageFunMap(1, loginMessageFun);

    int playerId = 101;kjkkk
    short code = 1;
    lm::helloworld helloworld;
    helloworld.set_id(201);
    helloworld.set_str("hello");

    short packLen;
    char *byte = packPBBuffer(playerId, code, (Message *)(&helloworld), &packLen);

    int cPlayerId;
    short cCode;
    lm::helloworld *pHelloworld = NULL;
    unpackPBBuffer(byte, packLen, &cPlayerId, &cCode, (Message **)&pHelloworld);

    printf("--playerId = %d, code = %d\n", cPlayerId, cCode);
    printf("--%s %d\n", pHelloworld->str().c_str(), pHelloworld->id());
}

