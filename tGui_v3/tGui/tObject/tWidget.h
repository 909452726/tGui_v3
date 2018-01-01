#ifndef _TWIDGET_H_
#define _TWIDGET_H_

#include "tObject/tEven.h"
#include "tObject/tPoint.h"
#include "tObject/tSize.h"
#include "tObject/tObject.h"
#include "tContainter/tWidgetList.h"
#include "tPainter/tPainter.h"

class tWidget :public tObject
{
public:
	tWidget(const char* n, tWidget* obj);
	tWidget(int32 x, int32 y, int32 w, int32 h, const char* n, tWidget* obj);
	virtual		~tWidget();
	void		setX(int32 x) { rect->setX(x); }
	void		setY(int32 y) { rect->setY(y); }
	void		setW(int32 w) { rect->setWidth(w); }
	void		setH(int32 h) { rect->setHeight(h); }
	int32		x() { return rect->x(); }
	int32		y() { return rect->y(); }
	int32		width() { return rect->width(); }
	int32		height() { return rect->height(); }
	tRect*		getRect() { return rect; };
	void		setZpos(int32 z) { zpos = z; }
	int32		getZpos() { return zpos; }
	void		setBackColor(colorDef c) { backColor = c; };
	colorDef	getBackColor() { return backColor; }
	void		setOffsetWH(int32 w, int32 h) { offsetWH->setWidth(w); offsetWH->setHeight(h); } //�����븸���ƫ��
	tSize*		getOffsetWH() { return offsetWH; }	
	void		chgChildsXY(tWidget* widget);//�ı��������� -- �����ڶ�
	void		chgInValid(tRect* area1 = NULL , tRect* area2 = NULL); //�޸�/���/ɾ��������
	tWidgetList* getInvalidList() { return invalidList; } 
	bool		isInRealArea(int32 x, int32 y); //��ʵ�����򣬱����Ǻ�ʣ�µ�����
	bool		isInArea(int32 x, int32 y); //�趨������
	void        showAll() { showAll(this); }
	tRect*		getPaintInvaild() { return paintInvaild; }

	virtual void show() =0;
	virtual void eventFilter(tEvent* e);
	virtual void touchPressEvent(tTouchEvent *) {};
	virtual void touchReleaseEvent(tTouchEvent *) {};
	virtual void touchClickEvent(tTouchEvent *) {};
	virtual void touchMoveEvent(tTouchEvent *) {};
	virtual void mousePressEvent(tMouseEvent *) {};
	virtual void mouseReleaseEvent(tMouseEvent *) {};
	virtual void mouseDoubleClickEvent(tMouseEvent *) {};
	virtual void mouseClickEvent(tMouseEvent *) {};
	virtual void mouseMoveEvent(tMouseEvent *) {};
	virtual void keyPressEvent(tKeyEvent *) {};
	virtual void keyReleaseEvent(tKeyEvent *) {};
	virtual void focusInEvent(tFocusEvent *) {};
	virtual void focusOutEvent(tFocusEvent *) {};
	virtual void enterEvent(tEvent *) {};
	virtual void leaveEvent(tEvent *) {};
	virtual void paintEvent(tPaintEvent *) {};
	virtual void moveEvent(tMoveEvent *) {};
	virtual void resizeEvent(tResizeEvent *) {};
	virtual void closeEvent(tCloseEvent *) {};

private:
	tRect*	rect;
	tSize*	offsetWH;//���ݸ����ڵ�point��ƫ��
	tRect*  paintInvaild;//���ػ������
	int32	zpos;
	colorDef   backColor;
	tWidgetList* invalidList;

	void		showAll(tWidget*);
	void		chgAllInValid(tObjList* chdlist, tWidget* area,tRect* area1, tRect* area2);
	void		repaintInvaild(tRect* area1, tRect* area2);
	void		addAchgInvalid(tWidget* area,tRect* area1,tRect* area2);
	void		remInvalid(tWidget* area);
};


#endif // !_TWIDGET_H_

