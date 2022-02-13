/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 09:39:33
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-02-11 21:07:32
 * @Description: file content
 */
#include "sensor.h"
#include "lcd.h"

// extern unsigned char w_0;
// extern unsigned char w_1;
// extern unsigned char w_2;
// extern unsigned char w_3;
// extern unsigned char w_4;
// extern unsigned char w_5;
// extern unsigned char w_6;
// extern unsigned char w_7;
// extern unsigned char w_8;
// extern unsigned char w_9;
// extern unsigned char w_baifenhao;
// extern unsigned char w_du;
// extern unsigned char w_dufuhao;
// extern unsigned char w_maohao;
// extern unsigned char w_nong;
// extern unsigned char w_shi;
// extern unsigned char w_wen;
// extern unsigned char w_wu;
// extern unsigned char w_yan;

// template
// unsigned char w_word[] = {};

//宽x高
// 16x16

// 'C
unsigned char w_dufuhao[] = {
    0x60, 0x00, 0x91, 0xF4, 0x96, 0x0C, 0x6C, 0x04, 0x08, 0x04, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
    0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x08, 0x00, 0x0C, 0x04, 0x06, 0x08, 0x01, 0xF0, 0x00, 0x00};

// . 8x16
unsigned char w_dian[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00};

//湿
unsigned char w_shi[] = {
    0x00, 0x00, 0x27, 0xF8, 0x14, 0x08, 0x14, 0x08, 0x87, 0xF8, 0x44, 0x08, 0x44, 0x08, 0x17, 0xF8,
    0x11, 0x20, 0x21, 0x20, 0xE9, 0x24, 0x25, 0x28, 0x23, 0x30, 0x21, 0x20, 0x2F, 0xFE, 0x00, 0x00};

// 烟
unsigned char w_yan[] = {
    0x10, 0x00, 0x13, 0xFE, 0x12, 0x02, 0x16, 0x22, 0x5A, 0x22, 0x52, 0x22, 0x53, 0xFE, 0x92, 0x22,
    0x12, 0x22, 0x12, 0x52, 0x12, 0x4A, 0x2A, 0x8A, 0x27, 0x02, 0x42, 0x02, 0x43, 0xFE, 0x82, 0x02};

// 雾
unsigned char w_wu[] = {
    0x3F, 0xF8, 0x01, 0x00, 0x7F, 0xFE, 0x41, 0x02, 0x9D, 0x74, 0x01, 0x00, 0x1D, 0x70, 0x04, 0x00,
    0x0F, 0xE0, 0x14, 0x40, 0x03, 0x80, 0x1C, 0x70, 0xE2, 0x0E, 0x0F, 0xE0, 0x04, 0x20, 0x18, 0x60};

// 温
unsigned char w_wen[] = {
    0x00, 0x00, 0x23, 0xF8, 0x12, 0x08, 0x12, 0x08, 0x83, 0xF8, 0x42, 0x08, 0x42, 0x08, 0x13, 0xF8,
    0x10, 0x00, 0x27, 0xFC, 0xE4, 0xA4, 0x24, 0xA4, 0x24, 0xA4, 0x24, 0xA4, 0x2F, 0xFE, 0x00, 0x00};

// 浓
unsigned char w_nong[] = {
    0x00, 0x40, 0x20, 0x40, 0x10, 0x40, 0x17, 0xFC, 0x84, 0x84, 0x48, 0x88, 0x41, 0x40, 0x11, 0x44,
    0x13, 0x48, 0x25, 0x30, 0xE9, 0x20, 0x21, 0x10, 0x21, 0x08, 0x21, 0x44, 0x21, 0x82, 0x01, 0x00};

// 度
unsigned char w_du[] = {
    0x01, 0x00, 0x00, 0x80, 0x3F, 0xFE, 0x22, 0x20, 0x22, 0x20, 0x3F, 0xFC, 0x22, 0x20, 0x22, 0x20,
    0x23, 0xE0, 0x20, 0x00, 0x2F, 0xF0, 0x24, 0x10, 0x42, 0x20, 0x41, 0xC0, 0x86, 0x30, 0x38, 0x0E};

// 8x16

// 显示冒号  “ : ”
unsigned char w_maohao[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00};

//  显示%
unsigned char w_baifenhao[] = {
    0x00, 0x00, 0x00, 0x44, 0xA4, 0xA8, 0xA8, 0xB0, 0x54, 0x1A, 0x2A, 0x2A, 0x4A, 0x44, 0x00, 0x00};

unsigned char w_0[] = {
    0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00};
unsigned char w_1[] = {
    0x00, 0x00, 0x00, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};
unsigned char w_2[] = {
    0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x02, 0x04, 0x08, 0x10, 0x20, 0x42, 0x7E, 0x00, 0x00};
unsigned char w_3[] = {
    0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 0x04, 0x18, 0x04, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};
unsigned char w_4[] = {
    0x00, 0x00, 0x00, 0x04, 0x0C, 0x0C, 0x14, 0x24, 0x24, 0x44, 0x7F, 0x04, 0x04, 0x1F, 0x00, 0x00};
unsigned char w_5[] = {
    0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 0x78, 0x44, 0x02, 0x02, 0x42, 0x44, 0x38, 0x00, 0x00};
unsigned char w_6[] = {
    0x00, 0x00, 0x00, 0x18, 0x24, 0x40, 0x40, 0x5C, 0x62, 0x42, 0x42, 0x42, 0x22, 0x1C, 0x00, 0x00};
unsigned char w_7[] = {
    0x00, 0x00, 0x00, 0x7E, 0x42, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};
unsigned char w_8[] = {
    0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};
unsigned char w_9[] = {
    0x00, 0x00, 0x00, 0x38, 0x44, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02, 0x24, 0x18, 0x00, 0x00};


/**
 * @brief 获取DHT22传感器的数据
 * 
 * @return void* 
 */
void *handle_dht22()
{
    int ret, cnt_yes = 0, cnt_err = 0;

    int data[3];
    int dht22_fd = open(DHT22, O_RDWR);
    if (dht22_fd < 0)
    {
        perror("open dht22_dev driver");
    }

    //文字显示
    //温度：
    lcd_draw_word(w_wen, sizeof(w_wen), 16, BLACK, 660, 70);
    lcd_draw_word(w_du, sizeof(w_du), 16, BLACK, 676, 70);
    lcd_draw_word(w_maohao, sizeof(w_maohao), 8, BLACK, 692, 70);
    // lcd_draw_word(w_dian,sizeof(w_dian),8,BLACK,716,70);
    lcd_draw_word(w_dufuhao, sizeof(w_dufuhao), 16, BLACK, 732, 70);
    //湿度：
    lcd_draw_word(w_shi, sizeof(w_wen), 16, BLACK, 660, 85);
    lcd_draw_word(w_du, sizeof(w_du), 16, BLACK, 676, 85);
    lcd_draw_word(w_maohao, sizeof(w_maohao), 8, BLACK, 692, 85);
    lcd_draw_word(w_baifenhao, sizeof(w_baifenhao), 8, BLACK, 716, 85);

    while (1)
    {
        ret = ioctl(dht22_fd, GEC6818_GET_DHTDATA, &data[0]);
        if (ret != 0)
        {
            cnt_err++;
            perror("GEC6818_GET_DHTDATA error");
            break;
        }
        else
        {
            cnt_yes++;
            printf("app:  Hum= %d  Temprature=%d.%d  err:%d  correct:%d\n", data[0], data[1], data[2], cnt_err, cnt_yes);
        }
        diplay_dht22_data(data[0], data[1], data[2]);
        //根据说明 至少延时2秒获取数据
        sleep(2);
    }
    close(dht22_fd);
}

/**
 * @brief 显示DHT22获得的数据
 *
 * @param Hum  湿度
 * @param T    温度
 * @param T_l  小数点后的温度
 */
void diplay_dht22_data(int Hum, int T, int T_l)
{
    //清屏
    lcd_draw_rect(700, 70, 32, 16, BLUE);
    lcd_draw_rect(700, 85, 32, 16, BLUE);

    //小数
    lcd_draw_word(w_dian, sizeof(w_dian), 8, BLACK, 716, 70);

    //温度十位
    int T_decade;
    //温度个位
    int T_units;
    //湿度十位
    int Hum_decade;
    //湿度个位
    int Hum_units;

    T_decade = T % 100 / 10;
    T_units = T % 10;

    Hum_decade = Hum % 100 / 10;
    Hum_units = Hum % 10;

    int num[] = {
        T_decade,   //温度十位
        T_units,    //温度个位
        T_l,        //温度 小数点后一位
        Hum_decade, //湿度十位
        Hum_units,  //湿度个位
    };

    // 数字数组大小 8x16
    int num_len = sizeof(w_0);

    //显示温度
    display_num(num[0],num_len,8,BLACK,700,70);
    display_num(num[1],num_len,8,BLACK,708,70);
    display_num(num[2],num_len,8,BLACK,724,70);

    //显示湿度
    display_num(num[3],num_len,8,BLACK,700,85);
    display_num(num[4],num_len,8,BLACK,708,85);


}

#if 0
/**
 * @description: 处理收到的烟雾数据
 * @param {unsigned int value} 烟雾数据
 * @return {null} 
 */
void handleSmokeValues(unsigned int value){
    // 烟雾浓度 文字显示
    lcd_draw_word(w_yan,sizeof(w_yan),16,BLACK,628,49);
    lcd_draw_word(w_wu,sizeof(w_wu),16,BLACK,644,49);
    lcd_draw_word(w_nong,sizeof(w_nong),16,BLACK,660,49);
    lcd_draw_word(w_du,sizeof(w_du),16,BLACK,676,49);
    lcd_draw_word(w_maohao,sizeof(w_maohao),8,BLACK,692,49);

    // printf("value : %d\n", value);
    //在LCD的某个位置将value的值显示出来
    unsigned int thousand;
    unsigned int hundred;
    unsigned int decade;
    unsigned int units;

    thousand = value/1000%10;
    hundred = value/100%10;
    decade = value%100/10;
    units = value%10;

    int num[] = {thousand,hundred,decade,units};
    
    switch (thousand)
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 700,50);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 700,50);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 700,50);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 700,50);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 700,50);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 700,50);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 700,50);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 700,50);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 700,50);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 700,50);
        break;
    
    default:
        break;
    }

    switch (hundred)
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 708,50);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 708,50);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 708,50);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 708,50);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 708,50);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 708,50);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 708,50);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 708,50);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 708,50);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 708,50);
        break;
    
    default:
        break;
    }

    switch (decade)
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 716,50);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 716,50);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 716,50);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 716,50);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 716,50);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 716,50);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 716,50);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 716,50);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 716,50);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 716,50);
        break;
    
    default:
        break;
    }
    
    switch (units)
        {
        case 0:
            lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 724,50);
            break;
        case 1:
            lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 724,50);
            break;
        case 2:
            lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 724,50);
            break;
        case 3:
            lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 724,50);
            break;
        case 4:
            lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 724,50);
            break;
        case 5:
            lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 724,50);
            break;
        case 6:
            lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 724,50);
            break;
        case 7:
            lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 724,50);
            break;
        case 8:
            lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 724,50);
            break;
        case 9:
            lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 724,50);
            break;
        
        default:
            break;
        }
}

/**
 * @description: 向烟雾传感器发送数据并接收
 * @param {null} 
 * @return {null} 
 */
void* handle_smoke()
{
    unsigned char cmd[9]={0xFF,0x1,0x86,0,0,0,0,0,0x79};
    unsigned char buf[9]={0};
    int i,n;
    int fd = open(SMOKE_FILE, O_RDWR);

    while(1)
    {
        //向传感器发送命令
        n = write(fd, cmd, 9);
        //读取传感器返回的数据
        n = read(fd, buf, 9);

        // printf("have read %d bytes\n", n);
        // for(i=0;i<9;i++)
        //     printf("0x%x ",buf[i]);
        // printf("\n");

        value = buf[2]<<8 | buf[3];
        // printf("Smoke:%d\n",value);
        handleSmokeValues(value);
        // 延时
        sleep(3);
        lcd_draw_rect(700,50,32,16,WHITE);
    }
}

/**
 * @description: 处理GY39模块收到的数据
 * @param {unsigned int Lux} 光照强度数据
 * @return {null} 
 */
void handle_GY_Values(unsigned int T,unsigned int Hum){
    //温度十位
    unsigned int T_decade;
    //温度个位
    unsigned int T_units;
    //湿度十位
    unsigned int Hum_decade;
    //湿度个位
    unsigned int Hum_units;

    T_decade = T%100/10;
    T_units = T%10;

    Hum_decade = Hum%100/10;
    Hum_units = Hum%10;

    int num[] = {T_decade,T_units,Hum_decade,Hum_units};
    
    switch (num[0])
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 700,70);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 700,70);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 700,70);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 700,70);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 700,70);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 700,70);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 700,70);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 700,70);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 700,70);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 700,70);
        break;
    
    default:
        break;
    }

    switch (num[1])
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 708,70);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 708,70);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 708,70);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 708,70);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 708,70);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 708,70);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 708,70);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 708,70);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 708,70);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 708,70);
        break;
    
    default:
        break;
    }

    switch (num[2])
    {
    case 0:
        lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 700,85);
        break;
    case 1:
        lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 700,85);
        break;
    case 2:
        lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 700,85);
        break;
    case 3:
        lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 700,85);
        break;
    case 4:
        lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 700,85);
        break;
    case 5:
        lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 700,85);
        break;
    case 6:
        lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 700,85);
        break;
    case 7:
        lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 700,85);
        break;
    case 8:
        lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 700,85);
        break;
    case 9:
        lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 700,85);
        break;
    
    default:
        break;
    }
    
    switch (num[3])
        {
        case 0:
            lcd_draw_word(w_0, sizeof(w_0), 8, BLACK, 708,85);
            break;
        case 1:
            lcd_draw_word(w_1, sizeof(w_1), 8, BLACK, 708,85);
            break;
        case 2:
            lcd_draw_word(w_2, sizeof(w_2), 8, BLACK, 708,85);
            break;
        case 3:
            lcd_draw_word(w_3, sizeof(w_3), 8, BLACK, 708,85);
            break;
        case 4:
            lcd_draw_word(w_4, sizeof(w_4), 8, BLACK, 708,85);
            break;
        case 5:
            lcd_draw_word(w_5, sizeof(w_5), 8, BLACK, 708,85);
            break;
        case 6:
            lcd_draw_word(w_6, sizeof(w_6), 8, BLACK, 708,85);
            break;
        case 7:
            lcd_draw_word(w_7, sizeof(w_7), 8, BLACK, 708,85);
            break;
        case 8:
            lcd_draw_word(w_8, sizeof(w_8), 8, BLACK, 708,85);
            break;
        case 9:
            lcd_draw_word(w_9, sizeof(w_9), 8, BLACK, 708,85);
            break;
        
        default:
            break;
        }
}

/**
 * @description: 向GY39模块发送数据并接收
 * @param {null} 
 * @return {null} 
 */
void* handle_gy(){

    //文字显示
    //温度：
    lcd_draw_word(w_wen,sizeof(w_wen),16,BLACK,660,70);
    lcd_draw_word(w_du,sizeof(w_du),16,BLACK,676,70);
    lcd_draw_word(w_maohao,sizeof(w_maohao),8,BLACK,692,70);
	lcd_draw_word(w_dufuhao,sizeof(w_dufuhao),16,BLACK,716,70);
    //湿度：
    lcd_draw_word(w_shi,sizeof(w_wen),16,BLACK,660,85);
    lcd_draw_word(w_du,sizeof(w_du),16,BLACK,676,85);
    lcd_draw_word(w_maohao,sizeof(w_maohao),8,BLACK,692,85);
    lcd_draw_word(w_baifenhao,sizeof(w_baifenhao),8,BLACK,716,85);

    //发送命令
    unsigned char cmd[9] = {0xA5,0x52,0xF7};
    //接收数据
    unsigned char buf[15] = {0};
    int i,n;
    // //定义温度T  湿度Hum
    // unsigned int T,Hum;
    int fd = open(GY39_FILE,O_RDWR);
    while (1)
    {
        //向传感器发送命令
        n = write(fd, cmd, 9);
        //读取传感器返回的数据
        n = read(fd, buf, 9);
        // printf("have read %d bytes\n", n);
        // for(i=0;i<15;i++)
        //     printf("0x%x ",buf[i]);
        // printf("\n");
        
        unsigned int value,Lux;
        // value = (buf[4]<<24) | (buf[5]<<16) | (buf[6]<<8) | buf[7];
        // Lux = value/100;
        // printf("Lux: %d\n",Lux);
        // handle_GY_Values(Lux);
        T = buf[4]<<24 | buf[5];
        Hum = buf[10]<<8 | buf[11];
        // printf("Temperature:%d\n",T);
        // printf("Humidity:%d\n",Hum);
        handle_GY_Values(T,Hum);
        // 延时
        sleep(3);
        lcd_draw_rect(700,70,16,32,WHITE);
    }
}

#endif
