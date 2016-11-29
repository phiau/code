//
// Created by zhenbiao.cai on 2016/11/29.
//
#ifndef PROTOBUF_MASTER_PROTOCOLMSG_H
#define PROTOBUF_MASTER_PROTOCOLMSG_H
#include <google/protobuf/message.h>

class ProtocolMsg {

public:
    const static short HEADER_SIZE = 20;  //sizeof(header, len, checksum, code) + sizeof(playerId, empty1, empty2)
    const static short HEADER = 0x71ab;

    ProtocolMsg();

    //把数据写入缓存, 结构体本身有一个头部长度，消息体也有一个长度，下面就是消息体的长度
    void writeHeader(char *out);
    void writeBody();
    //从缓存读入数据
    void readHeader(char *in);

    //getter setter
    short getLen();
    void setLen(short len);
    short getChecksum();
    void setChecksum(short checksum);
    short getCode();
    void setCode(short code);
    google::protobuf::Message* getMessage();
    void setMessage(google::protobuf::Message* message);

    char *getBytes();

private:
    //头部
    short header;
    short len;
    short checksum;
    short code;
    int playerId;
    int empty1;
    int empty2;

    //消息体，这个是网络传输的内容(包括了头部，和实体逻辑数据)，只是放在这个类里面而已，也可以放在其他地方
    char *bytes;
    //解包后，得到实体逻辑数据，然后传给下面的 message 进行序列化，就可以进行相应的逻辑
    google::protobuf::Message *message;
};
#endif //PROTOBUF_MASTER_PROTOCOLMSG_H
