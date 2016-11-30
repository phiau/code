//
// Created by zhenbiao.cai on 2016/11/30.
//

#ifndef PROTOBUF_MASTER_PBMESSAGEMANAGER_H
#define PROTOBUF_MASTER_PBMESSAGEMANAGER_H

#include <map>
#include <string>
#include <stdio.h>
#include <google/protobuf/message.h>
#include "pstddef.h"
using namespace std;
using namespace google::protobuf;

typedef void (*messageFun)(Message *);

static map<short, string> messageMap;
static map<short, messageFun> funMap;

//这里对初始化，Protocol Buffer Message 和 code 的映射，code 会在解析协议的时候得到
static void initMessageMap(short code, string name) {
    messageMap.insert(make_pair(code, name));
}

void addMessageMap(short code, string name) {
    initMessageMap(code, name);
}

//这里根据 code，生成相应的 Protocol Buffer Message
Message* generateMessage(short code) {
    map<short, string>::iterator it = messageMap.find(code);
    if(messageMap.end() == it) {
        return NULL;
    }
    const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(it->second);
    if(NULL == descriptor) return NULL;
    const Message* protoType = MessageFactory::generated_factory()->GetPrototype(descriptor);
    if(NULL == protoType) return NULL;
    Message* message = protoType->New();
    return message;
}

//这里初始化，code 对应的处理函数
static void initMessageFunMap(short code, messageFun fun) {
    funMap.insert(make_pair(code, fun));
}

void addMessageFunMap(short code, messageFun fun) {
    initMessageFunMap(code, fun);
}

//这里根据 code，调用相应的处理函数
void dispatch(short code, Message* msg) {
    map<short, messageFun>::iterator it = funMap.find(code);
    if(funMap.end() != it) {
        (it->second)(msg);
    }
}

#endif
