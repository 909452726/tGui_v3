#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f4xx_conf.h"

void DelayMSConfig();
void Delay10USConfig();
void DelayUSConfig();
// Systick�ӳ� ��Ҫ������ʱ��
void DelayHandler(int num);

//��ͨ�ӳ� ѭ���ӳ�
void Delay(__IO uint32_t nCount);

#endif //!_DELAY_H_

