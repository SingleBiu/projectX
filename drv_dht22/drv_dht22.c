/*
 * @Author: SingleBiu
 * @Date: 2022-01-21 14:19:30
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-01-22 11:02:05
 * @Description: DHT22 driver
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
static struct cdev dht22_cdev;
static unsigned int devno_major = 0; //主设备号
static unsigned int devno_minor = 0; //次设备号
static dev_t dht22_dev_num;          //设备号
static struct class *dht22_class;
static struct device *dht22_device;

// 板子引脚  CON2 TX1
#define DHT_DATA (PAD_GPIO_D + 19)
// 命令cmd
#define GEC6818_GET_DHTDATA _IOR('K', 0, unsigned int)

static int gec6818_dht22_open(struct inode *inode, struct file *filp)
{
    gpio_set_value(DHT_DATA, 1);
    printk("DHT22 driver is opened\n");
    return 0;
}

static int gec6818_dht22_realse(struct inode *inode, struct file *filp)
{
    gpio_set_value(DHT_DATA, 1);
    printk("DHT22 driver is closed\n");
    return 0;
}

static unsigned char get_byte(void)
{
    int i, j = 0;
    int ret = 0;

    for (j = 0; j < 8; j++)
    {
        i = 0;
        while (!gpio_get_value(DHT_DATA))   // 等待总线拉高跳出
        {
            i++;
            udelay(1);
            if (j > 60)
            {
                printk("DHT22 high level get byte timeout error\n");
                break;
            }
        }

        udelay(22);
        
        ret <<= 1;          //将数据移到最高位
        if (gpio_get_value(DHT_DATA))
        {
            ret |= 0x01;    // 接收最高位放在第一位
        }

        i = 0;
   
        while (gpio_get_value(DHT_DATA))     // 等待总线拉低跳出
        {
            i++;
            udelay(1);
            if (i > 200)
            {
                printk("DHT22 low level get byte timeout error\n");
                break;
            }
        }
    }
    return ret;
}

static long gec6818_dht22_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret, i = 0;

    unsigned long flags;                //中断
    unsigned char dht22_data[5] = {0}; //数据组
    unsigned char checksum = 0;

    int hum = 0;    //湿度
    int temp = 0;   //温度

    int temp_h = 0; //温度高位
    int temp_l = 0; //温度低位

    if (cmd == GEC6818_GET_DHTDATA)
    {
        local_irq_save(flags);                     //关中断
        ret = gpio_direction_output(DHT_DATA, 0); //设置输出
        if (ret != 0)
        {
            printk("gpio_direction_output DHT_DATA error\n");
            goto gpio_err;
        }

        udelay(800); //主机拉低800us

        ret = gpio_direction_output(DHT_DATA, 1); //设置输出
        if (ret != 0)
        {
            printk("gpio_direction_output DHT_DATA error\n");
            goto gpio_err;
        }

        udelay(30); //主机拉高 30us

        ret = gpio_direction_input(DHT_DATA); // 设置输入

        if (gpio_get_value(DHT_DATA))    //如果响应会拉低总线
        {
            printk("DHT22 low level timeout error\n");
            local_irq_restore(flags);
            return -EAGAIN;
        }

        i = 0;

        while (!gpio_get_value(DHT_DATA)) //等待总线拉高跳出
        {
            i++;
            udelay(1);
            if (i > 100)
            {
                printk("DHT22 high level timeout error\n");
                local_irq_restore(flags);
                return -EAGAIN;
            }
        }

        i = 0;

        while (gpio_get_value(DHT_DATA)) //等待总线拉低跳出
        {
            i++;
            udelay(1);
            if (i > 100)
            {
                printk("DHT22 low level timeout error\n");
                    local_irq_restore(flags);
                return -EAGAIN;
            }
        }

        for (i = 0; i < 5; i++)
        {
            dht22_data[i] = get_byte();
        }

        checksum = dht22_data[0] + dht22_data[1] + dht22_data[2] + dht22_data[3];
        if (checksum != dht22_data[4])
        {
            printk("DHT22 checksum error\n");
            return -EAGAIN;
        }

        local_irq_restore(flags); //恢复中断
    }
    else
        return -EINVAL; //无效命令

    hum = (dht22_data[0] * 256 + dht22_data[1]) / 10;    //湿度
    temp = (dht22_data[2] * 256 + dht22_data[3]) / 10;   //温度

    //高精度
    temp_h = (dht22_data[2] * 256 + dht22_data[3]) / 10; //温度高位 小数点以前
    temp_l = (dht22_data[2] * 256 + dht22_data[3]) % 10; //温度地位 小数点之后

    // DEBUG INFO
    printk("kdata: u8  th_data = %d %d  temp_data = %d %d\n", dht22_data[0], dht22_data[1], dht22_data[2], dht22_data[3]);
    printk("kdata:temp_h : %d temp_l : %d\n", temp_h, temp_l);
    printk("kdata:int th_data = %d  temp_data = %d\n", hum, temp);

    ret = copy_to_user(((int *)arg), &hum, sizeof(hum));             //拷贝湿度
    if (ret != 0)
        return -EFAULT;
    ret = copy_to_user(((int *)arg) + 1, &temp_h, (sizeof(temp_h))); //拷贝温度
    ret = copy_to_user(((int *)arg) + 2, &temp_l, (sizeof(temp_l))); //拷贝温度
    if (ret != 0)
        return -EFAULT;

    return 0;

gpio_err:
    //恢复中断
    local_irq_restore(flags);
    return ret;
}

static const struct file_operations gec6818_dht22_fops =
    {
        .owner = THIS_MODULE,
        .open = gec6818_dht22_open,
        .release = gec6818_dht22_realse,
        .unlocked_ioctl = gec6818_dht22_ioctl,
};

//驱动初始化
static int __init gec6818_dht22_init(void)
{
    int ret;
  
    if (devno_major == 0)  //获取设备号
    {
        ret = alloc_chrdev_region(&dht22_dev_num, devno_minor, 1, "dht22_device");
    }
    else
    {
        dht22_dev_num = MKDEV(devno_major, devno_minor);
        ret = register_chrdev_region(dht22_dev_num, 1, "dht22_device");
    }
    if (ret < 0)
    {
        printk("Can not get dht22 device number\n");
        return ret;
    }

    cdev_init(&dht22_cdev,&gec6818_dht22_fops); //初始化cdev

    ret = cdev_add(&dht22_cdev, dht22_dev_num, 1); //将初始化好的cdev加入内核
    if (ret < 0)
    {
        printk("cdev add error\n");
        goto cdev_add_err;
    }
   
    dht22_class = class_create(THIS_MODULE, "DHT22_class"); //创建class
    if (IS_ERR(dht22_class))
    {
        ret = PTR_ERR(dht22_class);
        printk("DHT22 driver class create error\n");
        goto class_create_err;
    }

    dht22_device = device_create(dht22_class, NULL, dht22_dev_num, NULL, "dht22_dev");
    if (IS_ERR(dht22_device))
    {
        ret = PTR_ERR(dht22_device);
        printk("dht22 driver device create error\n");
        goto device_create_err;
    }

    if (gpio_request(DHT_DATA, "DHT_DATA") != 0) //申请物理内存区
    {
        printk("gpio_request error\n");
    }

    ret = gpio_direction_output(DHT_DATA, 1); //设置输出
    if (ret != 0)
    {
        printk("gpio_direction_output DHT_DATA error\n");
        gpio_free(DHT_DATA);
        goto device_create_err;
    }

    printk(KERN_INFO "gec6818_dht22_init\n");
    return 0;

    //错误处理
device_create_err:
    class_destroy(dht22_class);
class_create_err:
    cdev_del(&dht22_cdev);
cdev_add_err:
    unregister_chrdev_region(dht22_dev_num, 1);
    return ret;
}

//驱动卸载
static void __exit gec6818_dht22_exit(void)
{
    gpio_free(DHT_DATA);
    device_destroy(dht22_class, dht22_dev_num);
	class_destroy(dht22_class);
	cdev_del(&dht22_cdev);
	unregister_chrdev_region(dht22_dev_num, 1);
	printk(KERN_INFO "gec6818_dht22_exit\n");
}

module_init(gec6818_dht22_init);
module_exit(gec6818_dht22_exit);

MODULE_AUTHOR("SingleBiu@hotmail.com");
MODULE_DESCRIPTION("DHT22 driver for GEC6818");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0");

