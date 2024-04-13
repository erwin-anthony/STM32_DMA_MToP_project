#include "stm32f10x.h"                  // Device header
#include "bsp_led.h"
#include "bsp_dma_mtp.h"
#include "bsp_systick.h"


extern uint8_t SendBuff[SENDBUFF_SIZE];



int main(void){
	
	uint16_t i = 0;
	
	
	//相关函数初始化
	LED_GPIO_Config();
	USARTx_DMA_Config();
	USART_Config();
	
	
	/* 使能串口发送请求 */
	USART_DMACmd(USARTx,USART_DMAReq_Tx, ENABLE);

		
	//填充数组
	for(i = 0;i < SENDBUFF_SIZE;i++){
		SendBuff[i] = 'A';
	}


	
	while(1){
		LED_G_TOGGLE;
		SysTick_Delay_ms(500);

			}
		
	
	
}
