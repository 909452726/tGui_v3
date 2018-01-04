#include "tObject/tAbstractScrollArea.h"



tAbstractScrollArea::tAbstractScrollArea(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	:tFrame(x,y,w,h,n,obj)
{
	scrollH = NULL;
	scrollV = NULL;
}


tAbstractScrollArea::~tAbstractScrollArea()
{
	delete scrollH;
	delete scrollV;
}

//��ʵ��ȣ���ʵ�߶ȣ��������Ķ̳��ȣ��Ƿ���ˮƽ���������Ƿ�����ֱ������
void tAbstractScrollArea::showScroll(int32 realW, int32 realH, int32 scrollSize, bool hasH, bool hasV)
{
	//ˮƽ������
	if (hasH)
	{
		scrollH = new tScrollBar(x(), y(), width(), scrollSize, NULL, this, true);
		if (realW > width())
			scrollH->setRealLen(width()*width() / realW);
		else
			scrollH->setRealLen(width());
	}
	
	//��ֱ������
	if (hasV)
	{
		scrollV = new tScrollBar(x(), y(), scrollSize, height(), NULL, this, true);
		if (realH > height())
			scrollH->setRealLen(height()*height() / realH);
		else
			scrollH->setRealLen(height());
	}
}