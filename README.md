Для изначальной задачи мигать тремя светодиодами асинхронно, я выбрал очень тривиальный метод.
Просто изменял задержку для каждого светодиода отдельно т.е. f = 1 Hz, T = (1/f)*1000;
Как бы мой подход не был правильным или не правильным, я немного сбился с изначальней задачи
желанием немного поработать со структурами и изучить их глубже.

В led.c хотел сделать универсальную инициализацию любого GPIO.

Параметры init_led(uint16_t frequency, uint16_t pin, uint8_t port)
frequency - Частота для вычисления нужной задержки vTaskDelay(), чтобы с такой то частотой мигал
pin       - Для выяснения GPIOx->CRx верхних или нижних, и выставление мода и конфиг.
port      - Для выяснения GPIOx и RCC_APB2ENR_IOPxEN.
            Сам GPIOx является ссылкой структуры GPIO_TypeDef*

Но мне кажется именно в функция choice_CRx(); в led.c написана криво. Хочу доработать в образовательных целях.

Включенные компоненты в Run-Time Environment

CMSIS   -   CORE
        -   RTOS(API)   -   FreeRTOS
        -   RTOS2(API)  -   FreeRTOS
Device  -   Startup
RTOS    -   Config
        -   Core
        -   Event Groups
        -   Heap_1
        -   Timers
