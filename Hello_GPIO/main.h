
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Error_Handler(void);

#define GPIO_LED_Pin GPIO_PIN_13
#define GPIO_LED_GPIO_Port GPIOC
#define GPIO_SW_Pin GPIO_PIN_0
#define GPIO_SW_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
