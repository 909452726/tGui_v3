#include "tObject/tDirver.h"

//-----------------------------touchdiver----------------
void tTouchDirver::obtainData()
{
	if (getState())//����
	{
		if (lock)//������(�����ظ���)
		{
			changeLock();
			setType(Event_TouchPress);
			data1 = getTouchX();
			data2 = getTouchY() ;		
		}
		else //֮ǰû����
		{
			setType(Event_None);
			data1 = -1;
			data2 = -1;
		}
		//else if (data1 != *x || data2 != *y) //��������δ����x��y�仯��---���ÿ����ٶ�
		//{
		//	setType(Event_TouchMove);
		//	data1 = *x;
		//	data2 = *y;
		//}
	}
	else //���� �� û����
	{
		if (!lock)  //��֮ǰ�����Ļ���֮ǰ�����ˣ�
		{
			changeLock();
			setType(Event_TouchRelese);
			data1 = getTouchX();
			data2 = getTouchY();
		}
		else //֮ǰû����
		{
			setType(Event_None);
			data1 = -1;
			data2 = -1;
		}
	}
}

