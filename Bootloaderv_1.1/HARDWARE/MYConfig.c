#include "sys.h"

/*********************************************************************************************************
*                                          ȫ�ֱ���
*********************************************************************************************************/



/*********************************************************************************************************
*                                          ��������
*********************************************************************************************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void TIM6_Configuration(void);
void EXTI_Configuration(void);
void TIM7_Configuration(void);

/*********************************************************************************************************
* ��    �� ��Config_Init 
* �������� : ��ʼ��Ӧ�����ú���
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� :�����ڡ��޸��������޸�ԭ��
* ����˵�� : 
*********************************************************************************************************/
void Config_Init (void)
{
	  RCC_Configuration();
	  GPIO_Configuration();
	  NVIC_Configuration();
	  USART1_Configuration();		//���ڴ�ӡ	   
//	TIM1_Configuration();		
	  TIM4_Configuration();		 //pwm
// 	TIM5_Configuration();
// 	TIM6_Configuration();		//��ʱ������̬
//	TIM7_Configuration();		//��ȷ��ʱ
	  EXTI_Configuration();
}

/*********************************************************************************************************
* ��    �� ��RCC_Configuration
* �������� : ��ʼ��ϵͳʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);�ⲿ�жϣ���Ҫʹ�� AFIO ʱ��
*********************************************************************************************************/
void RCC_Configuration(void){

  SystemInit(); 

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM6|RCC_APB1Periph_TIM7
  						, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
  						| RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE
						| RCC_APB2Periph_GPIOE| RCC_APB2Periph_USART1, ENABLE);
}
/*********************************************************************************************************
* ��    �� ��GPIO_Configuration
* �������� : 
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/ 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //ͨ���������ģʽ
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //ͨ���������ģʽ
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			 //ͨ���������ģʽ
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //ͨ���������ģʽ
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);				    
}

/*********************************************************************************************************
* ��    �� ��USART1_Configuration
* �������� : ��ʼ������1
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void USART1_Configuration()
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;              /*PA.9*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       /*�����������*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 /*��ʼ��GPIOA.9*/
   
	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             /*PA10*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  /*��������*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 /*��ʼ��GPIOA.10*/  

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;           /*���ڲ�����*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      /*�ֳ�Ϊ8λ���ݸ�ʽ*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           /*һ��ֹͣλ*/
	USART_InitStructure.USART_Parity = USART_Parity_No;              /*����żУ��λ*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  /*��Ӳ������������*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                 /*�շ�ģʽ*/

	USART_Init(USART1, &USART_InitStructure);     /*��ʼ������1*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);/*�������ڽ����ж�*/
	USART_Cmd(USART1, ENABLE);                    /*ʹ�ܴ���1*/ 
}

/*********************************************************************************************************
* ��    �� ��TIM4_Configuration
* �������� : ��ʼ����ʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void TIM4_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 10000;					 /*f��pwm��=(72Mhz/200000)=360hzƵ��*/
	TIM_TimeBaseStructure.TIM_Prescaler = (15-1);	 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
	TIM_OCInitStructure.TIM_Pulse = 5000;						            
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	      /*�ߵ�ƽ*/

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);			          /*ʹ�ܻ���ʧ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���*/

	TIM_ARRPreloadConfig(TIM4, ENABLE);  
	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}
/*********************************************************************************************************
* ��    �� ��TIM5_Configuration
* �������� : ��ʼ����ʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void TIM5_Configuration(void)
{
	
}
/*********************************************************************************************************
* ��    �� ��TIM6_Configuration
* �������� : ��ʼ����ʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void TIM6_Configuration(void)
{
	
}
/*********************************************************************************************************
* ��    �� ��TIM7_Configuration
* �������� : ��ʼ����ʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 5000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_PrescalerConfig(TIM7, 7200-1, TIM_PSCReloadMode_Immediate);
	 
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);		
}
/*********************************************************************************************************
* ��    �� ��NVIC_Configuration
* �������� : ��ʼ���ж����ȼ�
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
}
/*********************************************************************************************************
* ��    �� ��NVIC_Configuration
* �������� : ��ʼ���ж����ȼ�
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	     /*����ʹ��FreeRTOS�����Ա�������Ϊ��4*/   
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               /*USB_LP_CAN1_RX0_IRQn;	CAN1 RX0�ж�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		    /*��ռ���ȼ�0*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			        /*�����ȼ�Ϊ0*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		   
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

}
