/*
 * @Author: SingleBiu
 * @Date: 2022-01-19 20:36:20
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-01-22 10:54:11
 * @Description: A dht22 driver demo application
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#define GEC6818_GET_DHTDATA _IOR('K', 0, unsigned int) //注册宏

int main(void)
{
	int ret, cnt_yes = 0, cnt_err = 0;
	// unsigned char data[2];
	int data[3];
	int ultrasonic_fd = open("/dev/dht22_dev", O_RDWR);
	if (ultrasonic_fd < 0)
	{
		perror("open dht22_dev driver");
		return -1;
	}
	while (1)
	{
		ret = ioctl(ultrasonic_fd, GEC6818_GET_DHTDATA, &data[0]);
		if (ret != 0)
		{
			cnt_err++;
			perror("GEC6818_GET_DHTDATA error");
		}
		else
		{
			cnt_yes++;
			printf("app:  Hum= %d  Temprature=%d.%d  err:%d  correct:%d\n", data[0], data[1], data[2], cnt_err, cnt_yes);
		}
		sleep(2);
	}
	close(ultrasonic_fd);

	return 0;
}