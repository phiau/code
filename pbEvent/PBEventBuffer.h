//
// Created by zhenbiao.cai on 2016/12/1.
//

#ifndef LIBEVENT_PBEVENTBUFFER_H
#define LIBEVENT_PBEVENTBUFFER_H

#include <string>
#include <assert.h>
#include <event2/buffer.h>
#include <google/protobuf/message.h>
#include "pstddef.h"
#include "PackBuffer.h"
#include "PackPBBuffer.h"
#include "lm.helloworld.pb.h"

//检查 event 的 evbuffer 缓冲消息，看是不是头部标示
int preParsePBPkg(struct evbuffer *buf) {
    int playerId;
    short code;

    char pkgHeadFlag = -1;
    int offset = 0xffff;
    size_t size;
    struct evbuffer_iovec v[1];
    do {
        //确保缓冲前 HEADER_SIZE 字节在内存上是连续的
        if(!evbuffer_pullup(buf, HEADER_SIZE)) return -1;
        size = evbuffer_get_length(buf);
        if (HEADER_SIZE > size) break;
        //得到缓冲前 HEADER_SIZE 字节的指针
        int n = evbuffer_peek(buf, HEADER_SIZE, NULL, v, 1);
        if (0 >= n) return -1;
        assert(HEADER_SIZE <= v[0].iov_len);
        //检查是不是消息的头部
        offset = checkPkgHead((char*)v[0].iov_base, v[0].iov_len, &playerId, &code);
        if(0 > offset) {
            //不是头部，缓冲移除一个字节
            if(0 > evbuffer_drain(buf, 1)) break;
        } else {
            //解析到头部了
            pkgHeadFlag = 0;
            break;
        }
    } while (1);

    if(-1 == pkgHeadFlag) return -1;
    //消息偏移加上头部，是这次要获得的总的字节数
    offset += HEADER_SIZE;
    if(offset > evbuffer_get_length(buf)) return -1;

    char *pkg = (char *) malloc(offset + 1);
    memset(pkg, 0, offset + 1);
    if(0 > evbuffer_remove(buf, pkg, offset)) {
        printf("some error arisen preParsePBPkg\n");
        return -1;
    }
    std::string stdMsg(pkg + HEADER_SIZE);
    Message *message = generateMessage(code);
    if(message) {
        message->ParseFromString(stdMsg);
        lm::helloworld *pHelloworld = (lm::helloworld*)(message);
        printf("%d, %s\n", pHelloworld->id(), pHelloworld->str().c_str());
    } else {
        printf("the protocol code(%d) is incorrect\n", code);
    }
    printf("success preParsePBPkg\n");
    return 0;
}

#endif //LIBEVENT_PBEVENTBUFFER_H
