OLED_ENABLE = yes
OLED_DRIVER = ssd1306
SERIAL_DRIVER = vendor
AUDIO_DRIVER = pwm_hardware
KEY_OVERRIDE_ENABLE = no

SRC += features/status.c
SRC += features/oled.c
SRC += features/oneshot.c
SRC += features/swapper.c
SRC += features/select_word.c
SRC += features/casemodes.c
SRC += features/num_word.c
