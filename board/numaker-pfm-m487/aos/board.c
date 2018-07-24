#include <aos/kernel.h>
#include <aos/aos.h>

#include "hal/soc/soc.h"
#include "board.h"

/* User-defined */
/* UART */
struct serial_s board_uart[] = {
	{ /* UART PORT 0, STDIO UART, Tx/Rx over Nu-Link's VCOM */
		.uart 		= UART_0,
		.pin_tx		= STDIO_UART_TX,
		.pin_rx		= STDIO_UART_RX,
		.pin_rts	= NC,
		.pin_cts	= NC
	},
	{ /* UART PORT 1, UART TX/RX in UDO IF */
		.uart 		= UART_1,
		.pin_tx		= PB_3,
		.pin_rx		= PB_2,
		.pin_rts	= NC,
		.pin_cts	= NC
	},
};
const int i32BoardMaxUartNum = sizeof( board_uart ) / sizeof( board_uart[0] );

/* I2C */
struct i2c_s board_i2c[] = {
	{ /* I2C PORT 0 */
		.i2c		= I2C_0,
		.pin_scl	= I2C_SCL,
		.pin_sda	= I2C_SDA
	},
	{ /* I2C PORT 1 */
		.i2c		= I2C_1,
		.pin_scl	= PB_1,
		.pin_sda	= PB_0
	},
};
const int i32BoardMaxI2CNum = sizeof( board_i2c ) / sizeof( board_i2c[0] );

/* Analog-In */
struct analogin_s board_analogin [] = 
{
	/* Analog-In port */
	{ .adc = ADC_0_6,	.pin = A0	},
	{ .adc = ADC_0_7,	.pin = A1	},
	{ .adc = ADC_0_8,	.pin = A2	},
	{ .adc = ADC_0_9,	.pin = A3	},
	{ .adc = ADC_0_0,	.pin = A4	},
	{ .adc = ADC_0_1,	.pin = A5	},
};
const int i32BoardMaxADCNum  = sizeof( board_analogin ) / sizeof( board_analogin[0] );
    
/* GPIO */
struct gpio_s board_gpio [] = 
{
	{ .pin = D0 },
	{ .pin = D1 },
	{ .pin = D2 },
	{ .pin = D3 },
	{ .pin = D4 },
	{ .pin = D5 },
	{ .pin = D6 },
	{ .pin = D7 },
	{ .pin = D8 },
	{ .pin = D9 },
	{ .pin = D10 },
	{ .pin = D11 },
	{ .pin = D12 },
	{ .pin = D13 },
	{ .pin = D14 },
	{ .pin = D15 },	
	{ .pin = SW2 },	
	{ .pin = SW3 },	
	{ .pin = LED_RED },	
	{ .pin = LED_YELLOW },
	{ .pin = LED_GREEN },
};
const int i32BoardMaxGPIONum  = sizeof( board_gpio ) / sizeof( board_gpio[0] );

/* PWM port-M & channel-N */
struct pwmout_s board_pwm [] = 
{
	{	.pwm = PWM_0_0,  .pin = PA_5	},
	{	.pwm = PWM_0_1,  .pin = PA_4	},
	{	.pwm = PWM_0_2,  .pin = PA_3	},
	{	.pwm = PWM_0_3,  .pin = PA_0	},
	{	.pwm = PWM_0_4,  .pin = PA_1	},
	{	.pwm = PWM_0_5,  .pin = PA_2	},

	{	.pwm = PWM_1_0,  .pin = PC_12	},
	{	.pwm = PWM_1_1,  .pin = PC_11	},
	{	.pwm = PWM_1_2,  .pin = PC_10	},
	{	.pwm = PWM_1_3,  .pin = PC_9	},
	
	//{	.pwm = PWM_0_3,  .pin = PE_4	}, //The same with PA_0.
	//{	.pwm = PWM_0_2,  .pin = PE_5	}, //The same with PA_3.
};
const int i32BoardMaxPWMNum  = sizeof( board_pwm ) / sizeof( board_pwm[0] );

/* SPI */
struct spi_s board_spi [] = 
{
	{	/* SPI0 */
		.spi 		= SPI_0,
		.pin_mosi 	= PA_0,
		.pin_miso	= PA_1,
		.pin_sclk	= PA_2,
		.pin_ssel	= PA_3,
	},
	{	/* SPI2 */
		.spi 		= SPI_2,
		.pin_mosi 	= PA_8,
		.pin_miso	= PA_9,
		.pin_sclk	= PA_10,
		.pin_ssel	= PA_11,
	},
};
const int i32BoardMaxSPINum  = sizeof( board_spi ) / sizeof( board_spi[0] );


/* QSPI */
struct qspi_s board_qspi [] = 
{
	{	
		.qspi 		= QSPI_0,
		.pin_d0 	= PA_0,		//QSPI0-MOSI0
		.pin_d1		= PA_1,		//QSPI0-MISO0
		.pin_d2		= PA_4,		//QSPI0-MOSI1
		.pin_d3		= PA_5,		//QSPI0-MISO1
		.pin_sclk	= PA_2,
		.pin_ssel	= PA_3,
	},
};
const int i32BoardMaxQSPINum  = sizeof( board_qspi ) / sizeof( board_qspi[0] );

// FIXME
gpio_dev_t board_gpio_table[] = 
{
    {0,  OUTPUT_PUSH_PULL, NULL},//0
    {1,  OUTPUT_PUSH_PULL, NULL},      
    {2,  OUTPUT_PUSH_PULL, NULL},     
    {3,  OUTPUT_PUSH_PULL, NULL},     
    {4,  OUTPUT_PUSH_PULL, NULL},       
    {5,  OUTPUT_PUSH_PULL, NULL},       
    {6,  OUTPUT_PUSH_PULL, NULL},        
    {7,  OUTPUT_PUSH_PULL, NULL},       
    {8,  OUTPUT_PUSH_PULL, NULL},        
    {9,  OUTPUT_PUSH_PULL, NULL},//9          
    {10, OUTPUT_PUSH_PULL, NULL},          
    {11, OUTPUT_PUSH_PULL, NULL},            
    {12, OUTPUT_PUSH_PULL, NULL},      
    {13, OUTPUT_PUSH_PULL, NULL},
    {14, OUTPUT_PUSH_PULL, NULL},
    {15, OUTPUT_PUSH_PULL, NULL},
    {16, IRQ_MODE, 				 NULL},//16
    {17, IRQ_MODE, 				 NULL},
    {18, OUTPUT_PUSH_PULL, NULL},
    {19, OUTPUT_PUSH_PULL, NULL},
    {20, OUTPUT_PUSH_PULL, NULL},
};

/* Logic partition on flash devices */
hal_logic_partition_t hal_partitions[HAL_PARTITION_MAX];

/* Board partition */
static void board_partition_init()
{
    hal_partitions[HAL_PARTITION_APPLICATION].partition_owner            = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_APPLICATION].partition_description      = "Application";
    hal_partitions[HAL_PARTITION_APPLICATION].partition_start_addr       = FMC_APROM_BASE;	//0x80000, 512k
    hal_partitions[HAL_PARTITION_APPLICATION].partition_length           = 0x20000;    			//128k bytes
    hal_partitions[HAL_PARTITION_APPLICATION].partition_options          = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_PARAMETER_1].partition_owner            = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_PARAMETER_1].partition_description      = "PARAMETER1";
    hal_partitions[HAL_PARTITION_PARAMETER_1].partition_start_addr       = hal_partitions[HAL_PARTITION_APPLICATION].partition_start_addr+hal_partitions[HAL_PARTITION_APPLICATION].partition_length;
    hal_partitions[HAL_PARTITION_PARAMETER_1].partition_length           = FMC_FLASH_PAGE_SIZE; // 4k bytes
    hal_partitions[HAL_PARTITION_PARAMETER_1].partition_options          = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_PARAMETER_2].partition_owner            = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_PARAMETER_2].partition_description      = "PARAMETER2";
    hal_partitions[HAL_PARTITION_PARAMETER_2].partition_start_addr       = hal_partitions[HAL_PARTITION_PARAMETER_1].partition_start_addr + hal_partitions[HAL_PARTITION_PARAMETER_1].partition_length;
    hal_partitions[HAL_PARTITION_PARAMETER_2].partition_length           = FMC_FLASH_PAGE_SIZE*2; //8k bytes
    hal_partitions[HAL_PARTITION_PARAMETER_2].partition_options          = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_PARAMETER_3].partition_owner            = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_PARAMETER_3].partition_description      = "PARAMETER3";
    hal_partitions[HAL_PARTITION_PARAMETER_3].partition_start_addr       = hal_partitions[HAL_PARTITION_PARAMETER_2].partition_start_addr+hal_partitions[HAL_PARTITION_PARAMETER_2].partition_length;
    hal_partitions[HAL_PARTITION_PARAMETER_3].partition_length           = FMC_FLASH_PAGE_SIZE*2; //8k bytes
    hal_partitions[HAL_PARTITION_PARAMETER_3].partition_options          = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_PARAMETER_4].partition_owner            = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_PARAMETER_4].partition_description      = "PARAMETER4";
    hal_partitions[HAL_PARTITION_PARAMETER_4].partition_start_addr       = hal_partitions[HAL_PARTITION_PARAMETER_3].partition_start_addr+hal_partitions[HAL_PARTITION_PARAMETER_3].partition_length;
    hal_partitions[HAL_PARTITION_PARAMETER_4].partition_length           = FMC_FLASH_PAGE_SIZE*2; //8k bytes
    hal_partitions[HAL_PARTITION_PARAMETER_4].partition_options          = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_CUSTOM_1].partition_owner               = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_CUSTOM_1].partition_description         = "CUSTOM1";
    hal_partitions[HAL_PARTITION_CUSTOM_1].partition_start_addr          = hal_partitions[HAL_PARTITION_PARAMETER_4].partition_start_addr+hal_partitions[HAL_PARTITION_PARAMETER_4].partition_length;
    hal_partitions[HAL_PARTITION_CUSTOM_1].partition_length              = FMC_FLASH_PAGE_SIZE*16; //40k bytes
    hal_partitions[HAL_PARTITION_CUSTOM_1].partition_options             = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;

    hal_partitions[HAL_PARTITION_CUSTOM_2].partition_owner               = HAL_FLASH_EMBEDDED;
    hal_partitions[HAL_PARTITION_CUSTOM_2].partition_description         = "CUSTOM2";
    hal_partitions[HAL_PARTITION_CUSTOM_2].partition_start_addr          = hal_partitions[HAL_PARTITION_CUSTOM_1].partition_start_addr+hal_partitions[HAL_PARTITION_CUSTOM_1].partition_length;
    hal_partitions[HAL_PARTITION_CUSTOM_2].partition_length              = FMC_FLASH_PAGE_SIZE*16; //40k bytes
    hal_partitions[HAL_PARTITION_CUSTOM_2].partition_options             = PAR_OPT_READ_EN | PAR_OPT_WRITE_EN;
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

void board_init(void)
{
		board_gpio_init();
		board_button_init();
		board_leds_init();
	
    board_partition_init();
    board_cli_init();
}
