/* ************************************************************************
 *       Filename:  dht11.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2012年06月03日 15时34分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <mach/hardware.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>	/*  copy_to_user, copy_from_user */
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-p.h> 

#include "dht11.h"

#define DEBUG	//open debug message
#ifdef DEBUG
#define PRINTK(fmt, arg...)		printk(KERN_WARNING fmt, ##arg)
#else
#define PRINTK(fmt, arg...)		printk(KERN_DEBUG fmt, ##arg)
#endif

#define DEVICE_NAME	  "dht11"



static char DHT11ReadByte(void)
{
	int time, i;
	unsigned char data;

	data = 0;

	for (i = 0; i < 8; i++)
	{
		time = 0;
		while ((!(gpio_get_value(S3C64XX_GPP(1)))))
		{
			time++;
			if (time > 40)
			{
				return -1;
			}
			udelay(5);
		}

		time = 0;
		while ((gpio_get_value(S3C64XX_GPP(1))))
		{
			time++;
			if (time > 100)
			{
				return -1;
			}
			udelay(5);
		}
	
		data >>= 1;
		if (time >= 8)
		{
			data |= 0x80;
		}
	}

	return ((char)data);
}

static ssize_t  DHT11Read(struct file *filp, char *buff, size_t count, loff_t *f_pos)
{
	int time, i;
	char data[5];
	char sum;

	if (count > 5 || buff == NULL)
	{
		return -1;
	}

	s3c_gpio_cfgpin(S3C64XX_GPP(1), S3C_GPIO_SFN(1));  //set output
	gpio_set_value(S3C64XX_GPP(1), 0);    
	msleep(18);
	gpio_set_value(S3C64XX_GPP(1), 1);    
	udelay(45);
	s3c_gpio_cfgpin(S3C64XX_GPP(1), S3C_GPIO_SFN(0));  //set input
	
	time = 0;
	while ((!(gpio_get_value(S3C64XX_GPP(1)))))
	{
		time++;
		if (time > 30)
		{
			return -1;
		}
		udelay(5);
	}

	time = 0;
	while ((gpio_get_value(S3C64XX_GPP(1))))
	{
		time++;
		if (time > 30)
		{
			return -2;
		}
		udelay(5);
	}

	for (i = 0; i < 5; i++)
	{
		data[i] = DHT11ReadByte();
		if (data[i] == -1)
		{	
			return -3;
		}
	}

	sum = 0;
	for (i = 0; i < 4; i++)
	{
		sum += data[i];
	}
	
	if (sum != data[i])
	{
		return -4;
	}

	s3c_gpio_cfgpin(S3C64XX_GPP(1), S3C_GPIO_SFN(1));  //set output
	gpio_set_value(S3C64XX_GPP(1), 1);    

	copy_to_user(buff, data, count);

	return count;
}


static struct file_operations dev_fops = 
{
	.owner =		THIS_MODULE,
	.read  =		DHT11Read,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init DHT11_Init(void)
{
	int res;

	res = misc_register(&misc);
	s3c_gpio_cfgpin(S3C64XX_GPP(1), S3C_GPIO_SFN(1));  //set output
	gpio_set_value(S3C64XX_GPP(1), 1);    
	PRINTK("DHT11 module register success.\n");

	return res;
}

static void __exit DHT11_exit(void)
{
	misc_deregister(&misc);
	PRINTK("DHT11 module deregister success.\n");
}

module_init(DHT11_Init);
module_exit(DHT11_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("shark");


