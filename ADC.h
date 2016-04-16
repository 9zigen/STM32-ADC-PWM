#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "PWM.h"

typedef struct {
	 void (*initADC)(void);
	 void (*enableADC)(void);
	 void (*disableADC)(void);
	 uint32_t (*getResult)(void);
} typeADC;

extern typeADC mADC1;


#endif
