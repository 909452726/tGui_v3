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
	setBackColor(MIDLIGHT);
}

tDialog::~tDialog()
{

}

void tDialog::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawDialog(x(), y(), width(), height(), getName(), hasFocus, getBackColor());
}

void tDialog::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
	{
		//�������ڣ���֮ǰΪʧȥ����ģ����¼��Ͻ���
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
		if (getInvalidList())//��������и�����
		{
			getInvalidList()->clear();//��������
			tObjList* list = getChildList(); //����ֻ�鿴�����û�еݹ�鿴����
			if (list)	
			{
				tWidget* tmp;
				tmp = (tWidget*)list->getFirst();
				tmp->getInvalidList()->clear();
				while (tmp = (tWidget*)list->getNext())
					tmp->getInvalidList()->clear();
			}
			showAll();//�ػ�  -------��֤�����
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
		
		//������ȫ���������ͼ��
		showAll();
		//�������������ø������  Zpos / �ƶ����油��û��
		
		int32 nowX = e->x() - contactOffsetW;
		int32 nowY = e->y() - contactOffsetH;
		tRect r1(preX, preY, width(), height());//�ռ��ƶ������µĿ�϶Ϊ�������ι���
		tRect r2(nowX, nowY, width(), height());
		restRect(preX, preY, nowX, nowY, r1, r2);
		chgInValid(&r1, &r2);
		//���߱����ǵĶ����ػ��ƶ��������
		preX = nowX;
		preY =nowY;
	}
};


//�ƶ����ͷŵ�����  
void tDialog::restRect(int32 preX, int32 preY, int32 nowX, int32 nowY ,tRect &r1, tRect &r2)
{
	//chgInValid(&r1, NULL); //����dialogˢ��
	/*	|---------|
	|---|-----|	  |
	|	|	  |	  |
	|	|-----|---|
	|---------|*/
	if (nowX > preX)
	{
		if (preY > nowY)//���Ϸ��ƶ�
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(nowX - preX + 1);
			r1.setHeight(height() + nowY - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width());
			r2.setHeight(preY - nowY + 1);
		}
		else //���·��ƶ�
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(width());
			r1.setHeight(nowY - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY);
			r2.setWidth(nowX - preX + 1);
			r2.setHeight(height() + nowY - preY + 1);
		}
	}
	else
	{
		if (preY > nowY)//���Ϸ��ƶ�
		{
			r1.setLeft(nowX + width() - 1);
			r1.setTop(preY);
			r1.setWidth(preX - nowX + 1);
			r1.setHeight(nowY + height() - preY + 1);
			r2.setLeft(preX);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width());
			r2.setHeight(preY - nowY + 1);
		}
		else   //���·��ƶ�
		{
			r1.setLeft(preX);
			r1.setTop(preY);
			r1.setWidth(width());
			r1.setHeight(nowY - preY + 1);
			r2.setLeft(nowX + width() - 1);
			r2.setTop(nowY);
			r2.setWidth(preX - nowX + 1);
			r2.setHeight(preY + height() - nowY + 1);
		}
	}
}


