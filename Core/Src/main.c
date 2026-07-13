#include <stdint.h>
#include "ciu32f003_std.h"
#include "user_led.h"

static void system_clock_config(void)
{
    std_flash_set_latency(FLASH_LATENCY_1CLK);

    std_rcc_rch_enable();
    while (std_rcc_get_rch_ready() != RCC_CSR1_RCHRDY)
    {
    }

    std_rcc_set_sysclk_source(RCC_SYSCLK_SRC_RCH);
    while (std_rcc_get_sysclk_source() != RCC_SYSCLK_SRC_STATUS_RCH)
    {
    }

    std_rcc_set_ahbdiv(RCC_HCLK_DIV1);
    std_rcc_set_apbdiv(RCC_PCLK_DIV1);

    SystemCoreClockUpdate();
}

static void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 1000U; i++)
    {
        __NOP();
    }
}

int main(void)
{
    system_clock_config();
    user_led_init();

    while (1)
    {
        user_led_toggle();
        delay_ms(500U);
    }
}
