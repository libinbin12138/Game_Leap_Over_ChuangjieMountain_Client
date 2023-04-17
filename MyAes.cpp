#define _CRT_SECURE_NO_WARNINGS
#include "MyAes.h"
#include<iostream>

MyAes::MyAes()
{
	this->userkey = NULL;
}
MyAes::MyAes(const char* userkey)
{
	bits = strlen(userkey) * 8;
	this->userkey = new char[bits + 1];
	memset(this->userkey, 0, bits);
	strcpy(this->userkey, userkey);
	std::cout << "userkey===" << userkey << std::endl;
}
MyAes::~MyAes()
{


}
std::string MyAes::Aes_Encode(std::string p)
{
	AES_set_encrypt_key((const unsigned char*)userkey, 128, &Enkey);

	int length = 0;
	int len =p.size() + 1;

	if (len % 16 != 0)
	{
		length = ((len / 16) + 1) * 16;
	}
	else
	{
		length = len;
	}

	char* out = new char[length];

	unsigned char ivec[AES_BLOCK_SIZE];
	memset(ivec, 9, sizeof(ivec));
	// 密文存储在out中
	AES_cbc_encrypt((const unsigned char*)p.c_str(), (unsigned char*)out, length, &Enkey, ivec, AES_ENCRYPT);

	std::string retStr = std::string(out,length);
	delete[]out;
	return std::string(retStr);

}

std::string MyAes::Aes_Decode(std::string in)
{

	AES_set_decrypt_key((const unsigned char*)userkey, 128, &Dekey);
	int length = 0,len= in.size();


	if (len % 16 != 0)
	{
		length = ((len / 16) + 1) * 16;
	}
	else
	{
		length = len;
	}

	char* data = new  char[length];
	//memset(data, 0, sizeof(data));
	unsigned char ivec[AES_BLOCK_SIZE];
	memset(ivec, 9, sizeof(ivec));

	AES_cbc_encrypt((const unsigned char*)in.c_str(), (unsigned char*)data, length, &Dekey, ivec, AES_DECRYPT);

	std::string retStr = std::string(data, strlen(data));
	delete[]data;

	// 6. 打印
	std::cout << "还原的数据: " << retStr << std::endl;

	return std::string(retStr);
}


std::string MyAes::Aes_Decode(std::string in, int len)
{
	AES_set_decrypt_key((const unsigned char*)userkey, 128, &Dekey);
	int length = 0;


	if (len % 16 != 0)
	{
		length = ((len / 16) + 1) * 16;
	}
	else
	{
		length = len;
	}

	 char* data = new  char[length];
	 //memset(data, 0, sizeof(data));
	unsigned char ivec[AES_BLOCK_SIZE];
	memset(ivec, 9, sizeof(ivec));

	AES_cbc_encrypt((const unsigned char*)in.c_str(), (unsigned char*)data, length, &Dekey, ivec, AES_DECRYPT);
	
	std::string retStr = std::string(data, strlen(data));
	delete[]data;
	
	// 6. 打印
	std::cout << "还原的数据: " << retStr << std::endl;

	return std::string(retStr);
}