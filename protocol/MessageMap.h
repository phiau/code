//
// Created by zhenbiao.cai on 2016/11/29.
//

#ifndef PROTOBUF_MASTER_MESSAGEMAP_H
#define PROTOBUF_MASTER_MESSAGEMAP_H

#include <map>
#include "pstddef.h"
#include "lm.helloworld.pb.h"
#include <google/protobuf/message.h>
using namespace std;
using namespace google::protobuf;

class MessageMap {
private:
    static map<short, string> messageMap;
public:
    static void initMessageMap() {
        MessageMap::messageMap.insert(make_pair(1, lm::helloworld::descriptor()->full_name()));
    }

    static Message* generateMessage(short code) {
        map<int, string>::iterator it = messageMap.find(code);
        if(messageMap.end() == it) {
            return NULL;
        }
        const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(it->second);
        if(NULL == descriptor) return NULL;
        const Message* protoType = MessageFactory::generated_factory()->GetPrototype(descriptor);
        if(NULL == protoType) return NULL;
        return protoType->New();
    }
};

#endif
