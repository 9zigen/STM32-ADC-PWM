#include "Delay.h"

static uint8_t flag = 1;

void delay(uint32_t _delay){

	initTIM6();
	TIM6->ARR = _delay * 10;
	TIM6->CR1 |= TIM_CR1_CEN;
	flag = 1;
	while(flag);

}


void TIM6_IRQHandler(void){
	flag = 0;
	TIM6->CR1 &= ~TIM_CR1_CEN;
	TIM6->SR &= ~TIM_SR_UIF;
}

void initTIM6(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = SystemCoreClock / 10000 - 1;
	TIM6->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM6_IRQn);
}
