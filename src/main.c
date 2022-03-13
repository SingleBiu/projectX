/*
 * @Author: SingleBiu
 * @Date: 2021-09-12 22:16:08
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-13 21:35:25
 * @Description: file content
 */
#include"lcd.h"
#include"bmp.h"
#include"ts.h"
#include"sensor.h"

#include"tcp.h"

#include<pthread.h>
#include<semaphore.h>



int main(int argc, char const *argv[])
{
    //LCD初始化
    lcd_init();
    //清屏
    lcd_draw_rect(0,0,800,480,WHITE);

    //信号量初始化
    sem_init(&semDHT,0,1);
    // sem_init(&semFire,0,1);

    pthread_t p1,p2;
    pthread_create(&p1,NULL,handle_dht22,NULL);
    pthread_create(&p2,NULL,handle_fire_detect,NULL);

    //TODO: 将ip和端口写入配置文件自动读取
    // int sock = create_tcp_socket(argv[1],atoi(argv[2]));

    while (1)
    {
        // printf("Hum= %d Temprature= %d.%d\n",data[0],data[1],data[2]);

        // 0 正常 | 非 0失败
        // if(tcp_send(sock))
        // {
        //     printf("tcp send error\n");
        //     break;
        // }

        if (tcp_send(argv[1],atoi(argv[2])))
        {
            /* code */
        }
        
    }

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    sem_destroy(&semDHT);
    sem_destroy(&semFire);

    printf("system exit\n");

    return 0;
}
