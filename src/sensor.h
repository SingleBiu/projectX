/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 09:39:38
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-13 20:57:04
 * @Description: file content
 */
#ifndef __SENSER_H__
#define __SENSER_H__

#include <sys/ioctl.h>
#include <asm/ioctl.h>

#include <semaphore.h>

//DHT22文件描述符
#define DHT22 "/dev/dht22_dev"
#define GEC6818_GET_DHTDATA _IOR('K', 0, unsigned int) //注册宏

//火焰探测器文件描述符
#define FIRE_DETECT "/dev/fire_detect_dev"
#define GEC6818_GET_FIREDATA _IOR('F', 0, unsigned int) //注册宏

//蜂鸣器文件描述符
#define BEEP_FD "/dev/gpio_misc"

// 温湿度数据
unsigned int T,Hum;

//信号量
sem_t semDHT;
sem_t semFire;

// DHT22温湿度数据 湿度 data[0] 温度 data[1]  小数点后温度 data[2]
int data[3];

void *handle_dht22();
void diplay_dht22_data(int Hum,int T,int T_l);
void beep_init(int fd);
void beep_ctrl(int fd, int beep_state);
void *handle_fire_detect();


//烟雾数据
unsigned int value;

//火焰警报数据
unsigned int fire_state;


enum GPIO_NO
{
    GPIO_A = (0 * 32),
    GPIO_B = (1 * 32),
    GPIO_C = (2 * 32),
    GPIO_D = (3 * 32),
    GPIO_E = (4 * 32),
    GPIO_ALV = (5 * 32)
};

// GPIO模式
enum GPIO_MODE
{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT
};

// 初始化GPIO用到的结构体
typedef struct general_gpio_cfg
{
    unsigned int gpio_no;
    unsigned int gpio_mode;
    unsigned int gpio_init_value;
} gpio_cfg_t;

// 更新GPIO值用到的结构体
typedef struct general_gpio_val
{
    unsigned int gpio_no;
    unsigned int gpio_val;
} gpio_val_t;


#define GPIO_CONFIG      _IOW('G',1,gpio_cfg_t)
#define GPIO_SET_VALUE   _IOW('G',2,gpio_val_t)
#define GPIO_GET_VALUE   _IOWR('G',3,gpio_val_t)

enum BEEP_STATE
{
    BEEP_OFF,
    BEEP_ON
};

enum KEY_NUM
{
    KEY1,
    KEY2,
    KEY3,
    KEY4
};

enum KEY_STATUS
{
    KEY_DOWN,
    KEY_UP
};

enum LED_NUM
{
    LED1,
    LED2,
    LED3,
    LED4,
};

enum LED_STATE
{
    LED_ON,
    LED_OFF
};

#endif