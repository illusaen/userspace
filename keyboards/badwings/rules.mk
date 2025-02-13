# SPI_DRIVER_REQUIRED = yes 
# CUSTOM_MATRIX = lite

POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
POINTING_DEVICE_ENABLE  = yes
LTO_ENABLE = yes
CONSOLE_ENABLE = no
EXTRAFLAGS += -flto

SRC += features/status.c
SRC += features/oneshot.c
SRC += features/swapper.c
SRC += features/select_word.c
SRC += features/casemodes.c
SRC += features/num_word.c