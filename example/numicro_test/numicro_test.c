/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <aos/aos.h>
#include <hal/hal.h>

#include "board.h"

#define DEF_TEST_RNG 	0
#define DEF_TEST_WDT 	0
#define DEF_TEST_RTC 	0 
#define DEF_TEST_BTN 	0
#define DEF_TEST_DO		1
#define DEF_TEST_ADC	1

uint8_t pngbuf [ 32 ];
random_dev_t 	g_sRngDev;
wdg_dev_t 		g_sWdtDev;
rtc_dev_t 		g_sRtcDev;
rtc_time_t		g_sRtcTimeData;
adc_dev_t			g_sAdcDev[] = 
{
    {0,  0, NULL},//0
    {1,  0, NULL},  
    {2,  0, NULL},     
    {3,  0, NULL},     
    {4,  0, NULL},       
    {5,  0, NULL},       
};

static void print_pngbuf ( uint8_t* pbuf, int length )
{
	int i=0;  
	printf("\r\n[%s](%d) ", __func__, length );
	for (i=0;i<length;i++)
    printf("%02X ", pbuf[i] );
  printf("\r\n");		

}

static void rng_test (void) 
{
	if ( !hal_random_num_read ( g_sRngDev, (void *)pngbuf, sizeof(pngbuf) ) )
		print_pngbuf(pngbuf, sizeof(pngbuf) );

	if ( !hal_random_num_read ( g_sRngDev, (void *)pngbuf, 1) )
		print_pngbuf(pngbuf, 1 );

	if ( !hal_random_num_read ( g_sRngDev, (void *)pngbuf, 0) )
		print_pngbuf(pngbuf, 0 );	
}

static wdt_test () 
{
		if ( aos_now_ms() < 10000 )
				hal_wdg_reload(&g_sWdtDev);
}

static rtc_test () 
{
	hal_rtc_get_time(&g_sRtcDev, &g_sRtcTimeData);
	printf("RTC: %02d-%02d-%02d(%d) %02d:%02d:%02d \r\n",  \
															g_sRtcTimeData.year, \
															g_sRtcTimeData.month, \
															g_sRtcTimeData.date, \
															g_sRtcTimeData.weekday, \
															g_sRtcTimeData.hr, \
															g_sRtcTimeData.min, \
															g_sRtcTimeData.sec );
	
}

//D0~D14
extern gpio_dev_t board_gpio_table[];
static digitalout_test()
{
	int i;
	static int toggle=0;
	
	for (i = 0; i < i32BoardMaxGPIONum; ++i)
	{
		if ( board_gpio_table[i].config >= OUTPUT_PUSH_PULL )
			hal_gpio_output_toggle(&board_gpio_table[i]);
	}

	#if 0
	for (i = 0; i < i32BoardMaxGPIONum; ++i)
	{
		if(toggle)
			hal_gpio_output_high(&board_gpio_table[i]);
		else
			hal_gpio_output_low(&board_gpio_table[i]);
	}
	toggle = ~toggle;
	#endif
}	

static adc_test () 
{
	if (DEF_TEST_ADC)
	{
		int i=0;
		uint16_t u16data;
		printf("\r\n");		
		for (i = 0; i < i32BoardMaxADCNum; ++i)
		{
			hal_adc_value_get(&g_sAdcDev[i], (void*)&u16data, 0);
			printf("ADC Channel [%d] -> %d\r\n", i, u16data );
		}
		printf("\r\n");		
	}	
}


static void testcase_run(){

	if (DEF_TEST_RNG)
		rng_test();
	
	if (DEF_TEST_WDT)
		wdt_test();

	if (DEF_TEST_RTC)
		rtc_test();

	if (DEF_TEST_DO)
		digitalout_test();

	if (DEF_TEST_ADC)
		adc_test();
	
}

static int g_interval=100;

void key_process(input_event_t *eventinfo, void *priv_data)
{
    if (eventinfo->type != EV_KEY) {
        return;
    }

    LOG("[%d %d %d %d]\n" , eventinfo->time, eventinfo->type, eventinfo->code, eventinfo->value);
    if (eventinfo->code == 16) {
				if (g_interval>0)
					g_interval -= 50;
        if (eventinfo->value == VALUE_KEY_CLICK) {
            LOG("SW2 press do_active\n");
        } else if (eventinfo->value == VALUE_KEY_LTCLICK) {
            LOG("SW2 press do_reset\n");
        }
    } else if (eventinfo->code == 17) {
				g_interval += 50;
        if (eventinfo->value == VALUE_KEY_CLICK) {
            LOG("SW3 press do_active\n");
        } else if (eventinfo->value == VALUE_KEY_LTCLICK) {
            LOG("SW3 press do_reset\n");
        }		
		}
		
}

static void testcase_init() {

	//RNG
	if (DEF_TEST_RNG)
		memset((void*)&g_sRngDev, 0, sizeof(g_sRngDev));
	
	//WDT
	if (DEF_TEST_WDT)
	{
		memset((void*)&g_sWdtDev, 0, sizeof(g_sWdtDev));
		g_sWdtDev.config.timeout=3;
		hal_wdg_init(&g_sWdtDev);
	}
	
	//RTC
	if (DEF_TEST_RTC)
	{
		memset((void*)&g_sRtcDev, 0, sizeof(g_sRtcDev));
		hal_rtc_init(&g_sRtcDev);
		memset ( &g_sRtcTimeData, 0, sizeof(g_sRtcTimeData) );
		//2018-07-16 16:25:00
		g_sRtcTimeData.year 		= 18;
		g_sRtcTimeData.month 		=	7;
		g_sRtcTimeData.date			= 16;
		g_sRtcTimeData.weekday	= 1;
		g_sRtcTimeData.hr				= 16;
		g_sRtcTimeData.min			= 25;
		g_sRtcTimeData.sec			= 0;	
		g_sRtcDev.config.format = HAL_RTC_FORMAT_DEC;
		hal_rtc_set_time(&g_sRtcDev, &g_sRtcTimeData);
	}
	
	// SW2/SW3
	if (DEF_TEST_DO)
			aos_register_event_filter(EV_KEY, key_process, NULL);

	if (DEF_TEST_ADC)
	{
		int i=0;
		for (i = 0; i < i32BoardMaxADCNum; ++i)
			hal_adc_init(&g_sAdcDev[i]);		
	}	
}

static void app_delayed_action(void *arg)
{
	//LOG("helloworld %s:%d %s\r\n", __func__, __LINE__, aos_task_name());
		
	testcase_run();

	aos_post_delayed_action(g_interval, app_delayed_action, NULL);
}

int application_start(int argc, char *argv[])
{
	LOG("application started.");

	testcase_init();
  
	aos_post_delayed_action(100, app_delayed_action, NULL);
	
  aos_loop_run();	
  
	return 0;
}

