//
//  main.cpp
//  crypto
//
//  Created by Laurent Zubiaur on 9/24/14.
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "AES.h"

const unsigned char key[] = {
    0xCB,0xEF,0x5C,0x34,0x71,0x43,0x5F,0xF9,0x81,0xEF,0xCC,0xCD,0x16,0x54,0xEC,0xA1,
    0x08,0x5E,0x7C,0x7B,0x28,0x03,0x98,0xF0,0x92,0x84,0xBE,0xA9,0xD7,0x77,0x6C,0x0B,
    0x6C,0x38,0x0F,0x6E,0xF5,0xB7,0xEE,0xD7,0x95,0x33,0x30,0xC1,0x66,0xD3,0x18,0x5E,
    0xF6,0x33,0x0B,0xD9,0x82,0x0A,0x36,0x94,0x32,0x38,0xFB,0x4D,0xE6,0x8F,0x63,0xFA,
    0x22,0xF5,0x78,0xB5,0x29,0x95,0xD4,0x04,0x50,0x43,0x36,0x0F,0x8E,0x86,0x6F,0xAC,
    0x12,0xDC,0xDD,0x1C,0xAD,0xD2,0x85,0xEC,0x0A,0x47,0x67,0xBB,0x08,0xB0,0x66,0xC2,
    0x21,0x2C,0x15,0x4D,0x6E,0x54,0xBD,0x67,0x4C,0x1A,0x8A,0xC4,0xE0,0xE7,0xE1,0xF9,
    0x4E,0xEC,0x56,0xA6,0x17,0xE5,0x94,0xFD,0x97,0x2F,0x3D,0x60,0x0E,0xD4,0x7C,0x7B
};

unsigned char* readFile(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    *pSize = 0;
    do
    {
        FILE *fp = fopen(pszFileName, pszMode);
        if(!fp) break;

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    if (! pBuffer)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        std::cerr << msg << std::endl;
    }
    return pBuffer;
}

bool writeFile(const char *filename, const char *data, unsigned long size)
{
    /// libstdc++ (Gnu) has different constructor than libc++ (llvm) and does not accept a std::string as parameter
    std::ofstream out(filename, std::ofstream::binary);
    out.write(data, size);
    out.flush();
    bool rc = true;
    if (out.bad())
        rc = false;
    out.close();
    return rc;
}

int unpadding(const unsigned char *in, unsigned char **out, size_t size)
{
    unsigned char mod = in[size - 1];
    size -= mod;
    *out = new unsigned char[size];
    memcpy(*out, in, size);
    return size;
}

int padding(const unsigned char *in, unsigned char **out, size_t size)
{
    unsigned char mod = 16 - (size % 16);
    *out = new unsigned char[size + mod];
    memcpy(*out, in, size);
    for (int i=0; i < mod - 2; ++i) {
        (*out)[size + i] = rand() % 255;
    }
    (*out)[size + mod - 1] = mod;
    return (size + mod) / 16;
}

void encrypt(const char *inf,const char *outf)
{
    unsigned long size;
    unsigned char *data = readFile(inf, "rb", &size);

    /// std::cerr.write((const char *)data,size);

    unsigned char *enc = new unsigned char[size + 16];
    unsigned char *pad = new unsigned char[size + 16];

    int block = padding((const unsigned char *)data, &pad, size);
    /*
    std::cerr << "padding block: " << block << std::endl;
    std::cerr.write((const char *)pad, block * 16);
    std::cerr << "---" << std::endl;
    */

    AES aes;
    aes.SetParameters(128,128);
    aes.StartEncryption(key);
    aes.Encrypt(pad, enc, block);

    // std::cerr.write((const char *)enc, block * 16);
    writeFile(outf, (const char *)enc, block * 16);

    // delete[] enc;
    delete[] data;
}

void decrypt(const char *inf,const char *outf)
{
    unsigned long size;
    unsigned char *data = readFile(inf, "rb", &size);
    unsigned char *dec = new unsigned char[size];

    if (size % 16 != 0) {
        std::cerr << "Abort. Input is not 16 blocks padded." << std::endl;
        exit(-1);
    }

    std::cerr << "read " << size << " bytes" << std::endl;

    AES aes;
    aes.SetParameters(128,128);
    aes.StartDecryption(key);
    aes.Decrypt(data, dec, size / 16);

    /// std::cout.write((const char *)dec, size);

    unsigned char *pad;
    int unpadSize = unpadding(dec, &pad, size);
    // std::cout.write((const char *)pad, unpadSize);

    writeFile(outf, (const char *)pad, unpadSize);

    delete[] pad;
    delete[] dec;
    delete[] data;
}

void usage()
{
    std::cerr << "Usage: crypto enc|dec input output" << std::endl;
}

int main(int argc, const char * argv[])
{
    if (argc < 4) {
        usage();
        return -1;
    }

    srand(time(NULL));

    if (strcmp(argv[1],"enc") == 0) {
        std::cerr << std::endl << "------------[[ Encrypt ]]------------" << std::endl;
        encrypt(argv[2],argv[3]);
    } else if (strcmp(argv[1],"dec") == 0) {
        std::cerr << std::endl << "------------[[ Decrypt ]]------------" << std::endl;
        decrypt(argv[2],argv[3]);
    } else {
        usage();
        return -1;
    }
    return 0;
}
