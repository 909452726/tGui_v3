#include "sdramtest.h"

/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));

void SDRAM_Demo()
{
	/*��SDRAM���ж�д���ԣ����SDRAM�Ƿ�����*/
	if (SDRAM_Test() == 1)
	{
		  //�������� �̵���
		LED_GREEN_ON();			  
	}
	else
	{
		//����ʧ�� �����
		LED_RED_ON();
	}
	
	//ָ�뷽ʽ����SDRAM
	{	
		uint32_t temp;
	
		printf("\r\npoint way to visit SDRAM\r\n");
	   //��SDRAMд��8λ����
		*(uint8_t*)(SDRAM_BANK_ADDR) = (uint8_t)0xAA;
		printf("\r\nponit visit SDRAM,write data 0xAA \r\n");

			 //��SDRAM��ȡ����
		temp =  *(uint8_t*)(SDRAM_BANK_ADDR);
		printf("read data: 0x%X \r\n", temp);

			 //д/�� 16λ����
		*(uint16_t*)(SDRAM_BANK_ADDR + 10) = (uint16_t)0xBBBB;
		printf("ponit visit SDRAM,write data 0xBBBB \r\n");
	 
		temp =  *(uint16_t*)(SDRAM_BANK_ADDR + 10);
		printf("read data:0x%X \r\n", temp);


			 //д/�� 32λ����
		*(uint32_t*)(SDRAM_BANK_ADDR + 20) = (uint32_t)0xCCCCCCCC;
		printf("ponit visit SDRAM,write data 0xCCCCCCCC \r\n");	 
		temp =  *(uint32_t*)(SDRAM_BANK_ADDR + 20);
		printf("read data:0x%X \r\n", temp);

	}

	//���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���
	{
		testValue = 0xDD;
		printf("\r\nAbsolute positioning access SDRAM, write data 0xDD, read data 0x%X, variable address for %X\r\n", testValue, (uint32_t)&testValue);	 
	}
	
	
}