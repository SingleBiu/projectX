/*
 * @Author: SingleBiu
 * @Date: 2021-08-31 20:26:58
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-20 20:25:33
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

#include"sql.h"

#define NET_CFG_FILE "net.conf"
char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; 


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
    int n = 0;
    char sendbuf[128];
    char recvbuf[128];
    memset(sendbuf,0,sizeof(sendbuf));
    memset(recvbuf,0,sizeof(recvbuf));
    
    while (1)
    {
        n = recv(conn_fd,recvbuf,sizeof(recvbuf),0);
        sprintf(sendbuf,"%s","Data recv OK!");
        send(conn_fd,sendbuf,sizeof(sendbuf),0);

        if (n == 0)
        {
            //conn_fd closed by the client
            close(conn_fd);
            printf("Client exit\n");
            break;
        }
        
        printf("recv: %s\n",recvbuf);
        // printf("send: %s\n",sendbuf);
        //解析信息并插入数据库
        handle_db(recvbuf);
        
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
    }
}

int main(int argc, char *argv[])
{
    //从配置文件中读取服务器ip和端口号
    char servIp[15];
    char servPort[5];
    FILE* cfgFp = fopen(NET_CFG_FILE,"r");
    fscanf(cfgFp,"%s",servIp);
    fscanf(cfgFp,"%s",servPort);

    int sock = creat_tcp_socket(servIp,atoi(servPort));
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
