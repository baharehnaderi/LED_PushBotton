#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

int main(){
	
	void delay(void);
	
	GPIO_InitTypeDef GPIO_Struct;
	EXTI_InitTypeDef EXTI_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// LED
	GPIO_Struct.GPIO_Mode=(GPIO_Mode_Out_PP);
	GPIO_Struct.GPIO_Pin=(GPIO_Pin_2);
	GPIO_Struct.GPIO_Speed=(GPIO_Speed_50MHz);
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	//PushBotton
	GPIO_Struct.GPIO_Mode=(GPIO_Mode_IPU);
	GPIO_Struct.GPIO_Pin=(GPIO_Pin_6);
	GPIO_Struct.GPIO_Speed=(GPIO_Speed_50MHz);
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
	
	EXTI_Struct.EXTI_Line=EXTI_Line6;
	EXTI_Struct.EXTI_LineCmd=ENABLE;
	EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_Struct);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_Struct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Struct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Struct);
	
	
	while(1){
		
		delay();
	}		
}

void EXTI9_5_IRQHandler(void) {
    if(EXTI_GetFlagStatus(EXTI_Line6)==1){
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
			delay();
			GPIO_ResetBits(GPIOC,GPIO_Pin_2);
			EXTI_ClearFlag(EXTI_Line6);
			
		}

	}	

void delay(void){
		
		int i,j;
	for(i=1;i<1000;++i)
		for(j=1;j<1000;++j);
	}