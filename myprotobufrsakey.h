
#ifndef MYPROTOBUFRSAKEY_H
#define MYPROTOBUFRSAKEY_H

#include "myprorobuf.h"
#include"dafuwen.pb.h"

using namespace dafuwenprotobuf;

struct MyprotobufRsakeyStruct
{
    int flag;
    int size;
    std::string RsaKey;
    std::string encontent;
    std::string Hashcontent;
};
class MyprotobufRsakey : public MyProrobuf
{
public:
    MyprotobufRsakey();
    //MyprotobufRsakeyStruct *RsakeyStruct
    virtual void initMessage(void * ptr);
    virtual std::string encodeMsg();
    virtual void* decodeMsg(std::string EnproStr) ;

private:
    std::string Pub_EnproStr;
    Protobuf_RsaPubKey Pro_Rsa_pub;
};

#endif // MYPROTOBUFRSAKEY_H
