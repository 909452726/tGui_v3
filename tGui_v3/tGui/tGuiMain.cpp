#include "tGuiMain.h"

//�źŶ��Ǵ�root��ʼ�ַ��������Ҫ��ʹ��
void distribute(tEvent* event)
{
	//������

}
static void function()
{
	printf("signal function!\n");
}

static void slotfun()
{
	printf("slot run!\n");
}
void tGuiRun()
{
	printf("hello world!\n");
	//�����¼�����
	tQueue<tEvent*>* queue = new tQueue<tEvent*>();
	//�������ã��������жϵ�ʱ�����,����Event��������
	//driverCall(&queue);
	//ѭ���鿴����
	tEvent e(Event_None);
	queue->enqueue(&e);
	tEvent* tempEvent;
	while (1)
	{
		tempEvent = NULL;
		if (queue->isEmpty())
			continue;
		tempEvent = queue->dequeue();
		distribute(tempEvent);
	}
}