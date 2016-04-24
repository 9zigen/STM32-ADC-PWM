#include "locator.h"
#include "Delay.h"
static volatile double Distance = 0;

static void initGPIO(){

	//port
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	//GPIOB->CRL = (GPIOB->CRL &= ~GPIO_CRL_CNF1) | GPIO_CRL_MODE1;

	GPIOB->CRL = (GPIOB->CRL &= ~(GPIO_CRL_CNF1_0)) | GPIO_CRL_CNF1_1;
	GPIOB->CRL |= GPIO_CRL_MODE1;

	GPIOB->CRH = (GPIOB->CRH &= ~GPIO_CRH_CNF14_0 ) | GPIO_CRH_CNF14_1;
	GPIOB->CRH &= ~ GPIO_CRH_MODE14;

}

static void initTIM3(){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		TIM3->PSC = SystemCoreClock / 1000000 -1;
		TIM3->ARR = 60000;
		TIM3->CCR4 = 10;
		TIM2->CCMR2 |= TIM_CCMR2_OC4PE;
		TIM3->CCMR2 |= TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
		TIM3->CCER |= TIM_CCER_CC4E;
		TIM3->CR1 |= TIM_CR1_CEN;
}

static void mesure(){

	delay(50000);
	GPIOB->ODR |= GPIO_ODR_ODR1;
	delay(10);
	GPIOB->ODR &= ~GPIO_ODR_ODR1;
}

static void initTIM7(){

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = SystemCoreClock/1000000-1;
	TIM7->ARR = 50000;
}

static void initINT(){

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB;
	EXTI->IMR = EXTI_IMR_MR14;
	EXTI->RTSR = EXTI_RTSR_TR14;
	EXTI->FTSR = EXTI_FTSR_TR14;
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void EXTI15_10_IRQHandler(void)
{
   EXTI->PR |= EXTI_PR_PR14;
   if(GPIOB->IDR & GPIO_IDR_IDR14) TIM7->CR1 |= TIM_CR1_CEN;
   else{
      TIM7->CR1 &= ~TIM_CR1_CEN;
      Distance = TIM7->CNT/58;
      TIM7->CNT = 0;
   }
}

static void init(){
	initGPIO();
	initTIM3();
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

