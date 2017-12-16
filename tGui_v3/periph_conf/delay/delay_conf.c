#include "delay/delay_conf.h"

int TimeCount;
/*T INT = VALUE LOAD / CLK AHB-------����ֻ������Value LOAD����
		SystemCoreClock =180MHZ
		SystemCoreClock/1000=1ms
		SystemCoreClock/100000=10us
		SystemCoreClock/1000000=1us
*/

void DelayMSConfig()
{
	SysTick_Config(SystemCoreClock / 1000);
}
void Delay10USConfig()
{
	SysTick_Config(SystemCoreClock / 100000);
}
void DelayUSConfig()
{
	SysTick_Config(SystemCoreClock / 1000000);
}

void DelayHandler(int num)
{
	TimeCount = num;
	while (TimeCount > 0);
	TimeCount = 0;
}



//��ͨ�ӳ�
void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ���� ���Ϊ1/10000ms
{
	for (; nCount != 0; nCount--)
		;
}

