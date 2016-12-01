//
// Created by zhenbiao.cai on 2016/11/30.
//

#ifndef PROTOBUF_MASTER_PACKBUFFER_H
#define PROTOBUF_MASTER_PACKBUFFER_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pstddef.h"

struct PackageHead {
    short header;         //协议头部开始标示
    short len;            //body 的长度
    short checksum;       //校验码
    short code;           //协议号，可以辅助反序列化
    int connMappingId;   //链接对应的逻辑 id 映射，如果是游戏，可以用玩家的标示 playerId
    int empty1;
    int empty2;
};

const static short HEADER_SIZE = 20;   //sizeof(header, len, checksum, code) + sizeof(connMappingId, empty1, empty2)
const static short HEADER = 0x71ab;

struct PackageProtocol {
    PackageHead head;
    char *body;
};

//功能：打包消息
char * packBuffer(int connMappingId, short code, const char *buffer, int bufferLen, short *packLen) {
    assert(sizeof(PackageHead) == HEADER_SIZE);
    char *pack = (char *)malloc(HEADER_SIZE + bufferLen);
    PackageProtocol *packageProtocol = (PackageProtocol *) pack;
    //完成头部填充
    packageProtocol->head.header = HEADER;
    packageProtocol->head.len = bufferLen;
    packageProtocol->head.checksum = 0;
    packageProtocol->head.code = code;
    packageProtocol->head.connMappingId = connMappingId;
    //完成消息体填充
    memcpy(pack + HEADER_SIZE, buffer, bufferLen);
    (*packLen) = HEADER_SIZE + bufferLen;
    return pack;
}

//功能：检查是不是头部，如果是头部，返回消息体长度，否则返回 -1
int checkPkgHead(char *in, int inLen, int *connMappingId, short *code) {
    if(NULL == in || HEADER_SIZE > inLen) return -1;
    struct PackageHead *packageHead = (struct PackageHead *)in;
    if(HEADER != packageHead->header) return -1;
    if(connMappingId) {
        (*connMappingId) = packageHead->connMappingId;
    }
    if(code) {
        (*code) = packageHead->code;
    }
    return packageHead->len;
}

//功能：解包消息，对 in 按照规则进行解包
//返回：返回已解析的长度，返回 0 说明长度不够，返回负数，说明错误异常
int unpackBuffer(char *in, int inLen, int *connMappingId, short *code, char **buffer, int *bufferLen) {
    if(NULL == in || HEADER_SIZE > inLen) return 0;
    PackageHead *packageHead = (PackageHead *)in;
    //不是数据包的头部标示，跳过
    if(HEADER != packageHead->header) return 1;
    //非我们约好的规则，解析错误
    if(0 > packageHead->len) return -1;
    //数据长度不够，等待继续接收
    if(inLen - HEADER_SIZE < packageHead->len) return 0;
    //todo 校验checksum

    short len = packageHead->len;
    //这里在重新申请空间的时候，要多申请一个自己，存放结束符，这样 Protocol Buffer 在序列化的时候，才正常
    char *pack = (char *)malloc(HEADER_SIZE + len + 1);
    memset(pack, 0, HEADER_SIZE + len + 1);
    memcpy(pack, in, HEADER_SIZE + len);
    PackageProtocol *packageProtocol = (PackageProtocol *)pack;
    assert(len == packageProtocol->head.len);
    (*connMappingId) = packageProtocol->head.connMappingId;
    (*code) = packageProtocol->head.code;
    (*bufferLen) = packageProtocol->head.len;
    (*buffer) = pack + HEADER_SIZE;

    return (HEADER_SIZE + len);
}

#endif //PROTOBUF_MASTER_PACKBUFFER_H
