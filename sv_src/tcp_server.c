/*
 * @Author: SingleBiu
 * @Date: 2021-08-31 20:26:58
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-09-13 11:20:22
 * @Description: file content
 */
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int creat_tcp_socket(char *ip,short port)
{
    int sock;
    int ret;

    sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        perror("create tcp socket errno");
        return -1;
    }

    struct sockaddr_in sa;
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = inet_addr(ip);

    ret = bind(sock,(struct sockaddr*) &sa,sizeof(sa));
    if (ret == -1)
    {
        perror("bind error");
        close(sock);
        return -1;
    }
    
    ret = listen(sock,10);
    if (ret == -1)
    {
        perror("listen error");
        close(sock);
        return -1;
    }

    return sock;
}

void handle_connection(int conn_fd)
{
    char sendbuf[128];
    char recvbuf[128];
    memset(sendbuf,0,sizeof(sendbuf));
    memset(recvbuf,0,sizeof(recvbuf));
    
    while (1)
    {
        recv(conn_fd,recvbuf,sizeof(recvbuf),0);
        sprintf(sendbuf,"%s","TCP recv OK!");
        send(conn_fd,sendbuf,sizeof(sendbuf),0);
        printf("recv: %s\n",recvbuf);
        printf("send: %s\n",sendbuf);
        
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
    }
}

int main(int argc, char *argv[])
{
    int sock = creat_tcp_socket(argv[1],atoi(argv[2]));
    if (sock == -1)
    {
        printf("failed to create tcp socket\n");
        return -1;
    }

    while (1)
    {
        struct sockaddr_in client;
        socklen_t addrlen = sizeof(client);
        int conn_fd = accept(sock,(struct sockaddr*) &client,&addrlen);
        if (conn_fd > 0)
        {
            // 成功建立连接
            printf("client ip:%s\tport:%u\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        
            // 并发服务器
            pid_t pid = fork();
            if (pid > 0)
            {
                // 父进程
                close(conn_fd);
            }
            else if (pid == 0)
            {
                // 子进程
                handle_connection(conn_fd);
                exit(0);
            }
        }
    }
    return 0;
}
