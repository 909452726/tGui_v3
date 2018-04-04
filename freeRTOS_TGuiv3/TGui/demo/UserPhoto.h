#ifndef _USER_PHOTO_H_
#define _USER_PHOTO_H_

#ifdef __cplusplus
extern "C" {
#endif
	
// #include <stdio.h>
// #include "stm32f4xx_conf.h"
// #include "fatfs/ff.h"
// #include "interface_conf/tgui_conf.h"
// #include "libraries/picture_lib/piclib.h"	
// #include "libraries/exfuns_lib/exfuns.h"

#ifdef __cplusplus
}
#endif

#include "TPainter/TBufPainter.h"
#include "TWidget/TWindow.h"

#include "TObject/TImage.h"
#include "TWidget/TDialog.h"
#include "TWidget/TWidget.h"
#include "TWidget/TPushButton.h"
#include "TWidget/TCheckBox.h"
#include "TWidget/TRadioButton.h"
#include "TWidget/TLabel.h"
#include "TWidget/TSlider.h"
#include "TWidget/TImageBox.h"
#include "TWidget/TSwitch.h"
#include "TWidget/TIconButton.h"

#include "TGlobal.h"

class UserPhoto :public TWindow
{
public:
	UserPhoto(const char* filename,TApplication* app,const char*  n = NULL, TWidget* obj = NULL);
	virtual ~UserPhoto() ;
	virtual void show();

	void nextPhoto();
	void prevPhoto();
	void closePhoto();

	void scanfile(const char *path);


private:
	TPushButton* close_btn;	
	TPushButton* left_btn;
    TPushButton* right_btn;

	TRect* cleanArea;
	uint8 fileNum;
    uint8 fileName[32][32];
    FILINFO finfo;

	char lfnamebuff[_MAX_LFN];   
	int8 picIndex;
    
	// uint8 res;
 	// DIR picdir;	 		//图片目录
	// FILINFO *picfileinfo;//文件信息 
	// uint8 *pname;			//带路径的文件名
	// uint16 totpicnum; 		//图片文件总数
	// uint16 curindex;		//图片当前索引
	// uint8 key;				//键值
	// uint32 *picoffsettbl;	//图片文件offset索引表 
};

#endif //!_USER_PHOTO_H_
