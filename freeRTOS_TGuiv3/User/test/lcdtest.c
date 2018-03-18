#include "lcdtest.h"


/*���ڲ��Ը���Һ���ĺ���*/
void LCDTest(void)
{
	/*��ʾ��ʾ����*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;
	Delay(0xFF);
	/*ʹ�ò�͸��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER);  
	LCD_SetTransparency(0xff);
	
	LCD_Clear(LCD_COLOR_BLACK);	/* ��������ʾȫ�� */

	/*����������ɫ������ı�����ɫ(�˴��ı�������ָLCD�ı����㣡ע������)*/
	LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	  /*ѡ������*/
	LCD_SetFont(&Font16x24);

	LCD_DisplayStringLine(LINE(1), (uint8_t*)"BH 5.0 inch LCD para:");
	LCD_DisplayStringLine(LINE(2), (uint8_t*)"Image resolution:800x480 px");
	LCD_DisplayStringLine(LINE(3), (uint8_t*)"Touch pad:5 point touch supported");
	LCD_DisplayStringLine(LINE(4), (uint8_t*)"Use STM32-LTDC directed driver,");
	LCD_DisplayStringLine(LINE(5), (uint8_t*)"no extern lcd driver needed,RGB888,24bits data bus");
	LCD_DisplayStringLine(LINE(6), (uint8_t*)"Touch pad use IIC to communicate");
  
	
	
	  /*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff, "Display value demo: testCount = %d ", testCNT);
	LCD_ClearLine(LINE(7));
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD_DisplayStringLine(LINE(7), (uint8_t*)dispBuff);

  /* ��ֱ�� */
	LCD_SetTextColor(LCD_COLOR_BLUE);
  
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw line:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawUniLine(50, 250, 750, 250);  
	LCD_DrawUniLine(50, 300, 750, 300);
  
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawUniLine(300, 250, 400, 400);  
	LCD_DrawUniLine(600, 250, 600, 400);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
  
  
	/*������*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw Rect:");
	
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawRect(200, 250, 200, 100);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawRect(350, 250, 200, 50);
	
	LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	LCD_DrawRect(200, 350, 50, 200);
  
	Delay(0xFFFFFF);
  
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
  

	  /*������*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw Full Rect:");

	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawFullRect(200, 250, 200, 100);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawFullRect(350, 250, 200, 50);
	
	LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	LCD_DrawFullRect(200, 350, 50, 200);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	/* ��Բ */
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw circle:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_RED);
	LCD_DrawCircle(200, 350, 50);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_GREEN);
	LCD_DrawCircle(350, 350, 75);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


	  /*���Բ*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw full circle:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawFullCircle(300, 350, 50);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawFullCircle(450, 350, 75);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	LCD_ClearLine(LINE(8));
	
//���ֲ���Ч�����л������󣬲��Ƽ�ʹ�á�һ�㱳�����ʹ��ARGB��ʽ����ɫ�����	
//	/*͸��Ч�� ǰ�������*/
//	{
//		LCD_SetTextColor(LCD_COLOR_BLUE);
//		LCD_ClearLine(LINE(8));
//		LCD_DisplayStringLine(LINE(8),(uint8_t* )"Transparency effect:");
//		
//		/*����ǰ���㲻͸����*/
//		LCD_SetLayer(LCD_FOREGROUND_LAYER); 	
//		LCD_SetTransparency(200);
//		
//		/*��ǰ����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(400,350,75);
//	
//	}
//	
//	/*͸��Ч�� ���������*/
//	{		
//		/*���ñ����㲻͸��*/
//		LCD_SetLayer(LCD_BACKGROUND_LAYER); 	
//		LCD_SetTransparency(0xff);
//		LCD_Clear(LCD_COLOR_BLACK);

//		/*�ڱ�����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(450,350,75);
//		
//		/*�ڱ�����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(350,350,75);
//	}
  
	Delay(0xFFFFFF);
	
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	LCD_SetFont(&Font16x24); 	

	LCD_Clear(LCD_COLOR_BLACK);	/* ��������ʾȫ�� */

	/*����������ɫ������ı�����ɫ(�˴��ı�������ָLCD�ı����㣡ע������)*/
	LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	LCD_DisplayStringLineEx(0, 5, 16, 16, (uint8_t*)"��429 16*16 ", 0);
	LCD_DisplayStringLine_EN_CH(LINE(1), (uint8_t*)"��F429 24*24 ");
	LCD_DisplayStringLineEx(0, 50, 32, 32, (uint8_t*)"��F429 32*32 ", 0);
	LCD_DisplayStringLineEx(0, 82, 48, 48, (uint8_t*)"--F429 48*48 ", 0);
	Delay(0xFFFFFF);

	/*����LCD_SetLayer(LCD_FOREGROUND_LAYER)������
	����Һ����������ǰ����ˢ�£��������µ��ù�LCD_SetLayer�������ñ�����*/		
	//ʹ�ò�͸��ǰ����
	
	
	LCD_SetLayer(LCD_FOREGROUND_LAYER);  
	LCD_SetTransparency(0xff);
	LCD_Clear(LCD_COLOR_YELLOW);	// ��������ʾȫ�� 
	LCD_SetFont(&Font16x24); 
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_RED);
	LCD_DispString_EN_CH(LINE(1),0,"�θ���˧������");
	LCD_DisplayStringLineEx(0, 100, 100, 100, (uint8_t*)"Ϳ�Ŀ��Ǵ�ɵ�ƣ���", 0);
	LCD_DisplayStringLineEx(0, 240, 100, 100, (uint8_t*)"Ҷ���Ҳ�Ǵ�ɵ��", 0);
	
	Delay(0xFFFFFF);


}
