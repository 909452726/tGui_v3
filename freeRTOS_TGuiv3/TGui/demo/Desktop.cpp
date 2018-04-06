#include "demo/Desktop.h"

Desktop::Desktop(const char* filename,TApplication* app,const char* n, TWidget* obj)
	:TWindow(filename,app,n,obj)
{
	set_dialog = NULL;
    calcu_dialog = NULL;
    date_dialog = NULL;
    timer_dialog = NULL;


    icon_clock = new TIconButton(20,40,new TImage("1:/tgui_pic/clock.png"),NULL/*new TImage("1:/tgui_pic/clock2.png")*/,"ʱ��",this);
    icon_date = new TIconButton(222,45,new TImage("1:/tgui_pic/date.png"),NULL/*new TImage("1:/tgui_pic/date2.png")*/,"����",this);
    icon_setting = new TIconButton(409,40,new TImage("1:/tgui_pic/setting.png"),NULL/*new TImage("1:/tgui_pic/setting2.png")*/,"����",this);
    icon_calculator = new TIconButton(599,45,new TImage("1:/tgui_pic/calculator.png"),NULL/*new TImage("1:/tgui_pic/calculator2.png")*/,"������",this);
    
    icon_photo = new TIconButton(20,260,new TImage("1:/tgui_pic/photo.png"),NULL /*new TImage("1:/tgui_pic/photo2.png")*/,"��Ƭ",this);
    icon_play = new TIconButton(245,260,new TImage("1:/tgui_pic/play.png"),NULL /*new TImage("1:/tgui_pic/play2.png")*/,"������",this);
    icon_search = new TIconButton(420,260,new TImage("1:/tgui_pic/search.png"),NULL/*new TImage("1:/tgui_pic/search2.png")*/,"����",this);
    icon_game = new TIconButton(599,260,new TImage("1:/tgui_pic/imac.png"),NULL/*new TImage("1:/tgui_pic/weather2.png")*/,"��Ϸ",this);
	
    icon_clock->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openTimer));
    icon_date->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openDate));
    icon_setting->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openSetup));
    icon_calculator->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openCalculate));
    icon_photo->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openPhoto));
	icon_game->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openGame));
    
}

Desktop::~Desktop() 
{
}

void Desktop::show()
{
    // if(icon_clock == NULL)
    //     createIcon();
	refresh();
}

void Desktop::openSetup()
{
    if(!set_dialog)
    {
       // delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        showAll();
        delete imgbox;

        set_dialog = new TDialog(250, 100, new TImage("1:/tgui_pic/dialog.png"), "����", this,55);
	    TPushButton*  btn1 = new TPushButton(292, 234, new TImage("1:/tgui_pic/dialog_btn1.png"),new TImage("1:/tgui_pic/dialog_btn1_sel.png"),"ȷ��",set_dialog);
	    TPushButton*  btn2 = new TPushButton(442, 234,new TImage("1:/tgui_pic/dialog_btn2.png"),new TImage("1:/tgui_pic/dialog_btn2_sel.png"),"ȡ��",set_dialog);
        btn1->connect((func)(&TPushButton::sig_release),this,(func)(&Desktop::closeSetup));
        set_dialog->showAll();
    }
}

void Desktop::closeSetup()
{
    getApp()->setSignal(set_dialog,Event_Close);
    set_dialog = NULL;
}

void Desktop::openCalculate()
{
    if(!calcu_dialog)
    {
        //delete date_dialog;
        //delete set_dialog; //��������dialogɾ��
        
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
        delete(imgbox);

        calcu_dialog = new UserCalculate(224,17,new TImage("1:/calculate_pic/calculator.png"),NULL,this,65);
        calcu_dialog->showAll();
    }
    else//�ٰ�һ�� ��ɾ��
    {
        delete calcu_dialog;
        calcu_dialog = NULL;
        showAll();
    }
}


void Desktop::openDate()
{
    if(!date_dialog)
    {
        //delete calcu_dialog; 
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();//showAll();
        delete(imgbox);

        date_dialog = new UserCalendar(271,118,new TImage("1:/calendar_pic/calendar.png"),NULL,this,55);
        date_dialog->showAll();
    }
    else//�ٰ�һ�� ��ɾ��
    {
        delete date_dialog;
        date_dialog = NULL;
        showAll();
    }
}   

void Desktop::openTimer()
{
    if(!timer_dialog)
    {
        TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
        delete(imgbox);

        timer_dialog = new UserTime(225,116,new TImage("1:/time_pic/time_dialog.png"),NULL,this,55);
        timer_dialog->showAll();
    }
    else//�ٰ�һ�� ��ɾ��
    {
        delete timer_dialog;
        timer_dialog = NULL;
        showAll();
    }
}

void Desktop::openGame()
{
    TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
    imgbox->show();
    delete(imgbox);

    //deleteIcon();

    //---������Ϸ����-----
    UserGame* usergame = new UserGame("1:/game_pic/GameBack.jpg",getApp());
    getApp()->setSignal(usergame,Event_Show);
}


void Desktop::openPhoto()
{
    TImageBox* imgbox = new TImageBox(370,195,new TImage("1:/tgui_pic/wait.png"),2,NULL,this);
        imgbox->show();
    delete(imgbox);

    //deleteIcon();

    UserPhoto* userphoto = new UserPhoto("1:/tgui_pic/desk2.jpg",getApp());
    getApp()->setSignal(userphoto,Event_Show);
}

void Desktop::createIcon()
{
    icon_clock = new TIconButton(20,40,new TImage("1:/tgui_pic/clock.png"),NULL/*new TImage("1:/tgui_pic/clock2.png")*/,"ʱ��",this);
    icon_date = new TIconButton(222,45,new TImage("1:/tgui_pic/date.png"),NULL/*new TImage("1:/tgui_pic/date2.png")*/,"����",this);
    icon_setting = new TIconButton(409,40,new TImage("1:/tgui_pic/setting.png"),NULL/*new TImage("1:/tgui_pic/setting2.png")*/,"����",this);
    icon_calculator = new TIconButton(599,45,new TImage("1:/tgui_pic/calculator.png"),NULL/*new TImage("1:/tgui_pic/calculator2.png")*/,"������",this);
    
    //icon_photo = new TIconButton(20,260,new TImage("1:/tgui_pic/photo.png"),NULL /*new TImage("1:/tgui_pic/photo2.png")*/,"��Ƭ",this);
    icon_play = new TIconButton(245,260,new TImage("1:/tgui_pic/play.png"),NULL /*new TImage("1:/tgui_pic/play2.png")*/,"������",this);
    icon_search = new TIconButton(420,260,new TImage("1:/tgui_pic/search.png"),NULL/*new TImage("1:/tgui_pic/search2.png")*/,"����",this);
    //icon_game = new TIconButton(599,260,new TImage("1:/tgui_pic/imac.png"),NULL/*new TImage("1:/tgui_pic/weather2.png")*/,"��Ϸ",this);
	
    //icon_photo->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openPhoto));
    icon_setting->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openSetup));
	//icon_game->connect((func)(&TIconButton::sig_release),this,(func)(&Desktop::openGame));
}

void Desktop::deleteIcon()
{
    delete( icon_clock);
    delete( icon_date );
    delete( icon_setting);
    delete( icon_calculator) ;
    //delete( icon_photo ;
    delete( icon_play );
    delete( icon_search) ;
    //delete( icon_game ;
    
    icon_clock = NULL;
    icon_date = NULL;
    icon_setting = NULL;
    icon_calculator = NULL;
    //icon_photo = NULL;
    icon_play = NULL;
    icon_search = NULL;
    //icon_game = NULL;
}








