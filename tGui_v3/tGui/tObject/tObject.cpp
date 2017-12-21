#include "tObject/tObject.h"


//-----------------------------OBJECT-------------------------
tObject::tObject(tString* n , tObject* obj )
{
	name = n;
	parents = obj;
	childList = NULL;
	connections = NULL;
}
tObject::~tObject()
{
	destroyChild(this);
	delete childList;
	if (connections)
	{
		connections->setAutoDelete(true);
		connections->clear();
	}
	if (name)
		delete name;
}

void tObject::setName(const char* str) 
{ 
	if(!name)
		name = new tString(str);
	else
		name->setStr(str);
}


bool tObject::connect(func  sig, tObject* receiver, func  slot)
{
	if (!connections)
		connections = new tConnectList();
	int32 num = connections->find(sig);//���Ҫ�ȱ���һ��֮ǰ�Ƿ����ź�
	if (num >= 0)//����
	{//���Ҫ�ȱ���һ��֮ǰ�Ƿ��в�
		tFuncList* funclist = connections->at(num)->slotList;
		tObjList* objlist = connections->at(num)->recvList;
		if (funclist->find(slot) < 0)
		{
			funclist->append(slot);
			objlist->append(receiver);
		}
	}
	else//������
	{
		connection* con = new connection(sig, receiver,slot);
		if (!con)
			return false;
		connections->append(con);
	}
	return true;
}

bool tObject::disconnect(func  sig, tObject* receiver, func  slot)
{
	if (!connections)
		return true;
	int32 num = connections->find(sig);
	if (num >= 0)//����
	{
		tFuncList* funclist = connections->at(num)->slotList;
		tObjList* objlist = connections->at(num)->recvList;
		funclist->remove(slot);
		objlist->remove(receiver);
	}
	return true;
}

void tObject::unlink(tObject* obj)
{
	if (!(obj->getParents()))
		return;
	obj->getParents()->getChildList()->unlink(obj);
}


void tObject::addChild(tObject* child)
{
	if (!childList)
		childList = new tObjList();
	//���
	if((childList->find(child)) < 0)
		childList->append(child);
}

void tObject::remChild(tObject* child)
{
	if (!childList)
		return;
	//���--��û�к���
	destroyChild(child);
	//ɾ��
	childList->remove(child);
}

void tObject::destroyChild(tObject* obj)
{
	if (obj->childList)
	{	
		destroyChild(obj->childList->getLast());
		delete(obj->childList->getLast());
		obj->childList->removeLast();
	}
}


