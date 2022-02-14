/*
 * @Author: SingleBiu
 * @Date: 2022-01-14 11:08:47
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-01-14 20:31:02
 * @Description: file content
 */
#if !defined(__GENERAL_GPIO_H__)
#define __GENERAL_GPIO_H__

#include <asm/ioctl.h>

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

#endif // __GENERAL_GPIO_H__
