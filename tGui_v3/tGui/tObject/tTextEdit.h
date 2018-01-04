#ifndef _TTEXTEDIT_H_
#define _TTEXTEDIT_H_

#include "tContainter/tString.h"
#include "tContainter/tStrList.h"

class tTextEdit
{
public:
	tTextEdit();
	~tTextEdit();

	tString* getIndex(int32 x);//��ȡ��x���ַ���
	void getCursor(int32 *pLine = NULL, int32 *pOffset = NULL) const;
	void moveCursor(int32 offset);
	void setCursor(int32 line, int32 offset);
	void addText( tString * text);
	void insertText(tString* text);
	void findTextInAll( tString * text,int32 *line, int32 *offset);
	void deleteText( tString &text);
	void deleteText(int32 cursor, int32 pos, int32 length);
	void saveFile();

private:
	int32 curLine;	//��������
	int32 offset;	//ƫ��
	int32 lineNum;	//����
	int32 total;	//����
	int32 letters;	//��ĸ��
	int32 nums;		//������
	int32 spaces;	//�ո���
	int32 quots;	//����λ��

	tStrList* strList;
};


#endif // !_TTEXTEDIT_H_


