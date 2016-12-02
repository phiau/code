//
// Created by zhenbiao.cai on 2016/11/30.
//

#ifndef PROTOBUF_MASTER_PACKBUFFER_H
#define PROTOBUF_MASTER_PACKBUFFER_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "phiauComm/pstddef.h"

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

//功能：构造包头部，然后发送消息的时候，把这个头部的内容复制到要发送的内容的前面，就可以了，其中 bufferLen 是要发送内容的长度
//注意：在拷贝完 pHead 的内容后，要 free pHead
short genPkgHead(int connMappingId, short code, int bufferLen, char **pHead) {
    assert(sizeof(struct PackageHead) == HEADER_SIZE);
    struct PackageHead * head = (struct PackageHead *) malloc(HEADER_SIZE);
    head->header = HEADER;
    head->len = bufferLen;
    head->checksum = 0;
    head->code = code;
    head->connMappingId = connMappingId;
    (*pHead) = (char *)(head);
    return HEADER_SIZE;
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

#endif //PROTOBUF_MASTER_PACKBUFFER_H
