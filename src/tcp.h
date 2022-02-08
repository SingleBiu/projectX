/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 10:53:56
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-09-13 11:14:45
 * @Description: file content
 */
#ifndef __TCP_H__
#define __TCP_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int create_tcp_socket(const char *serv_ip,short serv_port);
int tcp_send(int sock);

#endif