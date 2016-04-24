#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include "stm32f10x.h"
#include "Delay.h"

typedef struct{
	void (*init)(void);
	void (*turning)(int);
} typeMotor;

extern typeMotor Motor;

#endif
