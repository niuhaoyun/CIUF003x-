#ifndef __USER_LED_H__
#define __USER_LED_H__

#include "ciu32f003_std.h"

#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_1

void user_led_init(void);
void user_led_toggle(void);

#endif
