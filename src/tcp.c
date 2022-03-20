/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 10:53:50
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-20 16:51:36
 * @Description: file content
 */
#include"tcp.h"
#include"sensor.h"

// extern int value;
// extern int Hum;
// extern int T;

#if 0
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
#endif

int tcp_send(const char *serv_ip,short serv_port)
{
    int n = 0;

    char sendbuf[128];
    char recvbuf[128];


    int sock;
    int ret;
retry:
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
        //每隔X秒尝试重连
        sleep(3);
        goto retry;
        return -1;
    }

    while (1)
    {
        // 清空
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));

        sprintf(sendbuf,"##Hum:%d:Temprature:%d.%d:Fire_state:%d:##",data[0],data[1],data[2],fire_state);
        // printf("Hum= %d Temprature= %d.%d\n",data[0],data[1],data[2]);
        // sprintf(sendbuf,"##smoke:%d,temprature:%d,hum:%d##",value,T,Hum);

        // 发送
        send(sock,sendbuf,sizeof(sendbuf),0);
        // printf("send: %s\n",sendbuf);

        // 重置信号量
        sem_post(&semDHT);
        sem_post(&semFire);
        //确保火焰信息发出再重置状态
        fire_state = 0;

        // 接收
        n = recv(sock,recvbuf,sizeof(recvbuf),0);
        if (n == 0)
        {
            printf("Server terminated prematually\n");
            break;
        }
        else if (n < -1)
        {
            
        }
        
        printf("received: %s\n",recvbuf);
        
        sleep(2);

    }

    return -1;
}