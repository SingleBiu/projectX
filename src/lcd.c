/*
 * @Author: SingleBiu
 * @Date: 2021-09-12 22:16:34
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-11 20:30:00
 * @Description: file content
 */
#include "lcd.h"



extern unsigned char w_0;
extern unsigned char w_1;
extern unsigned char w_2;
extern unsigned char w_3;
extern unsigned char w_4;
extern unsigned char w_5;
extern unsigned char w_6;
extern unsigned char w_7;
extern unsigned char w_8;
extern unsigned char w_9;
extern unsigned char w_baifenhao;
extern unsigned char w_du;
extern unsigned char w_dufuhao;
extern unsigned char w_maohao;
extern unsigned char w_nong;
extern unsigned char w_shi;
extern unsigned char w_wen;
extern unsigned char w_wu;
extern unsigned char w_yan;


/**
 * @description: LCD屏幕初始化
 * @param {*}
 * @return {*}
 */
void lcd_init()
{
    // 读写方式打开LCD文件
    lcd_fd = open(LCD_FILE, O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open LCD error");
        return;
    }

    // 使 plcd 指向缓冲区首地址
    plcd = mmap(NULL,
                WIDTH * HEIGHT * 4,
                PROT_READ | PROT_WRITE,
                MAP_SHARED,
                lcd_fd,
                0);
    printf("LCD init OK\n");
}

/**
 * @description: 在LCD屏幕上画一个color颜色的点
 * @param {int} x 屏幕的x坐标
 * @param {int} y 屏幕的y坐标
 * @param {int} color 要填充的颜色
 * @return {*}
 */
void lcd_draw_point(int x, int y, int color)
{
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    *(plcd + y * WIDTH + x) = color;
}

/**
 * @description: 在LCD的任意位置 显示一个任意大小的任意颜色的矩形
 * @param {uint} x0 矩形起始的x坐标
 * @param {uint} y0 矩形起始的y坐标
 * @param {uint} w  矩形的宽
 * @param {uint} h  矩形的高
 * @param {int} color  要填充的颜色
 * @return {*}
 */
void lcd_draw_rect(int x0, int y0, int w, int h, int color)
{
    int x, y;
    for (y = y0; y < y0 + h && y < HEIGHT; y++)
    {
        for (x = x0; x < x0 + w && x < WIDTH; x++)
            lcd_draw_point(x, y, color);
    }
}

/**
 * @description: 检测LCD屏幕有无坏点 测试用
 * @param {*}
 * @return {*}
 */
void lcd_color_check()
{
    while (1)
    {
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, BLACK);
        sleep(3);
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, RED);
        sleep(3);
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, GREEN);
        sleep(3);
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, BLUE);
        sleep(3);
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, YELLOW);
        sleep(3);
        lcd_draw_rect(0, 0, WIDTH, HEIGHT, WHITE);
        sleep(3);
    }
}

//在lcd上显示一个文字
// ch：文字的点阵数组
// len: 数组的长度
// w: 文字的宽度
// color: 文字的颜色
// x0,y0: 显示的起始点的横纵坐标
void lcd_draw_word(char *ch, int len, int w, int color, int x0, int y0)
{
    int i, j;
    int x, y;
    int flag = w / 8;
    //遍历整个点阵数组
    for (i = 0; i < len; i++)
    {
        for (j = 7; j >= 0; j--)
        {
            // if (ch[i] & (0x80/pow(2,7-j)))
            if ((ch[i] >> j) & 1)
            {
                x = 7 - j + 8 * (i % flag) + x0;
                y = i / flag + y0;
                lcd_draw_point(x, y, color);
            }
        }
    }
}

/**
 * @brief 在LCD上显示一个数字
 *
 * @param num   要显示的数字
 * @param lens  数字数组的长度
 * @param x0    起始点的横坐标
 * @param y0    起始点的纵坐标
 * @param w     数字的宽度
 * @param color 数字的颜色
 */
void display_num(int num, int lens, int w, int color, int x0, int y0)
{
    switch (num)
    {
    case 0:
        lcd_draw_word(&w_0, lens, w, color, x0, y0);
        break;
    case 1:
        lcd_draw_word(&w_1, lens, w, color, x0, y0);
        break;
    case 2:
        lcd_draw_word(&w_2, lens, w, color, x0, y0);
        break;
    case 3:
        lcd_draw_word(&w_3, lens, w, color, x0, y0);
        break;
    case 4:
        lcd_draw_word(&w_4, lens, w, color, x0, y0);
        break;
    case 5:
        lcd_draw_word(&w_5, lens, w, color, x0, y0);
        break;
    case 6:
        lcd_draw_word(&w_6, lens, w, color, x0, y0);
        break;
    case 7:
        lcd_draw_word(&w_7, lens, w, color, x0, y0);
        break;
    case 8:
        lcd_draw_word(&w_8, lens, w, color, x0, y0);
        break;
    case 9:
        lcd_draw_word(&w_9, lens, w, color, x0, y0);
        break;

    default:
        break;
    }
}