/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 09:39:38
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-14 18:46:12
 * @Description: file content
 */
#ifndef __SENSER_H__
#define __SENSER_H__

#include <sys/ioctl.h>
#include <asm/ioctl.h>


#define DHT22 "/dev/dht22_dev"
#define GEC6818_GET_DHTDATA _IOR('K', 0, unsigned int) //注册宏

#define FIRE_DETECT "/dev/fire_detect_dev"
#define GEC6818_GET_FIREDATA _IOR('F', 0, unsigned int) //注册宏

// 温湿度数据
unsigned int T,Hum;

void *handle_dht22();
void diplay_dht22_data(int Hum,int T,int T_l);
void beep_init(int fd);
void beep_ctrl(int fd, int beep_state);


//烟雾数据
unsigned int value;


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

#define BEEP_FD "/dev/gpio_misc"

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