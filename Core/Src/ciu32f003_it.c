#include "ciu32f003_it.h"
#include "ciu32f003.h"
#include <stdio.h>

void NMI_Handler(void)
{
}

__attribute__((noreturn, noinline, used)) void HardFault_Dump(uint32_t *stack_frame,
                                                              uint32_t *saved_regs)
{
    uint32_t r0 = stack_frame[0];
    uint32_t r1 = stack_frame[1];
    uint32_t r2 = stack_frame[2];
    uint32_t r3 = stack_frame[3];
    uint32_t r12 = stack_frame[4];
    uint32_t lr = stack_frame[5];
    uint32_t pc = stack_frame[6];
    uint32_t xpsr = stack_frame[7];
    uint32_t sp = (uint32_t)(stack_frame + 8U);

    if ((xpsr & (1UL << 9)) != 0U)
    {
        sp += 4U;
    }

    printf("\r\n[HardFault]\r\n");
    printf("R0  = 0x%08lX\r\n", (unsigned long)r0);
    printf("R1  = 0x%08lX\r\n", (unsigned long)r1);
    printf("R2  = 0x%08lX\r\n", (unsigned long)r2);
    printf("R3  = 0x%08lX\r\n", (unsigned long)r3);
    printf("R4  = 0x%08lX\r\n", (unsigned long)saved_regs[4]);
    printf("R5  = 0x%08lX\r\n", (unsigned long)saved_regs[5]);
    printf("R6  = 0x%08lX\r\n", (unsigned long)saved_regs[6]);
    printf("R7  = 0x%08lX\r\n", (unsigned long)saved_regs[7]);
    printf("R8  = 0x%08lX\r\n", (unsigned long)saved_regs[0]);
    printf("R9  = 0x%08lX\r\n", (unsigned long)saved_regs[1]);
    printf("R10 = 0x%08lX\r\n", (unsigned long)saved_regs[2]);
    printf("R11 = 0x%08lX\r\n", (unsigned long)saved_regs[3]);
    printf("R12 = 0x%08lX\r\n", (unsigned long)r12);
    printf("R13 = 0x%08lX\r\n", (unsigned long)sp);
    printf("R14 = 0x%08lX\r\n", (unsigned long)lr);
    printf("R15 = 0x%08lX\r\n", (unsigned long)pc);
    printf("xPSR= 0x%08lX\r\n", (unsigned long)xpsr);

    while (1)
    {
    }
}

__attribute__((naked)) void HardFault_Handler(void)
{
    __asm volatile(
        "mov r0, sp\n"
        "push {r4-r7}\n"
        "mov r4, r8\n"
        "mov r5, r9\n"
        "mov r6, r10\n"
        "mov r7, r11\n"
        "push {r4-r7}\n"
        "mov r1, sp\n"
        "bl HardFault_Dump\n"
        "b .\n");
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

void FLASH_IRQHandler(void)
{
}

void RCC_IRQHandler(void)
{
}

void EXTI0_1_IRQHandler(void)
{
}

void EXTI2_3_IRQHandler(void)
{
}

void EXTI4_7_IRQHandler(void)
{
}

void ADC_COMP_IRQHandler(void)
{
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
}

void TIM1_CC_IRQHandler(void)
{
}

void TIM3_IRQHandler(void)
{
}

void LPTIM1_IRQHandler(void)
{
}

void I2C1_IRQHandler(void)
{
}

void SPI1_IRQHandler(void)
{
}

void UART1_IRQHandler(void)
{
}

void UART2_IRQHandler(void)
{
}
