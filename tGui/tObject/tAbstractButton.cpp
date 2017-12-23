#include "tObject/tAbstractButton.h"


void tAbstractButton::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_depress(e->x(), e->y());
};

void tAbstractButton::touchReleaseEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
		sig_release(e->x(), e->y());
};

void tAbstractButton::touchMoveEvent(tTouchEvent *e)
{
	if (state && !isArea(e->x(), e->y()))//�����µ���λ���ֲ��������� ���ͷ�
		release();
};