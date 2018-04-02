#include "demo/UserPhoto.h"

UserPhoto::UserPhoto(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	
    left_btn = new TPushButton(100,400,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"��һ��", this);
    right_btn = new TPushButton(600,400,new TImage("1:/tgui_pic/button.png"),new TImage("1:/tgui_pic/button_sel.png"),"��һ��", this);
	
    right_btn->connect((func)(&TPushButton::sig_release),this,(func)(&UserPhoto::slot_close));
}

UserPhoto::~UserPhoto() 
{
	
}

void UserPhoto::show()
{
	refresh();
}


