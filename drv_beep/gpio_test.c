/*
 * @Author: SingleBiu
 * @Date: 2022-01-14 20:13:47
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-14 18:26:49
 * @Description: file content
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "general_gpio.h"

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

void beep_init(int fd)//GPIOC14
{
	gpio_cfg_t tmp;
	tmp.gpio_no = GPIO_C+14;
	tmp.gpio_mode = GPIO_MODE_OUTPUT;
	tmp.gpio_init_value = BEEP_OFF;
	// if(ioctl(fd,GPIO_CONFIG,&tmp))
	// {
	// 	printf("beep init failed!\n");
	// }
}

void beep_ctrl(int fd, int beep_state)
{
	gpio_val_t tmp;
	tmp.gpio_no = GPIO_C+14;
	tmp.gpio_val = beep_state;
	if(ioctl(fd,GPIO_SET_VALUE,&tmp))
	{
		printf("beep ctrl failed!\n");
	}
}

void key_init(int fd)//GPIOA28,GPIOB9,GPIOB30,GPIOB31
{
	gpio_cfg_t tmp;
	tmp.gpio_no = GPIO_A+28;
	tmp.gpio_mode = GPIO_MODE_INPUT;
	if(ioctl(fd,GPIO_CONFIG,&tmp))
	{
		printf("key init failed!\n");
	}
	tmp.gpio_no = GPIO_B+9;
	if(ioctl(fd,GPIO_CONFIG,&tmp))
	{
		printf("key init failed!\n");
	}
	tmp.gpio_no = GPIO_B+30;
	if(ioctl(fd,GPIO_CONFIG,&tmp))
	{
		printf("key init failed!\n");
	}
	tmp.gpio_no = GPIO_B+31;
	if(ioctl(fd,GPIO_CONFIG,&tmp))
	{
		printf("key init failed!\n");
	}
}

int key_status(int fd,int key_num)
{
	gpio_val_t tmp;
	switch(key_num)
	{
		case KEY1:
			tmp.gpio_no = GPIO_A+28;
			if(ioctl(fd,GPIO_GET_VALUE,&tmp))
			{
				printf("key init failed!\n");
			}
			return tmp.gpio_val;
		case KEY2:
			tmp.gpio_no = GPIO_B+9;
			if(ioctl(fd,GPIO_GET_VALUE,&tmp))
			{
				printf("key init failed!\n");
			}
			return tmp.gpio_val;
		case KEY3:
			tmp.gpio_no = GPIO_B+30;
			if(ioctl(fd,GPIO_GET_VALUE,&tmp))
			{
				printf("key init failed!\n");
			}
			return tmp.gpio_val;
		case KEY4:
			tmp.gpio_no = GPIO_B+31;
			if(ioctl(fd,GPIO_GET_VALUE,&tmp))
			{
				printf("key init failed!\n");
			}
			return tmp.gpio_val;
			
	}
}

void led_init(int fd)//GPIOE13,GPIOC17,GPIOC7,GPIOC8
{
	gpio_cfg_t tmp;
	tmp.gpio_no = GPIO_E+13;
	tmp.gpio_mode = GPIO_MODE_OUTPUT;
	tmp.gpio_init_value = LED_OFF;
	// if(ioctl(fd,GPIO_CONFIG,&tmp))
	// {
	// 	printf("led init failed!\n");
	// }
	tmp.gpio_no = GPIO_C+17;
	// if(ioctl(fd,GPIO_CONFIG,&tmp))
	// {
	// 	printf("led init failed!\n");
	// }
	tmp.gpio_no = GPIO_C+7;
	// if(ioctl(fd,GPIO_CONFIG,&tmp))
	// {
	// 	printf("led init failed!\n");
	// }
	tmp.gpio_no = GPIO_C+8;
	// if(ioctl(fd,GPIO_CONFIG,&tmp))
	// {
	// 	printf("led init failed!\n");
	// }
}

//GPIOE13,GPIOC17,GPIOC7,GPIOC8
void led_ctrl(int fd, int led_num, int led_state)
{
	gpio_val_t tmp;
	switch(led_num)
	{
		case LED1:
			tmp.gpio_no = GPIO_E+13;
			tmp.gpio_val = led_state;
			if(ioctl(fd,GPIO_SET_VALUE,&tmp))
			{
				printf("led set failed!\n");
			}
			break;
		case LED2:
			tmp.gpio_no = GPIO_C+17;
			tmp.gpio_val = led_state;
			if(ioctl(fd,GPIO_SET_VALUE,&tmp))
			{
				printf("led set failed!\n");
			}
			break;
		case LED3:
			tmp.gpio_no = GPIO_C+7;
			tmp.gpio_val = led_state;
			if(ioctl(fd,GPIO_SET_VALUE,&tmp))
			{
				printf("led set failed!\n");
			}
			break;
		case LED4:
			tmp.gpio_no = GPIO_C+8;
			tmp.gpio_val = led_state;
			if(ioctl(fd,GPIO_SET_VALUE,&tmp))
			{
				printf("led set failed!\n");
			}
			break;
	}
}
int main()
{
	int fd = open("/dev/gpio_misc",O_RDWR);
	if(fd == -1)
	{
		printf("open failed!\n");
		return -1;
	}
	beep_init(fd);
	key_init(fd);
	led_init(fd);

	while(1)
	{
		led_ctrl(fd,LED1,key_status(fd,KEY1));
		led_ctrl(fd,LED2,key_status(fd,KEY2));
		led_ctrl(fd,LED3,key_status(fd,KEY3));
		led_ctrl(fd,LED4,key_status(fd,KEY4));

		beep_ctrl(fd,BEEP_OFF);
		sleep(2);
		beep_ctrl(fd,BEEP_ON);
		sleep(1);

	}

	close(fd);
}