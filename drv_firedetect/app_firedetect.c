#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#define GEC6818_GET_FIREDATA _IOR('F', 0, unsigned int) //注册宏

int main(void)
{
	int ret;  
	// unsigned char data[2];
	int data;
	int fire_fd = open("/dev/fire_detect_dev", O_RDWR);
	if (fire_fd < 0)
	{
		perror("open firedetect_dev driver");
		return -1;
	}
	while (1)
	{
		ret = ioctl(fire_fd, GEC6818_GET_FIREDATA, &data);
		if (ret != 0)
		{
			perror("GEC6818_GET_FIREDATA error");
		}
		else
		{
			printf("app: Fire_detect:%d\n", data);
            data = 0;
		}
		sleep(2);
	}
	close(fire_fd);

	return 0;
}