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
extern void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);	  /*��ʽ�����*/


u8  USART_RX_BUF[USART_REC_LEN] __attribute__  ((at(0X20001000)));/*���ջ���,���USART_REC_LEN���ֽ�,��ʼ��ַΪ0X20001000.*/ 
u16 USART_RX_STA = 0;  /*����״̬���*/
u16 USART_RX_CNT = 0;  /*���յ��ֽ���*/
//int flag = 0;

/****************************************************************************
* ������: USART1_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void USART1_IRQHandler(void)
{
	u8 res;	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//���յ�����
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
* ������: TIM3_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void TIM3_IRQHandler(void)
{ 

}
/****************************************************************************
* ������: TIM6_IRQHandler()
* �� ��:
* �� ��: ��
* �� ��: ��
****************************************************************************/
void TIM6_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)			/*���ָ����TIM�жϷ������:TIM �ж�Դ*/
	{  		
		TIM_ClearFlag(TIM6,TIM_FLAG_Update);	                /*����жϱ�־λ*/			
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
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)			/*���ָ����TIM�жϷ������:TIM �ж�Դ*/
	{  		
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);	                /*����жϱ�־λ*/
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);										
	}
}
/****************************************************************************
* ������: EXTI0_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line0);                 /*���EXTI0��·����λ*/
	}
	
}
/****************************************************************************
* ������: EXTI1_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line1);                /*���EXTIx��·����λ*/
	}
	
}
/****************************************************************************
* ������: EXTI1_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!= RESET )
	{
	 
		
		EXTI_ClearITPendingBit(EXTI_Line2);                /*���EXTIx��·����λ*/
	}
	
}
/****************************************************************************
* ������: EXTI3_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line3);               /*���EXTIx��·����λ*/
	}
	
}
/****************************************************************************
* ������: EXTI4_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
****************************************************************************/
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!= RESET )
	{
	
		EXTI_ClearITPendingBit(EXTI_Line4);              /*���EXTIx��·����λ*/
	}
	
}
/****************************************************************************
* ������: EXTI9_5_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
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
 	 EXTI_ClearITPendingBit(EXTI_Line5);              /*���LINEx�ϵ��жϱ�־λ*/  
}

/****************************************************************************
* ������: EXTI15_10_IRQHandler()
* �� ��: ����
* �� ��: ��
* �� ��: ��
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
