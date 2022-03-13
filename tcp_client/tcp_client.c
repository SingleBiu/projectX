/*
 * @Author: SingleBiu
 * @Date: 2022-03-13 16:59:46
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-13 19:35:15
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

int value=0;
int Hum=0;
int T=0;


int create_tcp_socket(const char *serv_ip,short serv_port)
{
    int sock;
    int ret;

    sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        perror("socket errno");
        return -1;
    }

    struct sockaddr_in sa;
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(serv_port);
    sa.sin_addr.s_addr = inet_addr(serv_ip);

    ret = connect(sock,(struct sockaddr*) &sa,sizeof(sa));
    if (ret == -1)
    {
        perror("connect error");
        close(sock);
        return -1;
    }
    
    return sock;
}

int tcp_send(int sock)
{
    int n;
    char sendbuf[128];
    char recvbuf[128];

    while (1)
    {
        // 清空
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));

        sprintf(sendbuf,"##smoke:%d,temprature:%d,hum:%d##",value,T,Hum);
        // 发送
        send(sock,sendbuf,sizeof(sendbuf),0);
        printf("send: %s\n",sendbuf);

        // 接收
        n = recv(sock,recvbuf,sizeof(recvbuf),0);
        if (n == 0)
        {
            printf("Server terminated prematually\n");
        }
        
        printf("received: %s\n",recvbuf);
        sleep(3);

    }
    return 0;
}


int main(int argc, char const *argv[])
{
    int sock = create_tcp_socket(argv[1],atoi(argv[2]));
    while (1)
    {
        printf("smoke:%d\thum:%d\tT:%d\n",value,Hum,T);
        tcp_send(sock);
    }


    return 0;
}
