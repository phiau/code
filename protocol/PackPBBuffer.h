//
// Created by zhenbiao.cai on 2016/11/30.
//

#ifndef PROTOBUF_MASTER_PACKPBBUFFER_H
#define PROTOBUF_MASTER_PACKPBBUFFER_H

#include "pstddef.h"
#include "PackBuffer.h"
#include "PBMessageManager.h"
#include <string>
#include <assert.h>
#include <google/protobuf/message.h>
using namespace std;
using namespace google::protobuf;

//功能：打包 Protocol Buffer 消息
char* packPBBuffer(int playerId, short code, Message *message, short *packLen) {
    if(NULL == message) return NULL;
    string stdMsg;
    message->SerializeToString(&stdMsg);
    return packBuffer(playerId, code, stdMsg.c_str(), stdMsg.length(), packLen);
}

//功能：解包，得到 Protocol Buffer 消息
//返回：返回已解析的长度，返回 0 说明长度不够，返回负数，说明错误异常
int unpackPBBuffer(char *in, int inLen, int *playerId, short *code, Message **pmessage) {
    if(NULL == in || NULL == pmessage) return 0;
    char *buffer = NULL;
    int bufferLen;
    int offset = unpackBuffer(in, inLen, playerId, code, &buffer, &bufferLen);
    if(HEADER_SIZE > offset) return offset;
    assert(NULL != buffer);

    string stdMsg(buffer);
    Message *message = generateMessage((*code));
    message->ParseFromString(stdMsg);
    (*pmessage) = message;
    return offset;
}

#endif //PROTOBUF_MASTER_PACKPBBUFFER_H
