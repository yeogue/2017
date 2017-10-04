#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/delay.h>

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/ioport.h>

#include <asm/io.h>
#include <asm/delay.h>
#include <asm/irq.h>

#include <mach/map.h>
#include <mach/gpio.h>

#include <asm/gpio.h>
#include <mach/regs-gpio.h>

#include <plat/gpio-cfg.h>

#include <linux/slab.h>

#include <mach/hardware.h>
#include <mach/irqs.h>

// Device Address
#define LED     0x0A
#define TACT 0x0F
#define DELAY 100

#define ADDR_PIN_L_0(x)           EXYNOS4212_GPM0(x+1)
#define ADDR_PIN_L_1(x)           EXYNOS4212_GPM1(x)

#define ADDR_PIN_H_1(x)           EXYNOS4212_GPM1(x+1)

#define DATA_PIN_2(x)             EXYNOS4212_GPM2(x)
#define DATA_PIN_3(x)             EXYNOS4212_GPM3(x)
#define DATA_PIN_4(x)             EXYNOS4212_GPM4(x)
#define DATA_PIN_0(x)             EXYNOS4212_GPM0(x)

static void gpio_init(void){
	int i;

	//fpga data gpio init - gpm2_0~2
        for(i=0; i<3; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
        //fpga data gpio init - gpm0_0
	for(i=0; i<1; i++){
                gpio_request(DATA_PIN_0(i), "GPM0_0");
                s3c_gpio_cfgpin(DATA_PIN_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_0(i), 1);
        }
        //fpga data gpio init - gpm2_3~4
        for(i=3; i<5; i++){
                gpio_request(DATA_PIN_2(i), "GPM2_0");
                s3c_gpio_cfgpin(DATA_PIN_2(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_2(i), 1);
        }
        //fpga data gpio init - gpm3_0~7
        for(i=0; i<2; i++){
                gpio_request(DATA_PIN_3(i), "GPM3_0");
                s3c_gpio_cfgpin(DATA_PIN_3(i), S3C_GPIO_SFN(1));
                gpio_direction_output(DATA_PIN_3(i), 1);
        }
        //fpga address gpio init - gpm0_1~7 <= (0~6+1) //add 1
        for(i=0; i<7; i++){
                gpio_request(ADDR_PIN_L_0(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_0(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_0(i), 0);
                gpio_set_value(ADDR_PIN_L_0(i), 0);
        }
        //fpga address gpio init - gpm1_0~0
        for(i=0; i<1; i++){
                gpio_request(ADDR_PIN_L_1(i), "GPM0_0");
                s3c_gpio_cfgpin(ADDR_PIN_L_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_L_1(i), 0);
                gpio_set_value(ADDR_PIN_L_1(i), 0);
        }
        //fpga address gpio init - gpm1_1~6
        for(i=0; i<6; i++){
                gpio_request(ADDR_PIN_H_1(i), "GPM1_0");
                s3c_gpio_cfgpin(ADDR_PIN_H_1(i), S3C_GPIO_SFN(1));
                gpio_direction_output(ADDR_PIN_H_1(i), 0);
                gpio_set_value(ADDR_PIN_H_1(i), 0);
        }
}

static unsigned int sw_data = 0;

static unsigned int TACTSW_DATA(void)
{
	int i;
	
	for(i=0; i<3; i++){
                sw_data |= ((gpio_get_value(DATA_PIN_2(i)))<<i);
        }
                sw_data |= (gpio_get_value(DATA_PIN_0(0)))<<3;
                sw_data |= ((gpio_get_value(DATA_PIN_2(3)))<<4);
                sw_data |= ((gpio_get_value(DATA_PIN_2(4)))<<5);
                sw_data |= ((gpio_get_value(DATA_PIN_3(0)))<<6);
                sw_data |= ((gpio_get_value(DATA_PIN_3(1)))<<7);
	return sw_data;
}

static void LED_DATA(unsigned char val)
{
 	if(val & (1<<0))    gpio_set_value(DATA_PIN_2(0), 1);
        else                gpio_set_value(DATA_PIN_2(0), 0);
        if(val & (1<<1))    gpio_set_value(DATA_PIN_2(1), 1);
        else                gpio_set_value(DATA_PIN_2(1), 0);
        if(val & (1<<2))    gpio_set_value(DATA_PIN_2(2), 1);
        else                gpio_set_value(DATA_PIN_2(2), 0);

        if(val & (1<<3))    gpio_set_value(DATA_PIN_0(0), 1);
        else                gpio_set_value(DATA_PIN_0(0), 0);

        if(val & (1<<4))    gpio_set_value(DATA_PIN_2(3), 1);
        else                gpio_set_value(DATA_PIN_2(3), 0);
        if(val & (1<<5))    gpio_set_value(DATA_PIN_2(4), 1);
        else                gpio_set_value(DATA_PIN_2(4), 0);

        if(val & (1<<6))    gpio_set_value(DATA_PIN_3(0), 1);
        else                gpio_set_value(DATA_PIN_3(0), 0);
        if(val & (1<<7))    gpio_set_value(DATA_PIN_3(1), 1);
        else                gpio_set_value(DATA_PIN_3(1), 0);

}
static void write_addr_l(unsigned char val){
	int i;

        for(i=0; i<7; i++){
                if(val & (1<<i)){
                        gpio_set_value(ADDR_PIN_L_0(i), 1);
                }
                else{
                        gpio_set_value(ADDR_PIN_L_0(i), 0);
                }
        }
        if(val & (1 << 7))
                gpio_set_value(ADDR_PIN_L_1(0), 1);
        else
                gpio_set_value(ADDR_PIN_L_1(0), 0);

}

static int __init LED_probe(struct platform_device *pdev)
{
	char data;
	int i;
	unsigned int password = 7894;
	unsigned int input = 0;
	unsigned int compare = 0;

	gpio_init();

	write_addr_l(TACT);

	while(password != compare)
	{
		TACTSW_DATA();
		msleep(100);

		if(sw_data != 0)
		{
			if(sw_data == 10)
			{
				compare = input; // try enter
				sw_data = 0;
				continue;
			}
			if(sw_data == 12)
			{
				input = 0; // reset input
				sw_data = 0;
				continue;
			}
	
			if(sw_data == 11)
			{
				sw_data = 0;
			}
			input *= 10;
			input += sw_data;
			printk("%d\n", input);
			sw_data = 0;
		}
	}

	printk("LED probe!!\n");
	write_addr_l(LED);

	for(i = 0; i < 4; i++)
	{
		data = 0xf0;
		LED_DATA(data);
		msleep(DELAY);
		data = 0x0f;
		LED_DATA(data);
		msleep(DELAY);
	}

	for(i = 0; i < 2; i++)
	{
		data = 0x7e;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xbd;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xdb;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xe7;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xdb;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xbd;
		LED_DATA(data);
		msleep(DELAY);
	}
	data = 0x7e;
	LED_DATA(data);
	msleep(DELAY);

	for(i = 0; i < 8; i++)
	{
		data = 0x00;
		LED_DATA(data);
		msleep(DELAY);
		data = 0xff;
		LED_DATA(data);
		msleep(DELAY);
	}

	return 0;
}


static int LED_remove(struct platform_device *pdev)
{
	printk("LED remove!!\n");
	return 0;
}

static int LED_suspend(struct platform_device *dev, pm_message_t state)
{
	printk("LED_suspend!!\n");
	return 0;
}

static int LED_resume(struct platform_device *pdev)
{
	printk("LED_resume!!\n");
	return 0;
}

static struct platform_driver LED_driver = {
       .probe          = LED_probe,
       .remove         = LED_remove,
       .suspend        = LED_suspend,
       .resume         = LED_resume,
       .driver		= {
		.owner	= THIS_MODULE,
		.name	= "LED",
	},
};

int __init LED_init(void)
{
	return platform_driver_register(&LED_driver);
}

void __exit LED_exit(void)
{
	platform_driver_unregister(&LED_driver);
}

module_init(LED_init);
module_exit(LED_exit);

MODULE_LICENSE("GPL");
