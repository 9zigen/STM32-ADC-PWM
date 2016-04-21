#include "locator.h"
#include "Delay.h"
static volatile double Distance = 0;

static void initGPIO(){

	//port
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL = (GPIOB->CRL &= ~GPIO_CRL_CNF1) | GPIO_CRL_MODE1;
	GPIOB->CRH = (GPIOB->CRH &= ~GPIO_CRH_CNF14_0 ) | GPIO_CRH_CNF14_1;
	GPIOB->CRH &= ~ GPIO_CRH_MODE14;

}

static void mesure(){

	delay(50000);
	GPIOB->ODR |= GPIO_ODR_ODR1;
	delay(10);
	GPIOB->ODR &= ~GPIO_ODR_ODR1;


}

static void initTIM7(){

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = SystemCoreClock/1000000-1; //Предделитель настроен на счет каждую микросекунду
	TIM7->ARR = 50000;  //Считаем до 50 мс, с запасом ))
}

static void initINT(){

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB; //Настраиваем прерывания на ногу 14 порта B
	EXTI->IMR = EXTI_IMR_MR14; //Разрешаем прерывания с этой ноги
	EXTI->RTSR = EXTI_RTSR_TR14; //Прерывания по нарастающему сигналу
	EXTI->FTSR = EXTI_FTSR_TR14; //...и по спаду сигнала
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void EXTI15_10_IRQHandler(void)
{
   EXTI->PR |= EXTI_PR_PR14; //Сбрасываем флаг прерывания
   if(GPIOB->IDR & GPIO_IDR_IDR14) TIM7->CR1 |= TIM_CR1_CEN; //Проверяем, если на ноге PA1 лог 1, запускаем таймер
   else{                                                                                           //... а если 0, то:
      TIM7->CR1 &= ~TIM_CR1_CEN; //Останавливаем таймер
      Distance = (double)TIM7->CNT/58; //Записываем в глобальную переменную значение регистра CNT/58 - это и будет расстояние в см
      TIM7->CNT = 0; //Обнуляем таймер
   }
}

static void init(){
	initGPIO();
	initTIM7();
	initINT();



}

static volatile double getDist(){
	return Distance;
}


typeLocator locator = { .init = init,
						.mesure = mesure,
					 	.getDist = getDist
};

