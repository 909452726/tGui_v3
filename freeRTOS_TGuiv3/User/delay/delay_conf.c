#include "delay/delay_conf.h"


/*T INT = VALUE LOAD / CLK AHB-------����ֻ������Value LOAD����
		SystemCoreClock =180MHZ
		SystemCoreClock/1000=1ms
		SystemCoreClock/100000=10us
		SystemCoreClock/1000000=1us
*/

//��ͨ�ӳ�
void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ���� ���Ϊ1/10000ms
{
	for (; nCount != 0; nCount--)
		;
}

