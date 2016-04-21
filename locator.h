#ifndef LOCATOR_H
#define LOCATOR_H

#include "stm32f10x.h"

typedef struct{
	void (*init)(void);
	void (*mesure)(void);
	volatile double(*getDist)(void);
} typeLocator;


extern typeLocator locator;

#endif
