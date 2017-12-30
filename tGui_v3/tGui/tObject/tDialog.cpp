#include "tDialog.h"



tDialog::tDialog(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj)
	:tWidget(x, y, w, h, n, obj)
{
	contactOffsetW = -1;
	contactOffsetH = -1;
	preX = -1;
	preY = -1;
	state = false;
	hasFocus = true;
}

tDialog::~tDialog()
{

}

void tDialog::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawDialog(x(), y(), width(), height(), getName(), true);
}

void tDialog::touchPressEvent(tTouchEvent *e)
{
	if (isArea(e->x(), e->y()))
	{//�������ڣ���֮ǰΪʧȥ����ģ����¼��Ͻ���
		if (!hasFocus)
		{
			state = true;
			hasFocus = true;
			tPainter p(getInvalidList(),getPaintInvaild());
			p.drawDialogTitle(x(), y(), width(), getName(), true);
		}
		if ( e->x() < (x() + width()) &&  e->y() < (y() + WIN_TITLE_H))
		{
			state = true;
			contactOffsetW = e->x() - x();
			contactOffsetH = e->y() - y();
			preX = x();
			preY = y();
		}
	}
	else if(hasFocus)
	{
		hasFocus = false;
		tPainter p(getInvalidList(), getPaintInvaild());
		p.drawDialogTitle(x(), y(), width(), getName(), false);
	}
};

void tDialog::touchReleaseEvent(tTouchEvent *e)
{
	state = false;
	contactOffsetW = -1;
	contactOffsetH = -1;
};

void tDialog::touchMoveEvent(tTouchEvent *e)
{
	if (state && contactOffsetW != -1)
	{ 
		//�ı��Լ�������
		getRect()->moveTopLeft(e->x() - contactOffsetW, e->y() - contactOffsetH);
		//�����ı���������� 
		chgChildsXY(this);
		//�������������ø������  Zpos / �ƶ����油��û��

	/*		|---------|
		|---|-----|	  |
		|	|	  |	  |
		|	|-----|---|
		|---------|*/
		tRect r1(preX,preY,width(),height());//�ռ��ƶ������µĿ�϶Ϊ�������ι���
		tRect r2;
		//chgInValid(&r1, NULL);
		if (e->x() >= preX)
		{
			if (preY > e->y())//���Ϸ��ƶ�
			{
				r1.setLeft(preX);
				r1.setTop(preY);
				r1.setWidth(e->x() - preX + 1);
				r1.setHeight(height() + e->y() - preY + 1);
				r2.setLeft(preX);
				r2.setTop(e->y() + height() - 1);
				r2.setWidth(width());
				r2.setHeight(preY - e->y() + 1);
			}
			else//���Ϸ��ƶ�
			{
				r1.setLeft(preX);
				r1.setTop(preY);
				r1.setWidth(width());
				r1.setHeight(e->y() - preY + 1);
				r2.setLeft(preX);
				r2.setTop(e->y());
				r2.setWidth(e->x() - preX + 1);
				r2.setHeight(height() + e->y() - preY + 1);
			}
		}
		else
		{
			if (preY > e->y())//���Ϸ��ƶ�
			{
				r1.setLeft(preX + width() - e->x() - 1);
				r1.setTop(preY);
				r1.setWidth(preX - e->x() + 1);
				r1.setHeight(e->y() + height() - preY + 1);
				r2.setLeft(preX);
				r2.setTop(e->y() + height() - 1);
				r2.setWidth(width());
				r2.setHeight(preY - e->y() + 1);
			}
			else  //���·��ƶ�
			{
				r1.setLeft(preX);
				r1.setTop(preY);
				r1.setWidth(width());
				r1.setHeight(e->y() - preY + 1);
				r2.setLeft(e->x() + width() - 1);
				r2.setTop(e->y());
				r2.setWidth(e->x() - preX + 1);
				r2.setHeight(preY + height() - e->y() + 1);
			}
		}
		if (!r1.isValid() && !r2.isValid())
		chgInValid();
		else if (!r1.isValid())
		chgInValid(NULL, &r2);
		else if (!r2.isValid())
		chgInValid(&r1, NULL);
		else
		chgInValid(&r1, &r2);
		//������ȫ���������ͼ��
		showAll();
		//���߱����ǵĶ����ػ��ƶ��������
		preX = e->x();
		preY = e->y();
	}
};





