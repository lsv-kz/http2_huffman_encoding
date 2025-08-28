#include <iostream>
#include <cstring>
#include <sys/time.h>

#include "../../bytes_array.h"

using namespace std;
//======================================================================
void huffman_decode(const char *s, int len, std::string& out);
int huffman_encode(const char *in, ByteArray& out);
//======================================================================
void std_in(char *s, int len)
{
    char ch;
    
    while ((ch = getchar()) != '\n' && (len - 1))
    {
        *s++ = ch;
        len--;
    }
    *s = '\0';
    if (ch != '\n')
        while ((ch = getchar()) != '\n');
}
//======================================================================
void get_time(struct timeval *time1, char *s, int size)
{
    unsigned long ts12, tu12;
    struct timeval time2;

    gettimeofday(&time2, NULL);

    if ((time2.tv_usec-time1->tv_usec) < 0)
    {
        tu12 = (1000000 + time2.tv_usec) - time1->tv_usec;
        ts12 = (time2.tv_sec - time1->tv_sec) - 1;
    }
    else
    {
        tu12 = time2.tv_usec - time1->tv_usec;
        ts12 = time2.tv_sec - time1->tv_sec;
    }

    snprintf(s, size, "%lu.%06lu sec", ts12, tu12);
}
//======================================================================
void hex_print_stderr(const char *s, const void *p, int n)
{
    int count, addr = 0, col;
    unsigned char *buf = (unsigned char*)p;
    char str[18];
    fprintf(stderr, "---------------- %s ----------------\n", s);
    for(count = 0; count < n;)
    {
        fprintf(stderr, "%08X  ", addr);
        for(col = 0, addr = addr + 0x10; (count < n) && (col < 16); count++, col++)
        {
            if (col == 8) fprintf(stderr, " ");
            fprintf(stderr, "%02X ", *(buf+count));
            str[col] = (*(buf + count) >= 32 && *(buf + count) < 127) ? *(buf + count) : '.';
        }
        str[col] = 0;
        if (col <= 8) fprintf(stderr, " ");
        fprintf(stderr, "%*s  %s\n",(16 - (col)) * 3, "", str);
    }

    fprintf(stderr, "\n");
}
//======================================================================
int main(int count, char *strings[])
{
    ByteArray buf;
    struct timeval time1;
    char s[4096], s1[64], s2[64];
    string str;
    str.reserve(128);

    while (true)
    {
        printf("============================================\n"
               ">>> ");
        fflush(stdout);
        std_in(s, sizeof(s));
        //--------------------------------------------------------------
        fprintf(stdout, "input string size %d bytes\n", (int)strlen(s));
    gettimeofday(&time1, NULL);
        huffman_encode(s, buf);
    get_time(&time1, s1, sizeof(s1));
        fprintf(stdout, "output size=%d\n", buf.size());
        hex_print_stderr("encode", buf.ptr(), buf.size());

    gettimeofday(&time1, NULL);
        huffman_decode(buf.ptr(), buf.size(), str);
    get_time(&time1, s2, sizeof(s2));

        fprintf(stdout, "decode:\n [%s]\n", s);
        fprintf(stdout, " [%s]\n", str.c_str());
        hex_print_stderr("decode hex", str.c_str(), str.size());
        
        fprintf(stdout, "encose time: %s\n", s1);
        fprintf(stdout, "decode time: %s\n", s2);
    }

    return 0;
}

//  Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0
//  現代標準漢語   (Chinese)
//  У Вас продается славянский шкаф?   (Russian)
