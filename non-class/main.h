#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <cstring>
#include <sys/time.h>

#include "bytes_array.h"

int huffman_decode(const char *s, int len, std::string& out);
int huffman_encode(const char *in, ByteArray& out);

#endif
