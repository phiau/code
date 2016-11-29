//
// Created by zhenbiao.cai on 2016/11/29.
//
#include <string>
#include <stdio.h>
#include "ProtocolMsg.h"
#include "pstddef.h"
#include "MessageMap.h"

ProtocolMsg::ProtocolMsg() {
    this->bytes = NULL;
    this->message = NULL;
}

void readHeaderIn(char **buffer, void *data, int len) {
    if(NULL == buffer || NULL == (*buffer) || NULL == data) return;
    memcpy(data, (*buffer), len);
    (*buffer) += len;
}

//从内存读取数据，直接操作指针复制
void ProtocolMsg::readHeader(char *in) {
    if(NULL == in) return;
    readHeaderIn(&in, &this->header, sizeof(this->header));
    readHeaderIn(&in, &this->len, sizeof(this->len));
    readHeaderIn(&in, &this->checksum, sizeof(this->checksum));
    readHeaderIn(&in, &this->code, sizeof(this->code));
    readHeaderIn(&in, &this->playerId, sizeof(this->playerId));
    readHeaderIn(&in, &this->empty1, sizeof(this->empty1));
    readHeaderIn(&in, &this->empty2, sizeof(this->empty2));

    if(NULL != this->bytes) free(this->bytes);
    this->bytes = (char *)malloc(this->len - HEADER_SIZE + 1);
    memset(this->bytes, 0, this->len - HEADER_SIZE + 1);
    memcpy(this->bytes, in, this->len - HEADER_SIZE);

    std::string msg(this->bytes);
    if(NULL != this->message) free(this->message);
    this->message = MessageMap::generateMessage(this->code);
    if(NULL != this->message) {
        printf("2 this len=%d, len1=%d,  %s\n", this->len, msg.length(), msg.c_str());
        this->message->ParseFromString(msg);
    }
}

void ProtocolMsg::writeBody() {
    if(NULL == this->message) return;
    std::string msg;
    const google::protobuf::Message *tmpMsg = this->message;
    tmpMsg->SerializeToString(&msg);
    if(NULL != this->bytes) free(this->bytes);
    this->len = msg.length() + HEADER_SIZE;
    printf("1 this len=%d, len1=%d,  %s\n", this->len, msg.length(), msg.c_str());
    this->bytes = (char *)malloc(this->len);
    this->header = HEADER;
    this->writeHeader(this->bytes);
    memcpy((this->bytes + HEADER_SIZE), msg.data(), msg.length());
}

void writeHeaderIn(char **buffer, void *data, int len) {
    if(NULL == buffer || NULL == (*buffer) || NULL == data) return;
    memcpy((*buffer), data, len);
    (*buffer) += len;
}

//把数据写进内存，直接操作指针复制
void ProtocolMsg::writeHeader(char *out) {
    if(NULL == out) return;
    writeHeaderIn(&out, &this->header, sizeof(this->header));
    writeHeaderIn(&out, &this->len, sizeof(this->len));
    writeHeaderIn(&out, &this->checksum, sizeof(this->checksum));
    writeHeaderIn(&out, &this->code, sizeof(this->code));
    writeHeaderIn(&out, &this->playerId, sizeof(this->playerId));
    writeHeaderIn(&out, &this->empty1, sizeof(this->empty1));
    writeHeaderIn(&out, &this->empty2, sizeof(this->empty2));
}

short ProtocolMsg::getLen() {
    return this->len;
}

void ProtocolMsg::setLen(short len) {
    this->len = len;
}

short ProtocolMsg::getCode() {
    return this->code;
}

void ProtocolMsg::setCode(short code) {
    this->code = code;
}

short ProtocolMsg::getChecksum() {
    return this->checksum;
}

void ProtocolMsg::setChecksum(short checksum) {
    this->checksum = checksum;
}

google::protobuf::Message* ProtocolMsg::getMessage() {
    return this->message;
}

void ProtocolMsg::setMessage(google::protobuf::Message *message) {
    this->message = message;
}

char * ProtocolMsg::getBytes() {
    return this->bytes;
}
