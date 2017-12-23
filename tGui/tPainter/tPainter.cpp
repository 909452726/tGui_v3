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
void tPainter::drawButton(int32 x, int32 y, int32 w, int32 h, const char* str ,bool isPress, colorDef back)
{
	if (isPress)//����
		drawWinShades(x, y, w, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, back);
	else//δ����
		drawWinShades(x, y, w, h, LIGHT, DARK, MIDLIGHT, MIDDARK, back);
	setColors(BLACK,back);
	drawCenterText(x, y, w, h, str);
}

void tPainter::drawCheck(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back )
{
	if (isPress)//����
		drawWinShades(x, y, h, h, LIGHT, DARK, MIDLIGHT, MIDDARK, back);
	else//δ����
		drawWinShades(x, y, h, h, MIDLIGHT, LIGHT, DARK, MIDLIGHT, back);
	if (Selected)
	{
		setColors(BLACK, back);
		drawLine(x + 2, y + h / 2, x + h / 2, y + h - 2);
		drawLine(x + h / 2, y + h - 2, x + h - 2, y + 2);
	}
	setColors(BLACK, back);
	drawCenterText(x+h, y, w-h, h, str);	
}

void tPainter::drawRadio(int32 x, int32 y, int32 w, int32 h, const char* str, bool Selected, bool isPress, colorDef back)
{
	int32 xt, yt, rt;
	xt = x + h / 2;
	yt = y + h / 2;
	rt = h / 2;
	if (isPress)//����
	{
		setColors(MIDDARK, back);
		drawFullCircle(xt, yt, rt);
		setColors(DARK, back);
		drawFullCircle(xt, yt, 3 * rt /4);
		setColors(WHITE, back);
		drawFullCircle(xt, yt, rt / 2);
	}
	else
	{
		setColors(MID, back);
		drawFullCircle(xt, yt, rt);
		setColors(MIDDARK, back);
		drawFullCircle(xt, yt, 3 * rt / 4);
		setColors(WHITE, back);
		drawFullCircle(xt, yt, rt / 2);
	}
	if (Selected)
	{
		setColors(BLACK, back);
		drawFullCircle(xt, yt, rt / 3);
	}
	setColors(BLACK, back);
	drawCenterText(x + h, y, w - h, h, str);
}


void tPainter::drawSlider(int32 x, int32 y, int32 w, int32 h,int32 value, int32 value_pre, bool isPress, colorDef back)
{
	setColors(WHITE, WHITE);
	drawFullRect(x, y, w, h);
	drawWinShades(x, y + h / 3, w, h / 3, MIDDARK, MID, DARK, MIDDARK, MIDLIGHT);//����
	//if(value_pre <0)
	//	
	//else
	//{
	//	//�滭֮ǰ������
	//	
	//}
	//ʵ������
	int32 offset = value*( w / 10)/10 - h * 4/ 6;
	if (offset < 0)offset = 0;
	if (offset >( w - h * 4 / 3))offset = w - h * 4 / 3;
	drawButton(x + offset, y, h * 4 / 3, h, NULL, isPress, back);
	setColors(BLACK, back);
	int32 xstart = x + offset + h * 4 / 3 / 4;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
	xstart = x + offset + h * 4 / 3 / 2;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
	xstart = x + offset + h * 4 / 3  - h * 4 / 3 / 4;
	drawLine(xstart, y + h / 5, xstart, y + h - h / 5);
}

void tPainter::drawCenterText(int32 x, int32 y, int32 w, int32 h, const char* str,  bool isAllShow)
{
	if (!str)
		return;
	int32 len = -1;
	char* p = (char*)str;
	while (p[++len] != '\0')
		;
	
	 x += (w - font->Width*len )/ 2;
	 y += (h - font->Height) / 2;
	if (x < 0 || y < 0)
		//�Զ���С���壬ͨ����������б������Ȳ�������
		return;
	else
		drawDivText(x, y, str, len);
}