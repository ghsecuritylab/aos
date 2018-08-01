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
#define DEF_TEST_DO		0
#define DEF_TEST_BTN	1
#define DEF_TEST_ADC	0
#define DEF_TEST_PWM	0
#define DEF_TEST_LED	0
#define DEF_TEST_SD		1

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

pwm_dev_t			g_sPwmDev[] = 
{
    {0,  {0.5f,10}, NULL},
    {1,  {0.5f,10}, NULL},
    {2,  {0.5f,10}, NULL},
    {3,  {0.5f,10}, NULL},
    {4,  {0.5f,10}, NULL},
    {5,  {0.5f,10}, NULL},
    {6,  {0.5f,10}, NULL},
    {7,  {0.5f,10}, NULL},
    {8,  {0.5f,10}, NULL},
    {9,  {0.5f,10}, NULL},
    {10,  {0.5f,10}, NULL},
    {11,  {0.5f,10}, NULL},		
};

sd_dev_t			g_sSdDev[] = 
{
    {0,  {0, 0}, NULL},//0
};

static int g_interval=100;		//ms

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

static pwm_test (int on) 
{
	if (DEF_TEST_PWM)
	{
		int i=0;
		for (i = 0; i < i32BoardMaxPWMNum; ++i)
		{
			g_sPwmDev[i].config.freq=g_interval;
			if ( on )
				hal_pwm_start(&g_sPwmDev[i]);			
			else
				hal_pwm_stop(&g_sPwmDev[i]);
		}
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
void key_process(input_event_t *eventinfo, void *priv_data)
{
    if (eventinfo->type != EV_KEY) {
        return;
    }

    LOG("[%d %d %d %d]\n" , eventinfo->time, eventinfo->type, eventinfo->code, eventinfo->value);
    if (eventinfo->code == 16) {
				if (DEF_TEST_PWM)
					pwm_test(0);
				if (g_interval>0)
					g_interval -= 50;
        if (eventinfo->value == VALUE_KEY_CLICK) {
            LOG("SW2 press do_active\n");
        } else if (eventinfo->value == VALUE_KEY_LTCLICK) {
            LOG("SW2 press do_reset\n");
        }
    } else if (eventinfo->code == 17) {
				if (DEF_TEST_PWM)
					pwm_test(1);
				g_interval += 50;
        if (eventinfo->value == VALUE_KEY_CLICK) {
            LOG("SW3 press do_active\n");
        } else if (eventinfo->value == VALUE_KEY_LTCLICK) {
            LOG("SW3 press do_reset\n");
        }		
		}
		
}

static uint64_t   awss_time = 0;

static void key_poll_func(void *arg)
{
    uint32_t level;
    uint64_t diff;
		gpio_dev_t* psgpio;
	
    hal_gpio_input_get((gpio_dev_t*)arg, &level);
		psgpio = (gpio_dev_t*)arg;
	
    if (level == 0) { // still pressed
        aos_post_delayed_action(10, key_poll_func, arg);
    } else {		// released
        diff = aos_now_ms() - awss_time;
        if (diff > 5000) { 				/*long long press, 5 seconds */
            awss_time = 0;
            aos_post_event(EV_KEY, psgpio->port, VALUE_KEY_LLTCLICK);
        } else if (diff > 2000) { /* long press, 2 seconds */
            awss_time = 0;
            aos_post_event(EV_KEY, psgpio->port, VALUE_KEY_LTCLICK);
        } else if (diff > 40) { 	/* short press, 40 miliseconds */
            awss_time = 0;
            aos_post_event(EV_KEY, psgpio->port, VALUE_KEY_CLICK);
        } else {
            aos_post_delayed_action(10, key_poll_func, arg);
        }
    }
}

static void key_proc_work(void *arg)
{
    aos_schedule_call(key_poll_func, arg);
}

static void handle_awss_key(void *arg)
{
    uint32_t gpio_value;

    hal_gpio_input_get((gpio_dev_t*)arg, &gpio_value);
    if (gpio_value == 0 && awss_time == 0) {
        awss_time = aos_now_ms();
        aos_loop_schedule_work(0, key_proc_work, arg, NULL, NULL);
    }
}

static void board_gpio_init(void)
{
		int i;
    for (i = 0; i < i32BoardMaxGPIONum; ++i)
        hal_gpio_init(&board_gpio_table[i]);
}

static void board_button_init(void)
{		
		//SW2
		hal_gpio_enable_irq(&board_gpio_table[16], IRQ_TRIGGER_FALLING_EDGE, handle_awss_key, (void*)&board_gpio_table[16]);		
		
		//SW3
		hal_gpio_enable_irq(&board_gpio_table[17], IRQ_TRIGGER_FALLING_EDGE, handle_awss_key, (void*)&board_gpio_table[17]);		
}

static void board_leds_init(void)
{
		//LED_RED
		hal_gpio_output_low(&board_gpio_table[18]);
		//LED_YELLOW
		hal_gpio_output_low(&board_gpio_table[19]);
		//LED_GREEN
		hal_gpio_output_low(&board_gpio_table[20]);
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

	if (DEF_TEST_BTN || DEF_TEST_LED )
			board_gpio_init();

	// SW2/SW3
	if (DEF_TEST_BTN)
	{
		board_button_init();
		aos_register_event_filter(EV_KEY, key_process, NULL);
	}
	
	if (DEF_TEST_LED)
	{		
		board_leds_init();
	}
	
	// A0~A5
	if (DEF_TEST_ADC)
	{
		int i=0;
		for (i = 0; i < i32BoardMaxADCNum; ++i)
			hal_adc_init(&g_sAdcDev[i]);		
	}	
	
	if (DEF_TEST_PWM)
	{
		int i=0;
		for (i = 0; i < i32BoardMaxPWMNum; ++i)
		{
			hal_pwm_init(&g_sPwmDev[i]);
			hal_pwm_start(&g_sPwmDev[i]);			
		}
	}
	
	if ( DEF_TEST_SD )
	{
		if ( !hal_sd_init(&g_sSdDev[0]) )
		{
			hal_sd_info_t info;
			if ( hal_sd_info_get(&g_sSdDev[0], &info) )
				printf("SD0 get info failure.\r\n");
			else
				printf("SD card sector num=%d, size=%d.\r\n", info.blk_nums, info.blk_size);			
		}
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

