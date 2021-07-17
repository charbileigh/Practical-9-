// Description----------------------------------------------------------------|
/*
 * Initialises a struct with Name and Age data. Displays results on LEDs and
 * LCD.
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051
//>>> Uncomment line 10 if using System Workbench (SW4STM32) or STM32CubeIDE
//#define SW4STM32

#ifndef SW4STM32
	#define TRUESTUDIO
#endif

#include "stm32f0xx.h"

// GLOBAL VARIABLES ----------------------------------------------------------|


// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                                                   //COMPULSORY
void init_ADC(void);											   //COMPULSORY
void init_timer_2(void);
void init_timer_6(void);
#ifdef TRUESTUDIO												   //COMPULSORY
	void reset_clock_to_48Mhz(void);							   //COMPULSORY
#endif															   //COMPULSORY



// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{
#ifdef TRUESTUDIO  											 	   //COMPULSORY
	reset_clock_to_48Mhz();										   //COMPULSORY
#endif															   //COMPULSORY
	init_ADC();
	init_timer_2();
	init_timer_6();
	while(1)
	{

	}
}

// OTHER FUNCTIONS -----------------------------------------------------------|

#ifdef TRUESTUDIO												   //COMPULSORY
/* Description:
 * This function resets the STM32 Clocks to 48 MHz
 */
void reset_clock_to_48Mhz(void)									   //COMPULSORY
{																   //COMPULSORY
	if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL)			   //COMPULSORY
	{															   //COMPULSORY
		RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW);					   //COMPULSORY
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);	   //COMPULSORY
	}															   //COMPULSORY

	RCC->CR &= (uint32_t)(~RCC_CR_PLLON);						   //COMPULSORY
	while ((RCC->CR & RCC_CR_PLLRDY) != 0);						   //COMPULSORY
	RCC->CFGR = ((RCC->CFGR & (~0x003C0000)) | 0x00280000);		   //COMPULSORY
	RCC->CR |= RCC_CR_PLLON;									   //COMPULSORY
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);						   //COMPULSORY
	RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL);					   //COMPULSORY
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);		   //COMPULSORY
}																   //COMPULSORY
#endif															   //COMPULSORY

void init_ADC(void)
{
	// Enable Clock for Port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// Enable Analog mode for Port A Pin 6
	GPIOA->MODER |= GPIO_MODER_MODER6;
	// Enable ADC Clock
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	// Enable ADC
	ADC1->CR |= ADC_CR_ADEN;
	// Select channel 6 to link with Port A Pin 6
	ADC1->CHSELR |= ADC_CHSELR_CHSEL6;
	// Setup in wait mode
	ADC1->CFGR1 |= ADC_CFGR1_WAIT;
	// Setup 10 bit resolution
	ADC1->CFGR1 |= ADC_CFGR1_RES_0;
	// Wait until ADRDY == 1
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0);
}

void init_timer_2(void)
{
	// Enable clock for timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	// Enable clock for Port B
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	// Configure Alternate function mode on Port B pin 10
	GPIOB->MODER |= GPIO_MODER_MODER10_1;
	// Configure Port B pin 20 to timer2 channel 3
	GPIOB->AFR[1] |= 0b1000000000;

	// Set the Prescaler Register
	TIM2->PSC = 0;
	// Set the Auto Reload Register value for period of the PWM signal
	TIM2->ARR = 3200;
	// Set the Capture/Count Register value for duty cycle of PWM signal
	TIM2->CCR3 = 3200/4;
	// Select PWM mode 1 and enable Preload Register
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
	// Enable output on timer channel
	TIM2->CCER |= TIM_CCER_CC3E;
	// Start timer for timer 2
	TIM2->CR1 |= TIM_CR1_CEN;
}

void init_timer_2(void)
{
	// Enable clock for timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	// Enable clock for Port B
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	// Configure Alternate function mode on Port B pin 10
	GPIOB->MODER |= GPIO_MODER_MODER10_1;
	// Configure Alternate function mode on Port B pin 11
	GPIOB->MODER |= GPIO_MODER_MODER11_1; 
	// Configure Port B pin 10 to timer2 channel 3
	GPIOB->AFR[1] |= 0b1000000000;
	// Configure Port B pin 11 to timer2 channel 4
	GPIOB->AFR[1] |= 0b1000000000000;

	// Set the Prescaler Register
	TIM2->PSC = 0;
	// Set the Auto Reload Register value for period of the PWM signal
	TIM2->ARR = 3200;

	// Set the Capture/Count Register value for duty cycle of PWM signal
	TIM2->CCR3 = 3200/4;
	// Select PWM mode 1 and enable Preload Register on TIM2 channel 3
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
	// Enable output on TIM2 channel 3
	TIM2->CCER |= TIM_CCER_CC3E;

	// Set the Capture/Count Register value for duty cycle of PWM signal
	TIM2->CCR4 = 3200*(3/4);
	// Select PWM mode 1 and enable Preload Register on TIM2 channel 4
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE;
	// Enable output on TIM2 channel 4
	TIM2->CCER |= TIM_CCER_CC4E;

	// Start timer for timer 2
	TIM2->CR1 |= TIM_CR1_CEN;
}

void init_timer_6(void)
{
	// Enable TIM6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 36;
	TIM6->ARR = 64865;
	// Enable TIM6 interrupt
	TIM6->DIER |= TIM_DIER_UIE;
	// Unmask the TIM6 interrupt in the NVIC 
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	// Start counter for TIM6
	TIM6->CR1 |= TIM_CR1_CEN;
}

// INTERRUPT HANDLERS --------------------------------------------------------|

void TIM6_DAC_IRQHandler(void)
{
	// Start ADC conversion
	ADC1 -> CR |= ADC_CR_ADSTART;
	 // Wait until EOC == 1
	while((ADC1->ISR & ADC_ISR_EOC) == 0);
	
	TIM2->PSC = ADC1->DR + 1;
	// Set the Auto Reload Register value for period of the PWM signal
	TIM2->ARR = (0.05 + 48000000)/TIM2->PSC;
	// Set the Capture/Count Register value for duty cycle of PWM signal
	TIM2->CCR3 = TIM2->ARR * (ADC1->DR/1023);
	// acknowledge interrupt
	TIM6->SR &= ~TIM_SR_UIF;	
}