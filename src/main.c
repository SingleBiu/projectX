/*
 * @Author: SingleBiu
 * @Date: 2021-09-12 22:16:08
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-09-13 11:19:18
 * @Description: file content
 */
#include"lcd.h"
#include"bmp.h"
#include"ts.h"
#include"sensor.h"

#include"tcp.h"

#include<pthread.h>



int main(int argc, char const *argv[])
{
    //LCD初始化
    lcd_init();

    // 处理烟雾数据
    // handle_smoke();
    // 处理来自G39的数据
    // handle_gy();
    // lcd_color_check();

    pthread_t p1,p2;
    pthread_create(&p1,NULL,handle_smoke,NULL);
    pthread_create(&p2,NULL,handle_gy,NULL);


    int sock = create_tcp_socket(argv[1],atoi(argv[2]));
    while (1)
    {
        // printf("smoke:%d\thum:%d\tT:%d\n",value,Hum,T);
        tcp_send(sock);
    }

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    return 0;
}
