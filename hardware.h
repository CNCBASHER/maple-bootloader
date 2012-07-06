/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "common.h"

/* macro'd register and peripheral definitions */
#undef RCC
#undef FLASH
#undef GPIOA
#undef GPIOC

#define RCC   ((u32)0x40023800)
#define FLASH ((u32)0x40023c00)
#define GPIOA ((u32)0x40020000)
#define GPIOC ((u32)0x40020800)

#define RCC_CR      RCC
#define RCC_CFGR    (RCC + 0x08)
#define RCC_CIR     (RCC + 0x0c)
#define RCC_AHBENR  (RCC + 0x1c)
#define RCC_APB2ENR (RCC + 0x20)
#define RCC_APB1ENR (RCC + 0x24)

#define FLASH_ACR     (FLASH + 0x00)
#define FLASH_PECR    (FLASH + 0x04)
#define FLASH_PDKEYR  (FLASH + 0x08)
#define FLASH_PEKEYR  (FLASH + 0x0c)
#define FLASH_PRGKEYR (FLASH + 0x10)
#define FLASH_OPTKEYR (FLASH + 0x14)
#define FLASH_SR      (FLASH + 0x18)
#define FLASH_OBR     (FLASH + 0x1C)
#define FLASH_WRPR1   (FLASH + 0x20)
#define FLASH_WRPR1   (FLASH + 0x80)
#define FLASH_WRPR1   (FLASH + 0x84)

#define FLASH_PEKEY1     0x89ABCDEF
#define FLASH_PEKEY2     0x02030405
#define FLASH_SR_BSY     0x01

#define GPIO_MODER(port)   port
#define GPIO_OTYPER(port)  (port+0x04)
#define GPIO_OSPEED(port)  (port+0x08)
#define GPIO_PUPDR(port)   (port+0x0c)
#define GPIO_IDR(port)     (port+0x10)
#define GPIO_ODR(port)     (port+0x14)
#define GPIO_BSRR(port)    (port+0x18)

#undef NVIC
#undef SCB

#define SCS      SCS_BASE
#define NVIC     NVIC_BASE
#define SCB      SCB_BASE
#define STK      SysTick_BASE

#define SCB_VTOR (SCB+0x08)
#define STK_CTRL (STK+0x00)

#define TIM1_APB2_ENB ((u32)0x00000800)
#define TIM1          ((u32)0x40012C00)
#define TIM1_PSC      (TIM1+0x28)
#define TIM1_ARR      (TIM1+0x2C)
#define TIM1_RCR      (TIM1+0x30)
#define TIM1_CR1      (TIM1+0x00)
#define TIM1_CR2      (TIM1+0x04)
#define TIM1_DIER     (TIM1+0x0C)
#define TIM1_UP_IRQ_Channel ((u8)0x19)

#define USB_HP_IRQ  ((u8)0x13)
#define USB_LP_IRQ  ((u8)0x14)
#define TIM2_IRQ    ((u8)0x1C)


/* AIRCR  */
#define AIRCR_RESET         0x05FA0000
#define AIRCR_RESET_REQ     (AIRCR_RESET | (u32)0x04);

/* temporary copyage of example from kiel */
#define __VAL(__TIMCLK, __PERIOD) ((__TIMCLK/1000000UL)*__PERIOD)
#define __PSC(__TIMCLK, __PERIOD)  (((__VAL(__TIMCLK, __PERIOD)+49999UL)/50000UL) - 1)
#define __ARR(__TIMCLK, __PERIOD) ((__VAL(__TIMCLK, __PERIOD)/(__PSC(__TIMCLK, __PERIOD)+1)) - 1)

#define SET_REG(addr,val) do { *(vu32*)(addr)=val; } while(0)
#define GET_REG(addr)     (*(vu32*)(addr))


/* todo: there must be some major misunderstanding in how we access
   regs. The direct access approach (GET_REG) causes the usb init to
   fail upon trying to activate RCC_APB1 |= 0x00800000. However, using
   the struct approach from ST, it works fine...temporarily switching
   to that approach */
typedef struct
{
  vu32 CR;
  vu32 CFGR;
  vu32 CIR;
  vu32 APB2RSTR;
  vu32 APB1RSTR;
  vu32 AHBENR;
  vu32 APB2ENR;
  vu32 APB1ENR;
  vu32 BDCR;
  vu32 CSR;
} RCC_RegStruct;
#define pRCC ((RCC_RegStruct *) RCC)

typedef struct {
  vu32 ISER[2];
  u32  RESERVED0[30];
  vu32 ICER[2];
  u32  RSERVED1[30];
  vu32 ISPR[2];
  u32  RESERVED2[30];
  vu32 ICPR[2];
  u32  RESERVED3[30];
  vu32 IABR[2];
  u32  RESERVED4[62];
  vu32 IPR[15];
} NVIC_TypeDef;

typedef struct {
  vuc32 CPUID;
  vu32 ICSR;
  vu32 VTOR;
  vu32 AIRCR;
  vu32 SCR;
  vu32 CCR;
  vu32 SHPR[3];
  vu32 SHCSR;
  vu32 CFSR;
  vu32 HFSR;
  vu32 DFSR;
  vu32 MMFAR;
  vu32 BFAR;
  vu32 AFSR;
} SCB_TypeDef;


void setPin    (u32 bank, u8 pin);
void resetPin  (u32 bank, u8 pin);
bool readPin   (u32 bank, u8 pin);
void strobePin (u32 bank, u8 pin, u8 count, u32 rate);

void systemHardReset(void);
void systemReset   (void);
void setupCLK      (void);
void setupLED      (void);
void setupFLASH    (void);
bool checkUserCode (u32 usrAddr);
void jumpToUser    (u32 usrAddr);

bool flashWriteWord  (u32 addr, u32 word);
bool flashErasePage  (u32 addr);
bool flashErasePages (u32 addr, u16 n);
void flashLock       (void);
void flashUnlock     (void);
void nvicInit        (NVIC_InitTypeDef*);
void nvicDisableInterrupts(void);

#endif
