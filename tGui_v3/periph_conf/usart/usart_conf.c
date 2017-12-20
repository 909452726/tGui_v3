#include "usart_conf.h"

void USART1Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	/* TX PA9 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 /* RX PA10 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  ���� PXx �� USARTx__Rx*/
	/*  ���� PXx �� USARTx__Tx*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStructure); 
	
	/* Ƕ�������жϿ�����NVIC���� */
	USART1_NVICConfig();
	/* ʹ�ܴ��� */
	USART_Cmd(USART1, ENABLE);
	
    /* Enable the EVAL_COM1 Receive interrupt: this interrupt is generated when the 
       EVAL_COM1 receive data register is not empty */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void USART1_NVICConfig()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}




/*----------------------------------*/
void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);
	/* �ȴ��������ݼĴ���Ϊ�� �� TDR �Ĵ����������Ѵ��䵽��λ�Ĵ���ʱ����λ��Ӳ���� 1*/
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);
}

void USART_SendString(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k = 0;
	do 
	{
		USART_SendByte(pUSARTx, *(str + k));
		k++;
	} while (*(str + k) != '\0');
  
	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

//��16λ
void USART_SendHalfWord(USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	/* ȡ���߰�λ */
	temp_h = (ch & 0XFF00) >> 8;
	/* ȡ���Ͱ�λ */
	temp_l = ch & 0XFF;
	/* ���͸߰�λ */
	USART_SendData(pUSARTx, temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx, temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*----------------------------printf-------------------------------*/
//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����

// int fputc(int ch, FILE *f)
//{
//	// ����һ���ֽ����ݵ����� 
//	USART_SendData(USART1, (uint8_t) ch);
//		
//	// �ȴ�������� 
//	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//		;		
//	return (ch);
//}
//
////�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
//int fgetc(FILE *f)
//{
//	// �ȴ������������� 
//	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//		;
//	return (int)USART_ReceiveData(USART1);
//}


/*--------------------------------User------------------------------------*/

void USART1_TX(int*buf, int bufnum)
{
	int *q;
	q = buf;
	for (int i = 0; i < bufnum; i++)
	{
		USART_SendByte(USART1, *(q + i));
	}
	
}

int USART1_RX()
{
	/* �ȴ������������� �� RDR ��λ�Ĵ����������Ѵ��䵽 USART_DR �Ĵ���ʱ����λ��Ӳ���� 1��*/
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == 0);
	return USART_ReceiveData(USART1);
}
void out(const char *str)
{
	USART_SendString(USART1, str);
}
void USART1_TXByte(uint8_t ch)
{
	USART_SendByte(USART1, ch);
}

void USART1_TXString(char *str)
{
	USART_SendString(USART1, str);
}

void USART1_TXHalfWord(uint16_t ch)
{
	USART_SendHalfWord(USART1, ch);
}

