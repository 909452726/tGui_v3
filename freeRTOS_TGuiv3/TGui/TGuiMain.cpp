#include "tGuiMain.h"


void TGuiRun()
{
	// ��Ҫ�ļ���������Ҫ���
	//1.���߳� 
	TTouchDirver dirve;
	TApplication app(&dirve);

	Desktop desk("1:/tgui_pic/desk1.jpg",&app);
	app.addWindow(&desk);
	
	// UserPhoto userphoto("1:/tgui_pic/desk2.jpg",NULL,NULL);
	// app.addWindow(&userphoto);
	//User user("1:/tgui_pic/back2.jpg","user",NULL);
	//app.addWindow(&user);

	app.show(); 
	app.run();
}
