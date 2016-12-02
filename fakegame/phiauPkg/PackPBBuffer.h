//
// Created by zhenbiao.cai on 2016/11/30.
//

#ifndef PROTOBUF_MASTER_PACKPBBUFFER_H
#define PROTOBUF_MASTER_PACKPBBUFFER_H

#include "phiauComm/pstddef.h"
#include "PackBuffer.h"
#include "phiauEvent/PBMessageManager.h"
#include <string>
#include <assert.h>
#include <google/protobuf/message.h>
using namespace std;
using namespace google::protobuf;

//功能：打包 Protocol Buffer 消息
//注意：记得 free pkg
char* packPBBuffer(int playerId, short code, Message *message, short *packLen) {
    if(NULL == message) return NULL;
    string stdMsg;
    message->SerializeToString(&stdMsg);
    //构造一个头部
    char *head = NULL;
    int headLen = genPkgHead(playerId, code, stdMsg.length(), &head);
    //构造整个协议，复制头部和body，然后释放头部
    char *pkg = (char *)malloc(headLen + stdMsg.length());
    memcpy(pkg, head, headLen);
    memcpy(pkg + headLen, stdMsg.c_str(), stdMsg.length());
    free(head);
    (*packLen) = headLen + stdMsg.length();
    return pkg;
}

//功能：对某段内存进行解析，得到 Protocol Buffer Message，适用已经解析完头部
//风险：可能存在解析的时候，宕掉的危险
static Message *parsePBBuffer(char *in, short code) {
    if(NULL == in) return NULL;
    string stdMsg(in);
    Message *message = generateMessage(code);
    if(message) {
        message->ParseFromString(stdMsg);
    }
    return message;
}

//功能：解包，得到 Protocol Buffer 消息
//返回：返回已解析的长度，返回 0 说明长度不够，返回负数，说明错误异常
int unpackPBBuffer(char *in, int inLen, int *playerId, short *code, Message **pmessage) {
    if(NULL == in || NULL == pmessage) return 0;
    int offset = checkPkgHead(in, inLen, playerId, code);
    //不是头部
    if(0 > offset) return 0;
    //是头部，尝试解析 body
    //长度不够，不足以解析 body
    if(offset + HEADER_SIZE > inLen) return 0;
    string stdMsg(in + HEADER_SIZE);
    Message *message = parsePBBuffer(in + HEADER_SIZE, *code);
    (*pmessage) = message;
    return offset + HEADER_SIZE;
}

#endif //PROTOBUF_MASTER_PACKPBBUFFER_H
