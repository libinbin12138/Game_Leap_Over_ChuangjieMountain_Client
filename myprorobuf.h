#ifndef MYPROROBUF_H
#define MYPROROBUF_H
#include<string>

class MyProrobuf
{
public:
    MyProrobuf();
    virtual void initMessage(void * ptr)=0;
    virtual std::string encodeMsg()=0;
    virtual void* decodeMsg(std::string EnproStr)=0;

    ~MyProrobuf();
};

#endif // MYPROROBUF_H
