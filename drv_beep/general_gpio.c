/*
 * @Author: SingleBiu
 * @Date: 2022-01-14 10:56:30
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-01-14 20:33:46
 * @Description: file content
 */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/io.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#include<linux/device.h>
#include<linux/gpio.h>
#include<linux/uaccess.h>
#include<linux/miscdevice.h>

#include<cfg_type.h>

#include"general_gpio.h"

//次设备号
int devno_minor = 0;

struct general_gpio_gpio
{
    unsigned int num;
};

struct general_gpio_gpio general_gpio_arr[32];
int gpio_use_count = 0;

module_param(devno_minor,int,0660);

//定义混杂设备
struct miscdevice gpio_misc;

//定义文件操作集合
int general_gpio_open(struct inode *inode,struct file *filp)
{
    printk("General GPIO module has been opened\n");
    return 0;
}
ssize_t general_gpio_read(struct file *filp,char *__user_buf,size_t size,loff_t *off)
{
    return size;
}
ssize_t general_gpio_write(struct file *filp,const char *__user_buf,size_t size,loff_t *off)
{
    return size;
}
int general_gpio_release(struct inode *inode,struct file *filp)
{
    printk("General GPIO module closed\n");
    return 0;
}
long general_gpio_ioctl(struct file * filp,unsigned int cmd,unsigned long args)
{
    long ret = 0;
    gpio_cfg_t gpio_cfg;
    gpio_val_t gpio_val;
    
    switch(cmd)
	{
		case GPIO_CONFIG:
			if(copy_from_user(&gpio_cfg, (__user gpio_cfg_t*) args, sizeof(gpio_cfg_t)))
			{
				return  -EINVAL;
			}
			
			if(gpio_request(gpio_cfg.gpio_no,"UNIVERSAL GPIO"))//申请GPIO
	   		{
				return  -EINVAL;
	   		}
			if(gpio_cfg.gpio_mode == GPIO_MODE_INPUT)
			{
				gpio_direction_input(gpio_cfg.gpio_no);
			}
			else if(gpio_cfg.gpio_mode == GPIO_MODE_OUTPUT)
			{
				gpio_direction_output(gpio_cfg.gpio_no, gpio_cfg.gpio_init_value);
			}
			else
			{
				return  -EINVAL;
			}
			general_gpio_arr[gpio_use_count++].num = gpio_cfg.gpio_no;//保存gpio编号
			printk("GPIO%c%d request success!\n",'A'+gpio_cfg.gpio_no/32,gpio_cfg.gpio_no%32);
			break;
		case GPIO_SET_VALUE:
			if(copy_from_user(&gpio_val, (__user gpio_val_t*) args, sizeof(gpio_val_t)))
			{
				return  -EINVAL;
			}
			__gpio_set_value(gpio_val.gpio_no, gpio_val.gpio_val);
			break;
		case GPIO_GET_VALUE:
			if(copy_from_user(&gpio_val, (__user gpio_val_t*) args, sizeof(gpio_val_t)))
			{
				return  -EINVAL;
			}
			gpio_val.gpio_val = __gpio_get_value(gpio_val.gpio_no);
			if(copy_to_user((__user gpio_val_t*) args, &gpio_val, sizeof(gpio_val_t)))
			{
				return  -EINVAL;
			}
			break;
			
	}

    return ret;
}

static const struct file_operations general_gpio_fops =
{
    .owner = THIS_MODULE,
    .open = general_gpio_open,
    .read = general_gpio_read,
    .write = general_gpio_write,
    .release = general_gpio_release,
    .unlocked_ioctl = general_gpio_ioctl
};




static int __init general_gpio_init(void)
{
    // 返回值
    int ret = 0;

    // 注册混杂设备
    // 次设备号
    gpio_misc.minor = devno_minor;
    // 混杂设备名称
    gpio_misc.name = "gpio_misc";
    // 文件操作集合
    gpio_misc.fops = &general_gpio_fops;

    if (misc_register(&gpio_misc))
    {
        ret = -EINVAL;
        goto misc_register_err;
    }
    
    printk("general gpio module init success\n");
    return 0;

misc_register_err:
    return ret;
}

static void __exit general_gpio_exit(void)
{
    while (gpio_use_count--)
    {
        gpio_free(general_gpio_arr[gpio_use_count].num);
    }
    misc_deregister(&gpio_misc);
    printk("general gpio module exit\n");
}

module_init(general_gpio_init);
module_exit(general_gpio_exit);

MODULE_AUTHOR("SingleBiu@hotmail.com");
MODULE_DESCRIPTION("General GPIO driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0");