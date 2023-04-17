#include "MyRsa.h"
#include "qdebug.h"
#include<openssl/pem.h>
#include<QString>
using namespace std;
MyRsa::MyRsa()
{
	rsa = RSA_new();
	rpub =  RSA_new();
	rpri = RSA_new();
}
MyRsa::~MyRsa()
{
	if (rsa != NULL)
	{
		RSA_free(rsa);
	}
	if (rpub != NULL)
	{
		RSA_free(rpub);
	}
	if (rpri != NULL)
	{
		RSA_free(rpri);
	}
	if (e != NULL)
	{
		BN_free(e);
	}
}

void MyRsa::Create()
{
	e = BN_new();
	BN_set_word(e, 12345);
	int ret = RSA_generate_key_ex(rsa, 1024, e, NULL);
	rpub = RSAPublicKey_dup(rsa);
    rpri = RSAPrivateKey_dup(rsa);
    qDebug()<<"RSA_Size(rpub)"<<RSA_size(rpub);
}
void MyRsa::Write_Pub()
{
	BIO* bio = BIO_new_file("public.pem", "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	BIO_free(bio);
}
void MyRsa::Write_Pri()
{
	BIO* bio = BIO_new_file("private.pem", "w");
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
	BIO_free(bio);

}
void MyRsa::Read_Pub()
{
	BIO* bio = BIO_new_file("public.pem", "r");
	PEM_read_bio_RSAPublicKey(bio, &rpub, NULL, NULL);
	BIO_free(bio);
}
void MyRsa::Read_Pri()
{
	BIO* bio = BIO_new_file("private.pem", "r");
    PEM_read_bio_RSAPrivateKey(bio, &rpri, NULL, NULL);
    BIO_free(bio);
}

string MyRsa::Get_encrypt_Value_Pub(string from)
{
    cout << "加密数据长度" << from.size() <<endl;
                                    int keyLen = RSA_size(rpub);
    char* encode = new char[keyLen + 1];
    cout << "开始加密" << endl;

        int len = RSA_public_encrypt(from.size(), (const unsigned char*)from.data(),
                             (unsigned char*)encode, rpub, RSA_PKCS1_PADDING);
    string to = string();
    if (len >=0)
    {
        to = string(encode, len);
    }
    // 释放资源
    delete[]encode;

    return to;
}

string MyRsa::Get_decrypt_Value_Pri(string buf)
{
	cout << "解密数据长度" << buf.size() << endl;
	int keyLen = RSA_size(rpri);
	char* decode = new char[keyLen + 1];
	cout << "开始解密" << endl;
	int len = RSA_private_decrypt(buf.size(), (const unsigned char*)buf.data(),
		(unsigned char*)decode, rpri, RSA_PKCS1_PADDING);
	string to = string();
	if (len >= 0)
	{
		to = string(decode, len);

	}// 释放资源
	delete[]decode;


    return to;
}

string MyRsa::Read_RPub_To_String()
{
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, rpub);

    // Get the PEM-encoded RSA key and its length
    char* rsa_key;
    long rsa_key_size = BIO_get_mem_data(bio, &rsa_key);
    string rpubkeyString(rsa_key,rsa_key_size);
    return rpubkeyString;
}

void MyRsa::Read_RPub_FromString(string pubstring)
{
    BIO* bio = BIO_new_file("public.pem", "w");
    BIO_write(bio,&pubstring,pubstring.size());
            BIO_free(bio);

    bio = BIO_new_file("public.pem", "r");
    PEM_read_bio_RSAPublicKey(bio, &rpub, NULL, NULL);
    BIO_free(bio);

}

void MyRsa::Read_RPri_FromString(string pubstring)
{
    BIO* bio = BIO_new_file("private.pem", "w");
    BIO_write(bio,&pubstring,pubstring.size());
    BIO_free(bio);

    bio = BIO_new_file("private.pem", "r");
    PEM_read_bio_RSAPrivateKey(bio, &rpri, NULL, NULL);
    BIO_free(bio);
}

std::string MyRsa::My_RSA_sign(string text)
{
    int len = RSA_size(rpri);
    unsigned int outLen = 0;
    unsigned char* out = new unsigned char[len];
    RSA_sign(NID_sha256, (const unsigned char*)text.data(), text.size(),
             out, &outLen, rpri);
    // 要给到用户的数据
    string sigbuf((char*)out, outLen);
    cout << "哈希数据" << sigbuf << endl;
        return sigbuf;
}

int MyRsa::My_RSA_verify(string text, string sigbuf)
{
    int ret = RSA_verify(NID_sha256, (const unsigned char*)text.data(), text.size(),
                         (const unsigned char*)sigbuf.data(), sigbuf.size(), rpub);
    cout << "ret : " << ret << endl;

    return ret;
}

