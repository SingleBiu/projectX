/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 10:53:50
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-09-13 11:20:47
 * @Description: file content
 */
#include"tcp.h"


extern int value;
extern int Hum;
extern int T;

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
    // int sock = create_tcp_socket(serv_ip,serv_port);
    // if (sock == -1)
    // {
    //     printf("failed to create tcp socket\n");
    //     return -1;
    // }

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
        recv(sock,recvbuf,sizeof(recvbuf),0);
        printf("received: %s\n",recvbuf);
        sleep(3);

    }
    return 0;
}