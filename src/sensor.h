/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 09:39:38
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-08 20:11:29
 * @Description: file content
 */
#ifndef __SENSER_H__
#define __SENSER_H__

#include <sys/ioctl.h>

#define DHT22 "/dev/dht22_dev"
#define GEC6818_GET_DHTDATA _IOR('K', 0, unsigned int) //注册宏
// 温湿度数据
unsigned int T,Hum;

void *handle_dht22();
void diplay_dht22_data(int Hum,int T,int T_l);

// void* handle_gy();
// void handle_GY_Values(unsigned int T,unsigned int Hum);




// #define SMOKE_FILE "/dev/ttySAC1"
// 烟雾数据value
unsigned int value;

// void* handle_smoke();
// void handleSmokeValues(unsigned int value);





#endif