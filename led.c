#include "led.h"

void led_on(led* _led){
	(_led->__GPIO)->ODR		|= (1<<(_led->_pin));
}

void led_off(led* _led){
	(_led->__GPIO)->BSRR	|=	1<<(16+_led->_pin);
}

void toggle_led(led* _led){
	(_led->__GPIO)->BSRR	|=	1<<(_led->_pin);
}

void choice_CRx(uint16_t* pin, GPIO_TypeDef* GPIOx){
	if( (*pin)<=7 ){
		// 10: Output mode, max speed 2 MHz.
		GPIOx->CRL		&=	~(1<<(4*(*pin)));
		GPIOx->CRL		|=	2<<(4*(*pin));
		// 00: General purpose output push-pull
		GPIOx->CRL		&=	~(3<<(2+4*(*pin)));
	}
	if( (*pin)>7 ){
		*pin = ((*pin)-8);
		// 10: Output mode, max speed 2 MHz.
		GPIOx->CRH		&=	~(1<<(4*(*pin)));
		GPIOx->CRH		|=	2<<(4*(*pin));
		// 00: General purpose output push-pull
		GPIOx->CRH		&=	~(3<<(2+4*(*pin)));
	}
}

void choice_GPIOx(uint8_t* port, GPIO_TypeDef* GPIOx){
	switch(*port){
		case 'A':
			GPIOx					=		((GPIO_TypeDef *) GPIOA_BASE);
			RCC->APB2ENR	|=	RCC_APB2ENR_IOPAEN;
			break;
		case 'B':
			GPIOx					=		((GPIO_TypeDef *) GPIOB_BASE);
			RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
			break;
		case 'C':
			GPIOx					=		((GPIO_TypeDef *) GPIOC_BASE);
			RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;
			break;
		default:
			break;
	}	
}

led init_led(uint16_t frequency, uint16_t pin, uint8_t port){
	GPIO_TypeDef* GPIOx;
	choice_GPIOx(&port,GPIOx);
	choice_CRx(&pin,GPIOx);
	led buff_led = {pin,(uint32_t)(1000/frequency),GPIOx};
	return buff_led;
}

void vBlinker1(void *pvParameters){
	led* _led = (led*)pvParameters;
	while(1){
		toggle_led(_led);
		vTaskDelay(1000);
	}
}

void vBlinker2(void *pvParameters){
	while(1){
		toggle_led2();
		vTaskDelay(167);
	}
}

void vBlinker3(void *pvParameters){
	while(1){
		toggle_led3();
		vTaskDelay(77);
	}
}

void init_task_blink(led* _led){
	xTaskCreate(vBlinker1,"Blinker1",configMINIMAL_STACK_SIZE,(void*)_led,tskIDLE_PRIORITY+1,NULL);
	xTaskCreate(vBlinker2,"Blinker2",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1,NULL);
	xTaskCreate(vBlinker3,"Blinker3",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1,NULL);
	vTaskStartScheduler();
}

void init_led3(void){
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
	
	// 10: Output mode, max speed 2 MHz.
	GPIOB->CRH		&=	~GPIO_CRH_MODE13_0;
	GPIOB->CRH		|=	GPIO_CRH_MODE13_1;
	
	// 00: General purpose output push-pull
	GPIOB->CRH		&=	~GPIO_CRH_CNF13;
}

void init_led2(void){
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
	
	// 10: Output mode, max speed 2 MHz.
	GPIOB->CRH		&=	~GPIO_CRH_MODE12_0;
	GPIOB->CRH		|=	GPIO_CRH_MODE12_1;
	
	// 00: General purpose output push-pull
	GPIOB->CRH		&=	~GPIO_CRH_CNF12;
}

void init_led1(void){
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;
	
	// 10: Output mode, max speed 2 MHz.
	GPIOC->CRH		&=	~GPIO_CRH_MODE13_0;
	GPIOC->CRH		|=	GPIO_CRH_MODE13_1;
	
	// 00: General purpose output push-pull
	GPIOC->CRH		&=	~GPIO_CRH_CNF13;
}

void toggle_led1(void){
	GPIOC->ODR		^=	GPIO_ODR_ODR13;
}
void toggle_led2(void){
	GPIOB->ODR		^=	GPIO_ODR_ODR12;
}
void toggle_led3(void){
	GPIOB->ODR		^=	GPIO_ODR_ODR13;
}

