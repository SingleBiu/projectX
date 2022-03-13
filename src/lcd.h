/*
 * @Author: SingleBiu
 * @Date: 2021-09-12 22:16:39
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-11 20:13:50
 * @Description: file content
 */
#ifndef __LCD_H__
#define __LCD_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>




// 显示屏宽高
#define WIDTH 800
#define HEIGHT 480

// 常用颜色
#define RED       0xff0000
#define GREEN     0x00ff00
#define BLUE      0x0000ff
#define YELLOW    0xffff00
#define BLACK     0x000000
#define WHITE     0xffffff

// // 模拟屏LCD文件
// #define LCD_FILE "/dev/ubuntu_lcd"

// 帧缓冲设备文件描述符
#define LCD_FILE "/dev/fb0"
// 帧缓冲首地址
static int *plcd = NULL;
// LCD_FILE的文件描述符
static int lcd_fd;

void lcd_init();
void lcd_draw_point(int x,int y,int color);
void lcd_draw_rect(int x0, int y0, int w, int h, int color);
void lcd_color_check();
void lcd_draw_word(char *ch, int len, int w, int color, int x0, int y0);
void display_num(int num, int lens, int w, int color, int x0, int y0);




#endif