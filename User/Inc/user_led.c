#include "user_led.h"

void user_led_init(void)
{
    std_gpio_init_t gpio_init_struct;

    if (LED_PORT == GPIOA)
    {
        std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA);
    }
    else if (LED_PORT == GPIOB)
    {
        std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB);
    }
    else if (LED_PORT == GPIOC)
    {
        std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOC);
    }

    gpio_init_struct.pin = LED_PIN;
    gpio_init_struct.mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.pull = GPIO_NOPULL;
    gpio_init_struct.output_type = GPIO_OUTPUT_PUSHPULL;
    gpio_init_struct.alternate = 0U;

    std_gpio_init(LED_PORT, &gpio_init_struct);
    std_gpio_reset_pin(LED_PORT, LED_PIN);
}

void user_led_toggle(void)
{
    std_gpio_toggle_pin(LED_PORT, LED_PIN);
}
