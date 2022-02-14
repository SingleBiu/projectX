/*
 * @Author: SingleBiu
 * @Date: 2022-02-13 19:20:23
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-14 19:06:21
 * @Description: file content
 */
/*
 * @Author: SingleBiu
 * @Date: 2022-02-13 18:35:00
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-13 19:19:54
 * @Description: file content
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/time.h>
#include "cfg_type.h"   //GPIO定义 非Liunx系统文件

//定义一个字符设备
static struct cdev fire_detect_cdev;
static unsigned int devno_major = 0; //主设备号
static unsigned int devno_minor = 0; //次设备号
static dev_t fire_detect_dev_num;          //设备号
static struct class *fire_detect_class;
static struct device *fire_detect_device;

// 板子引脚  CON3 TX1
#define FIRE_DATA (PAD_GPIO_D + 20)
// 命令cmd
#define GEC6818_GET_FIREDATA _IOR('F', 0, unsigned int)

static int gec6818_fire_detect_open(struct inode *inode, struct file *filp)
{
    gpio_set_value(FIRE_DATA, 1);
    printk("fire_detect driver is opened\n");
    return 0;
}

static int gec6818_fire_detect_realse(struct inode *inode, struct file *filp)
{
    gpio_set_value(FIRE_DATA, 1);
    printk("fire_detect driver is closed\n");
    return 0;
}


static long gec6818_fire_detect_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret,fire = 0;

    unsigned long flags;                //中断


    if (cmd == GEC6818_GET_FIREDATA)
    {
        local_irq_save(flags);                     //关中断

        ret = gpio_direction_input(FIRE_DATA); // 设置输入
        if (ret != 0)
        {
            printk("gpio_direction_intput FIRE_DATA error\n");
            goto gpio_err;
        }

        //环境火焰光谱或光源低于设定阈值时D0口输出高电平
        //环境火焰光谱或光源超过设定阈值时D0口输出低电平

        //无火焰默认高电平
        if (gpio_get_value(FIRE_DATA))    
        {
            // printk("NO fire detected\n");
            return 0;
        }
        else
        {
            // printk("WARING:Fire detected\n");
            fire = 1;
            ret = copy_to_user(((int *)arg), &fire, sizeof(fire));             //拷贝结果
            if (ret != 0)
                return -EFAULT;
            return 0;
        }

        //恢复
        fire = 0;

        local_irq_restore(flags); //恢复中断
    }
    else
        return -EINVAL; //无效命令


    ret = copy_to_user(((int *)arg), &fire, sizeof(fire));             //拷贝结果
    if (ret != 0)
        return -EFAULT;


    return 0;

gpio_err:
    //恢复中断
    local_irq_restore(flags);
    return ret;
}

static const struct file_operations gec6818_fire_detect_fops =
    {
        .owner = THIS_MODULE,
        .open = gec6818_fire_detect_open,
        .release = gec6818_fire_detect_realse,
        .unlocked_ioctl = gec6818_fire_detect_ioctl,
};

//驱动初始化
static int __init gec6818_fire_detect_init(void)
{
    int ret;
  
    if (devno_major == 0)  //获取设备号
    {
        ret = alloc_chrdev_region(&fire_detect_dev_num, devno_minor, 1, "fire_detect_device");
    }
    else
    {
        fire_detect_dev_num = MKDEV(devno_major, devno_minor);
        ret = register_chrdev_region(fire_detect_dev_num, 1, "fire_detect_device");
    }
    if (ret < 0)
    {
        printk("Can not get fire_detect device number\n");
        return ret;
    }

    cdev_init(&fire_detect_cdev,&gec6818_fire_detect_fops); //初始化cdev

    ret = cdev_add(&fire_detect_cdev, fire_detect_dev_num, 1); //将初始化好的cdev加入内核
    if (ret < 0)
    {
        printk("cdev add error\n");
        goto cdev_add_err;
    }
   
    fire_detect_class = class_create(THIS_MODULE, "fire_detect_class"); //创建class
    if (IS_ERR(fire_detect_class))
    {
        ret = PTR_ERR(fire_detect_class);
        printk("fire_detect driver class create error\n");
        goto class_create_err;
    }

    fire_detect_device = device_create(fire_detect_class, NULL, fire_detect_dev_num, NULL, "fire_detect_dev");
    if (IS_ERR(fire_detect_device))
    {
        ret = PTR_ERR(fire_detect_device);
        printk("fire_detect driver device create error\n");
        goto device_create_err;
    }

    if (gpio_request(FIRE_DATA, "FIRE_DATA") != 0) //申请物理内存区
    {
        printk("gpio_request error\n");
    }

    ret = gpio_direction_output(FIRE_DATA, 1); //设置输出
    if (ret != 0)
    {
        printk("gpio_direction_output FIRE_DATA error\n");
        gpio_free(FIRE_DATA);
        goto device_create_err;
    }

    printk(KERN_INFO "gec6818_fire_detect_init\n");
    return 0;

    //错误处理
device_create_err:
    class_destroy(fire_detect_class);
class_create_err:
    cdev_del(&fire_detect_cdev);
cdev_add_err:
    unregister_chrdev_region(fire_detect_dev_num, 1);
    return ret;
}

//驱动卸载
static void __exit gec6818_fire_detect_exit(void)
{
    gpio_free(FIRE_DATA);
    device_destroy(fire_detect_class, fire_detect_dev_num);
	class_destroy(fire_detect_class);
	cdev_del(&fire_detect_cdev);
	unregister_chrdev_region(fire_detect_dev_num, 1);
	printk(KERN_INFO "gec6818_fire_detect_exit\n");
}

module_init(gec6818_fire_detect_init);
module_exit(gec6818_fire_detect_exit);

MODULE_AUTHOR("SingleBiu@hotmail.com");
MODULE_DESCRIPTION("fire_detect driver for GEC6818");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0");

