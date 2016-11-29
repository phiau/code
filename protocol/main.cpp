//
// Created by zhenbiao.cai on 2016/11/29.
//
//export LD_LIBRARY_PATH=/usr/local/lib
//g++ main.cpp lm.helloworld.pb.cc ProtocolMsg.cpp -I /usr/local/include/ -L /usr/local/lib -lprotoc
#include <string>
#include "MessageMap.h"
#include "lm.helloworld.pb.h"
#include "ProtocolMsg.h"
using namespace std;

int main(int argc, char **argv)
{
    MessageMap::initMessageMap();
    lm::helloworld msg;
    msg.set_id(101);
    msg.set_str("hello");

    ProtocolMsg protocolMsg;
    protocolMsg.setCode(234);
    protocolMsg.setChecksum(321);
    protocolMsg.setMessage(&msg);

    protocolMsg.writeBody();

    char *bytes = protocolMsg.getBytes();
    ProtocolMsg protocolMsg1;
    protocolMsg1.readHeader(bytes);

}


