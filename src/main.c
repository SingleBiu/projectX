/*
 * @Author: SingleBiu
 * @Date: 2021-09-12 22:16:08
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-14 19:20:22
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
    //清屏
    lcd_draw_rect(0,0,800,480,WHITE);

    //打开蜂鸣器 BEEP
    int beep_fd = open(BEEP_FD,O_RDWR);
    if(beep_fd == -1)
	{
		printf("beep open failed!\n");
		return -1;
	}
    beep_init(beep_fd);

    //打开火焰传感器 FIRE_DETECT
    int fire_state,ret;
    int fire_fd = open(FIRE_DETECT,O_RDWR);
    if (fire_fd < 0)
    {
        printf("fire detect open failed!\n");
        return -1;
    }
    

    pthread_t p1;
    pthread_create(&p1,NULL,handle_dht22,NULL);
    // pthread_create(&p2,NULL,handle_gy,NULL);

    while (1)
	{
		ret = ioctl(fire_fd, GEC6818_GET_FIREDATA, &fire_state);
		if (ret != 0)
		{
			perror("GEC6818_GET_FIREDATA error");
		}
		else
		{
			printf("app: Fire_detect:%d\n", fire_state);
            if(fire_state == 1)
            {
                beep_ctrl(beep_fd,BEEP_ON);
                sleep(2);
                beep_ctrl(beep_fd,BEEP_OFF);
            }
            fire_state = 0;
            beep_ctrl(beep_fd,BEEP_OFF);
		}
		sleep(2);
	}
	close(fire_fd);
	close(beep_fd);

    // int sock = create_tcp_socket(argv[1],atoi(argv[2]));
    // while (1)
    // {
    //     // printf("smoke:%d\thum:%d\tT:%d\n",value,Hum,T);
    //     // tcp_send(sock);
    // }

    pthread_join(p1,NULL);
    // pthread_join(p2,NULL);

    return 0;
}
