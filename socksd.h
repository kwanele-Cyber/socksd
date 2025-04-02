/* socksd.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

/*internet specific*/
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $6 (int64)
#define $c (char *)
#define $i (int)

#define PORT 1080

int main(int,char**);
