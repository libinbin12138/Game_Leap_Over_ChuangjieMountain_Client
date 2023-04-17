
#include "myprotobufrsakey.h"

MyprotobufRsakey::MyprotobufRsakey()
{

}

void MyprotobufRsakey::initMessage(void * ptr)
{
    MyprotobufRsakeyStruct *RsakeyStruct=(MyprotobufRsakeyStruct *)ptr;
    Pro_Rsa_pub.set_flag(RsakeyStruct->flag);
    Pro_Rsa_pub.set_encontentsize(RsakeyStruct->size);
    Pro_Rsa_pub.set_pubkey(RsakeyStruct->RsaKey);
    Pro_Rsa_pub.set_encontent(RsakeyStruct->encontent);
    Pro_Rsa_pub.set_hashcontent(RsakeyStruct->Hashcontent);
}
std::string MyprotobufRsakey::encodeMsg()
{
    Pro_Rsa_pub.SerializeToString(&Pub_EnproStr);
    return Pub_EnproStr;
}
void* MyprotobufRsakey::decodeMsg(std::string EnproStr)
{
    Pro_Rsa_pub.ParseFromString(EnproStr);
    return &Pro_Rsa_pub;
}
