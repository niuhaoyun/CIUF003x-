#include <stdio.h>
#include <stdint.h>

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 1000; i++)
    {
        __NOP(); // Do nothing, just waste time
    }
}

int main(void)
{
    user_led_init();

    while (1)
    {
        user_led_toggle();
        delay_ms(500);
    }
}