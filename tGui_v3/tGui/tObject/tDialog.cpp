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
	setIsVariable(true);//����Ϊ�ɱ�״̬
}

tDialog::~tDialog()
{

}

void tDialog::show()
{
	tPainter p(getInvalidList(),getPaintInvaild());
	p.drawDialog(x(), y(), width(), height(), getName(), hasFocus, getBackColor());
	//chgInValid(NULL, NULL);
}

void tDialog::touchPressEvent(tTouchEvent *e)
{
	if (isInRealArea(e->x(), e->y()))
	{
		//���߱����ǵĶ����ػ��ƶ��������
		chgInValid(NULL, NULL);
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
			tWidget* tmp;
			if (getInvalidList()->getFirst()->getParents() != this)//����������  ����������
				getInvalidList()->remove();
			while (tmp = getInvalidList()->getNext())
				if (tmp->getParents() != this)//����������  ����������
					getInvalidList()->remove();
			if (getChildList())//����ֻ�鿴�����û�еݹ�鿴����----------------------------------------
			{
				tmp = (tWidget*)getChildList()->getFirst();
				if(tmp->getInvalidList())
				tmp->getInvalidList()->clear();
				while (tmp = (tWidget*)getChildList()->getNext())
					if (tmp->getInvalidList())
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
		int32 nowX = e->x() - contactOffsetW;
		int32 nowY = e->y() - contactOffsetH;
		tRect r1(preX, preY, width(), height());//������������ �ռ��ƶ������µĿ�϶
		tRect r2(nowX, nowY, width(), height());
		//�ı��Լ�������
		getRect()->moveTopLeft(nowX, nowY);
		//�����ı���������� 
		chgChildsXY(this);
		//������ȫ���������ͼ��
		showAll();
		//�������������ø������  Zpos / �ƶ����油��û��
		restRect(preX, preY, nowX, nowY, r1, r2);
		//���߱����ǵĶ����ػ��ƶ��������
		chgInValid(&r1, &r2);
		//�ı�֮ǰ����
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
			r1.setLeft(preX -1);
			r1.setTop(preY -1);
			r1.setWidth(nowX - preX + 2);
			r1.setHeight(height() + nowY - preY + 2);
			r2.setLeft(preX -1);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width()+1);
			r2.setHeight(preY - nowY + 2);
		}
		else //���·��ƶ�
		{
			r1.setLeft(preX -1);
			r1.setTop(preY -1);
			r1.setWidth(width()+1);
			r1.setHeight(nowY - preY + 2);
			r2.setLeft(preX-1);
			r2.setTop(nowY-1);
			r2.setWidth(nowX - preX + 2);
			r2.setHeight(height() + nowY - preY + 2);
		}
	}
	else
	{
		if (preY > nowY)//���Ϸ��ƶ�
		{
			r1.setLeft(nowX + width() - 1);
			r1.setTop(preY-1);
			r1.setWidth(preX - nowX + 2);
			r1.setHeight(nowY + height() - preY + 2);
			r2.setLeft(preX-1);
			r2.setTop(nowY + height() - 1);
			r2.setWidth(width()+1);
			r2.setHeight(preY - nowY + 2);
		}
		else   //���·��ƶ�
		{
			r1.setLeft(preX-1);
			r1.setTop(preY-1);
			r1.setWidth(width()+1);
			r1.setHeight(nowY - preY +2);
			r2.setLeft(nowX + width() - 1);
			r2.setTop(nowY-1);
			r2.setWidth(preX - nowX + 2);
			r2.setHeight(preY + height() - nowY + 2);
		}
	}
}


