#include "ADC.h"
#include "step_motor.h"

static uint32_t adc1 = 0;


static void initADC1(){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = ( GPIOA->CRL &= ~GPIO_CRL_CNF0_1) | GPIO_CRL_CNF0_0;
    GPIOA->CRL &= ~(GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 );

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |= ADC_CR2_CAL;
	while(!(ADC1->CR2 & ADC_CR2_CAL));

	ADC1->CR1 |= ADC_CR1_JAUTO | ADC_CR1_SCAN | ADC_CR1_JEOCIE;
	ADC1->CR2 |= ADC_CR2_JEXTSEL | ADC_CR2_CONT | ADC_CR2_JEXTTRIG;
	ADC1->JSQR |= (1<<15);
	ADC1->SMPR2 |= ADC_SMPR2_SMP0;
	ADC1->JSQR |= ADC_JSQR_JL;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_JSWSTART;

	NVIC_EnableIRQ(ADC1_2_IRQn);
}

static void enableADC1(){
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_JSWSTART;
}

static void disableADC1(){
	ADC1->CR2 &= ~ADC_CR2_ADON;
}

static uint32_t getResult(){
	return adc1;
}


void ADC1_2_IRQHandler(void){

	  ADC1->SR &= ~ADC_SR_JEOC;
	  adc1 = ADC1->JDR1;
	  double p = (double)adc1 / 4000;
	  mPWM1.setPercent(1000 * p);


}


typeADC mADC1 = {initADC1, enableADC1, disableADC1, getResult};
