#ifndef _LED
#define _LED

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct{
	uint16_t _pin;
	uint32_t _delay_for_task;
	GPIO_TypeDef* __GPIO;
}led;

void choice_CRx(uint16_t* pin, GPIO_TypeDef* GPIOx);
void choice_GPIOx(uint8_t* port, GPIO_TypeDef* GPIOx);

void led_on(led* _led);
void led_off(led* _led);

void vBlinker1(void *pvParameters);
void vBlinker2(void *pvParameters);
void vBlinker3(void *pvParameters);
void init_task_blink(led* _led);

led init_led(uint16_t frequency, uint16_t pin, uint8_t port);
void init_led3(void);
void init_led2(void);
void init_led1(void);

void toggle_led(led* _led);
void toggle_led1(void);
void toggle_led2(void);
void toggle_led3(void);

#endif
