/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "iap.h"
#include "stdio.h"
#include "delay.h"
#include "usart.h"
extern void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);	  /*格式化输出*/


u8  USART_RX_BUF[USART_REC_LEN] __attribute__  ((at(0X20001000)));/*接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000.*/ 
u16 USART_RX_STA = 0;  /*接收状态标记*/
u16 USART_RX_CNT = 0;  /*接收的字节数*/
//int flag = 0;

/****************************************************************************
* 函数名: USART1_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void USART1_IRQHandler(void)
{
	u8 res;	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res=USART_ReceiveData(USART1);
		if(USART_RX_CNT<USART_REC_LEN)
		{
			USART_RX_BUF[USART_RX_CNT]=res;
			USART_RX_CNT++;			 									     
		}
		USART_ClearFlag(USART1, USART_FLAG_RXNE); 
	}
} 
/****************************************************************************
* 函数名: TIM3_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void TIM3_IRQHandler(void)
{ 

}
/****************************************************************************
* 函数名: TIM6_IRQHandler()
* 功 能:
* 输 入: 无
* 输 出: 无
****************************************************************************/
void TIM6_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)			/*检查指定的TIM中断发生与否:TIM 中断源*/
	{  		
		TIM_ClearFlag(TIM6,TIM_FLAG_Update);	                /*清除中断标志位*/			
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);	 
		
	}
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)			/*检查指定的TIM中断发生与否:TIM 中断源*/
	{  		
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);	                /*清除中断标志位*/
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);										
	}
}
/****************************************************************************
* 函数名: EXTI0_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line0);                 /*清除EXTI0线路挂起位*/
	}
	
}
/****************************************************************************
* 函数名: EXTI1_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line1);                /*清除EXTIx线路挂起位*/
	}
	
}
/****************************************************************************
* 函数名: EXTI1_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!= RESET )
	{
	 
		
		EXTI_ClearITPendingBit(EXTI_Line2);                /*清除EXTIx线路挂起位*/
	}
	
}
/****************************************************************************
* 函数名: EXTI3_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line3);               /*清除EXTIx线路挂起位*/
	}
	
}
/****************************************************************************
* 函数名: EXTI4_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line4);              /*清除EXTIx线路挂起位*/
	}
	
}
/****************************************************************************
* 函数名: EXTI9_5_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{			
	static int i = 0;
	if((EXTI_GetITStatus(EXTI_Line5) != RESET))
	{
     if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0)
		 {
			 
		 }
	}
 	 EXTI_ClearITPendingBit(EXTI_Line5);              /*清除LINEx上的中断标志位*/  
}

/****************************************************************************
* 函数名: EXTI15_10_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)
	{
	  //delay_ms(100);
		//if((GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10) == 0) )
		{
				//flag++;				    
				//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, GPIO_PinSource10);
			  
				EXTI_InitStructure.EXTI_Line = EXTI_Line15;
				EXTI_InitStructure.EXTI_LineCmd = DISABLE;
				EXTI_Init(&EXTI_InitStructure);
				EXTI_ClearITPendingBit(EXTI_Line15);
			
	   }
	 }
}


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
