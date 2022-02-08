/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 09:39:38
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-09-13 09:49:06
 * @Description: file content
 */
#ifndef __SENSER_H__
#define __SENSER_H__


#define GY39_FILE "/dev/ttySAC2"
// 温湿度数据
unsigned int T,Hum;

void* handle_gy();
void handle_GY_Values(unsigned int T,unsigned int Hum);




#define SMOKE_FILE "/dev/ttySAC1"
// 烟雾数据value
unsigned int value;

void* handle_smoke();
void handleSmokeValues(unsigned int value);





#endif