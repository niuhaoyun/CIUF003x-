#include "ciu32f003_std_gpio.h"

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_0


void user_led_init(void);
void user_led_toggle(void);
