#include "stm32f10x.h"
#include "ADC.h"
#include "PWM.h"
#include "Delay.h"

void initGPIO();

static const uint32_t Period = 1000;

uint32_t cnt = 0;

int main(void)
{
	initGPIO();

	mPWM1.initPWM();
	mPWM1.setPeriod(Period);
	mPWM1.enablePWM();
	mADC1.initADC();
	mADC1.enableADC();

    while(1)
    {
    	GPIOB->ODR |= GPIO_ODR_ODR5;
    	delay(1000);
    	GPIOB->ODR &= ~GPIO_ODR_ODR5;
    	delay(1000);
    }
}


void initGPIO(){

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL = (GPIOB->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF5_1)) | GPIO_CRL_MODE5_0;

}







