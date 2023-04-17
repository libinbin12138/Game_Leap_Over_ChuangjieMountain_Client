#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<openssl/rsa.h>
#include<openssl/bio.h>
#include<iostream>
# include <stdio.h>
# include <string.h>
#include<string>
using namespace std;
class MyRsa
{
public:
    MyRsa();

    ~MyRsa();

    void Create();
    void Write_Pub();
    void Write_Pri();
    void Read_Pub();
    void Read_Pri();
    string Get_encrypt_Value_Pub(string from);
    string Get_decrypt_Value_Pri(string buf);
    //    string Get_encrypt_Value_Pri(string from);
    //    string Get_decrypt_Value_Pub(string buf);
    string Read_RPub_To_String();
    void Read_RPub_FromString(string pubstring);
    void Read_RPri_FromString(string pubstring);

    std::string My_RSA_sign(string text);
    int My_RSA_verify(string text, string sigbuf);

private:
    RSA* rsa;
    BIGNUM* e;
    RSA* rpub;
    RSA* rpri;
};

