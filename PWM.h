#ifndef PWM_H
#define PWM_H

typedef struct{
	void (*initPWM)(void);
	void (*enablePWM)(void);
	void (*disablePWM)(void);
	void (*setPeriod)(uint32_t);
	void (*setPercent)(uint32_t);

} typePWM;

extern typePWM mPWM1;

#endif
