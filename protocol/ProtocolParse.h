//
// Created by zhenbiao.cai on 2016/11/29.
//

#ifndef PROTOBUF_MASTER_PROTOCOLPARSE_H
#define PROTOBUF_MASTER_PROTOCOLPARSE_H

#include "ProtocolMsg.h"

static bool parseBuffer(char **buffer, int bufferLen) {
    //长度不够，下次再解析
    if(NULL == buffer || NULL == (*buffer) || ProtocolMsg::HEADER_SIZE > bufferLen) return false;
    //这里不要 ‘&0xff’也应该可以
    short header = (((*buffer)[0] & 0xff) << 8) + (*buffer)[1] & 0xff;
    short len = (((*buffer)[2] << 8)) + (*buffer)[3];
    //非数据包头部开始标示，跳过，继续解密
    if(ProtocolMsg::HEADER != header) {
        (*buffer) += 1;
        return true;
    }
    //非我们约好的规则，解析错误
    if(len < ProtocolMsg::HEADER_SIZE) {
        return false;
    }
    //数据长度不够，等待下次接收
    if(len > bufferLen - ProtocolMsg::HEADER_SIZE) {
        return false;
    }
    ProtocolMsg protocolMsg;
    protocolMsg.readHeader((*buffer));
    (*buffer) += protocolMsg.getLen();
}

#endif //PROTOBUF_MASTER_PROTOCOLPARSE_H
