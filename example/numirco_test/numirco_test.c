/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <aos/aos.h>

#include <hal/hal.h>
uint8_t pngbuf [ 32 ];

random_dev_t 	g_sRngDev;
wdg_dev_t 		g_sWdtDev;
rtc_dev_t 		g_sRtcDev;
rtc_time_t		g_sRtcTimeData;

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

static void testcase_run(){
		rng_test();
		wdt_test();
		rtc_test();
}

static void testcase_init() {

	//RNG
	memset((void*)&g_sRngDev, 0, sizeof(g_sRngDev));
	
	//WDT
	memset((void*)&g_sWdtDev, 0, sizeof(g_sWdtDev));
	g_sWdtDev.config.timeout=3;
	hal_wdg_init(&g_sWdtDev);
	
	//RTC
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

static void app_delayed_action(void *arg)
{
	LOG("helloworld %s:%d %s\r\n", __func__, __LINE__, aos_task_name());
		
	testcase_run();

	aos_post_delayed_action(100, app_delayed_action, NULL);
}

int application_start(int argc, char *argv[])
{
	LOG("application started.");

	testcase_init();
  
	aos_post_delayed_action(100, app_delayed_action, NULL);
	
  aos_loop_run();	
  
	return 0;
}

