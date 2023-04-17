#pragma once
#include<openssl/aes.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
//# define AES_ENCRYPT 1    
//# define AES_DECRYPT 0

class MyAes
{
public:
	MyAes();
	MyAes(const char* userkey);
	~MyAes();
	std::string Aes_Encode(std::string p);
	std::string Aes_Decode(std::string in);
	std::string Aes_Decode(std::string in, int len);

private:
	char* userkey;

	AES_KEY Enkey;
	AES_KEY Dekey;

	int bits;
};

