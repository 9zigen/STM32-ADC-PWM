#include "stm32f10x.h"
#include "PWM.h"

static void initPWM1(){

	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL = (GPIOB->CRL &= ~(GPIO_CRL_CNF6_0)) | GPIO_CRL_CNF6_1;
	GPIOB->CRL |= GPIO_CRL_MODE6;

	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCMR1|=(TIM_CCMR1_OC1M_0 |TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);


}

static void enablePWM1(){
	TIM4->CR1 |= TIM_CR1_CEN;
	TIM4->CCR1 = 0;
}

static void disablePWM1(){
	TIM4->CR1 &= ~TIM_CR1_CEN;
}

static void setPeriod1(uint32_t p){
	TIM4->ARR =  p;
}

static void setPercent1(uint32_t p){
	TIM4->CCR1 = p;
}

typePWM mPWM1 = {.initPWM = initPWM1,
				 .enablePWM = enablePWM1,
				 .disablePWM = disablePWM1,
				 .setPeriod = setPeriod1,
				 .setPercent = setPercent1
				};
