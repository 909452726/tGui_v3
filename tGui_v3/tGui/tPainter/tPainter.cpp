#include "tPainter/tPainter.h"


tPainter::tPainter()
{
	font = &Font16x24;
	textcolor = 0;
	backcolor = 0;
}

void tPainter::setColors(colorDef text, colorDef back)
{
	textcolor = text;
	backcolor = back; 
	setDivColor(text, back); 
};
/**
* ���ڻ�ͼ���� ���ڴ��ںͰ���
*/
void tPainter::drawWinShades(int32 x, int32 y, int32 w, int32 h,
	colorDef c1, colorDef c2, colorDef c3, colorDef c4, colorDef back)
{
	setTextColor(c1); //�����
	drawDivLine(x, y + h - 2, x, y);
	drawDivLine(x, y, x + w - 2, y);
	setTextColor(c2);//�����
	drawDivLine( x, y + h - 1, x + w - 1, y + h - 1);
	drawDivLine( x + w - 1, y + h - 1, x + w - 1, y);
	setTextColor(c3);//���ڿ�
	drawDivLine(x + 1, y + h - 3, x + 1, y + 1);
	drawDivLine(x + 1, y + 1, x + w - 3, y + 1);
	setTextColor(c4);//���ڿ�
	drawDivLine(x + 1, y + h - 2, x + w - 2, y + h - 2);
	drawDivLine(x + w - 2, y + h - 2, x + w - 2, y + 1);
	setTextColor(back);
	drawDivFullRect(x + 2 , y + 2, w - 4, h - 4);
}

//button isPress ��ʾ�Ƿ���״̬
void tPainter::drawButton(int32 x, int32 y, int32 w, int32 h, const char* str, int32 len ,bool isPress, colorDef back)
{
	if (isPress)//����
		drawWinShades(x, y, w, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, back);
	else//δ����
		drawWinShades(x, y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, back);
	setColors(BLACK,back);
	drawCenterText(x, y, w, h, str, len);
}

void tPainter::drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str, int32 len, bool isAllShow)
{
	 x += (w - font->Width*len )/ 2;
	 y += (h - font->Height) / 2;
	if (x < 0 || y < 0)
		//�Զ���С���壬ͨ����������б������Ȳ�������
		return;
	else
		drawDivText(x, y, str, len);
}