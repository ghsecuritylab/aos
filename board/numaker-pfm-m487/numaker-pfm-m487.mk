NAME := numaker-pfm-m487


$(NAME)_TYPE         := kernel
MODULE               := 1062
HOST_ARCH            := Cortex-M4
HOST_MCU_FAMILY      := numicro_m48x
SUPPORT_BINS         := no
ENABLE_VFP           := 1
#HOST_MCU_NAME        := M487

$(NAME)_SOURCES += \
		   aos/board.c \
                   aos/soc_init.c \
                   aos/board_cli.c
                   
$(NAME)_SOURCES += startup_M480.c 

GLOBAL_INCLUDES += . \
                   hal/ \
                   aos/ \
                   inc/
				   
GLOBAL_CFLAGS += -DNUMICRO_M487

GLOBAL_DEFINES += STDIO_UART=0
GLOBAL_DEFINES += STDIO_UART_BUADRATE=115200
GLOBAL_DEFINES += CONFIG_AOS_CLI_BOARD

#$(NAME)_COMPONENTS += sensor
#GLOBAL_DEFINES += AOS_SENSOR_ACC_MIR3_DA217
#GLOBAL_DEFINES += AOS_SENSOR_ALS_LITEON_LTR553
#GLOBAL_DEFINES += AOS_SENSOR_PS_LITEON_LTR553
#GLOBAL_DEFINES += AOS_SENSOR_ACC_SUPPORT_STEP
#GLOBAL_DEFINES += IOTX_WITHOUT_TLS MQTT_DIRECT

sal ?= 1
no_tls ?= 1
ifeq (1,$(sal))
$(NAME)_COMPONENTS += sal
module ?= wifi.bk7231
#module ?= wifi.esp8266 WTF, build failre
else
GLOBAL_DEFINES += CONFIG_NO_TCPIP
endif

ifeq ($(COMPILER),armcc)
$(NAME)_LINK_FILES := startup_M480.o
endif

CONFIG_SYSINFO_PRODUCT_MODEL := ALI_AOS_NUMAKER_M487
CONFIG_SYSINFO_DEVICE_NAME := $(NAME)

GLOBAL_CFLAGS += -DSYSINFO_OS_VERSION=\"$(CONFIG_SYSINFO_OS_VERSION)\"
GLOBAL_CFLAGS += -DSYSINFO_PRODUCT_MODEL=\"$(CONFIG_SYSINFO_PRODUCT_MODEL)\"
GLOBAL_CFLAGS += -DSYSINFO_DEVICE_NAME=\"$(CONFIG_SYSINFO_DEVICE_NAME)\"
