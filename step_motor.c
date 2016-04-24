#include "step_motor.h"

static void init(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
	GPIOE->CRL  = (GPIOE->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_CNF3 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5 ))
					| GPIO_CRL_MODE2 | GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5;

	GPIOE->ODR &= ~(GPIO_ODR_ODR2 | GPIO_ODR_ODR3 | GPIO_ODR_ODR4 | GPIO_ODR_ODR5);
}


static void outPin(uint16_t pin, int8_t cmd){

	if(cmd){
		GPIOE->ODR |= pin;
	}
	else {
		GPIOE->ODR ^= ~pin;
	}

}

static void turning(int _corner){

	uint16_t pin[]= {GPIO_ODR_ODR2, GPIO_ODR_ODR3,GPIO_ODR_ODR4, GPIO_ODR_ODR5};
	int8_t seq[][4] = { {1,0,0,0},
	        {1,1,0,0},
	        {0,1,0,0},
	        {0,1,1,0},
	        {0,0,1,0},
	        {0,0,1,1},
	        {0,0,0,1},
	        {1,0,0,1} };

   for(int i = 0; i < 512; i++){
	   for(int j =0; j < 8; j++){
		   for(int k = 0; k < 4; k++){
			   outPin(pin[k], seq[j][k]);
		   }
		   delay(100);
	   }
   }

   GPIOE->ODR &= ~(GPIO_ODR_ODR2 | GPIO_ODR_ODR3 | GPIO_ODR_ODR4 | GPIO_ODR_ODR5);
}


typeMotor Motor = {.init = init,
				   .turning = turning
};
