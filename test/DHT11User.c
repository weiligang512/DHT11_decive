/* ************************************************************************
 *       Filename:  DHT11.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2012年05月24日 22时10分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "DHT11User.h"

static int fd;

void DHT11Init(void)
{
	fd = open(DHT11DEV, O_RDWR);
	if (fd < 0)
	{
		fprintf(stderr, "Open DHT11 device failed\n");

		exit(0);
	}
	else
	{
		printf("Open DHT11 device success. fd=%d\n", fd);
	}
}

int DHT11Read(char *Data)
{
	int cnt;

	cnt = read(fd, Data, 5);
	printf("cnt = %d\n", cnt);

	if (cnt < 5)
	{
		return -1;
	}

	return cnt;
}

void DHT11Close(void)
{
	close(fd);
}


int main(int argc, char *argv[])
{
	char DHdata[5];
	int res, i;

	DHT11Init();

	while (1)
	{
		memset(DHdata, 0, sizeof(DHdata));
		res = DHT11Read(DHdata);

		printf("res = %d\n", res);

		for (i = 0; i < 5; i++)
		{
			printf("DHdata[%d] = %d\n", i, DHdata[i]);
		}
		
		sleep(2);
	}
	
	DHT11Close();

	return 0;
}







