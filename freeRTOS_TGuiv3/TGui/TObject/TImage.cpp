#include "TObject/TImage.h"

//图像png加载出来一定是8888的格式

//fast for png need imgload
 TImage::TImage(const char* filename)  
 {
    this->filename = filename;
    imgBufAddr = NULL;
	imgType = 0;
    Decode();			//解码 并 根据图片来确定Image类的参数大小
 }

//fast for bmp/jpg need have buf
TImage::TImage(TBuffer* buf,uint16 w,uint16 h,const char* filen) 
{
	imgBufAddr = NULL;
	unsigned int wpng,hpng;
	this->filename = filen;
	imgType = ObFileType(filename);	//得到文件的类型
	switch(imgType)
	{	
		case T_PNG:
		{
			lodepng_decode32_file(&imgBufAddr, &wpng, &hpng, filename);			//解码png	  
			width = wpng;
			height = hpng;
			if(buf->getBufW()  < width  || buf->getBufH()  < height)
				return ;
			ImgBlendLoad(0,0,buf);
		}break;								  
		case T_JPG:
		case T_JPEG:
		case T_BMP:
			piclib_init(buf->getBufAddr(),w,h);		
			ai_load_picfile(filename,0,0,w,h,1);
			break;
		case T_GIF: 
				
			break;
		default:
	 		//res = PIC_FORMAT_ERR;  													//非图片格式!!!  
			break;
	}
}

 TImage::~TImage()
 {
     if(imgBufAddr)
        free(imgBufAddr);
 }


void TImage::Decode()
{
	uint8 res = 0;
	unsigned int wpng,hpng;
    imgType = ObFileType(filename);	//得到文件的类型
    switch(imgType)
	{											  
		case T_JPG:
		case T_JPEG:
			res = jpg_decode_file(&imgBufAddr, &width, &height, filename);				//解码JPG/JPEG	 
			break;
		case T_PNG:
  			res = lodepng_decode32_file(&imgBufAddr, &wpng, &hpng, filename);			//解码png	  
			width = wpng;
			height = hpng;
			break;
		case T_BMP:
			res = bmp_decode_file(&imgBufAddr, &width, &height, filename); 				//解码bmp	    	  
			break;
		case T_GIF:                    //先不实现 需要对有TIM
			//res = gif_decode(filename,x,y,width,height);								//解码gif  	    -->需要把 bufaddr ， width ，height 获取过来
			break;
		default:
	 		//res = PIC_FORMAT_ERR;  													//非图片格式!!!  
			break;
	}  	
	if(res)
		printf("\r\n>> decode is failed! the num is %d\r\n",res	);
}



void TImage::ImgLoad(int32 offX, int32 offY,TBuffer* buf)
{
	if(buf->getBufW()  < width + offX )
		return ;
	if(buf->getBufH()  < height + offY)
		return ;
	if(imgType == T_PNG ) 
	{
		ImgBlendLoad(offX,offY,buf);
	}
	else		//其他图片解码都是经过 gui 的绘图函数填充的 ，所以可以直接覆盖即可--快
	{
		uint8* des_addr = buf->getBufAddr() + (offX + offY * buf->getBufW()) * GUI_PIXELSIZE;
		uint8* src_addr = imgBufAddr;
		for(int i = 0;i < height;  i++)
		{
			gui_memcpy(des_addr,src_addr,width * GUI_PIXELSIZE);
			src_addr += width * GUI_PIXELSIZE;
			des_addr += buf->getBufW() * GUI_PIXELSIZE;
		}
	}
}



//混合
// readAddr:	开始 读 的地址
// readSize:	被 读 的区域所在的buf大小
// writeAddr:	开始 写 的地址
// writeSize:	被 写 的区域所在的buf大小
// imgRect:		图片混合的区域

void TImage::ImgBlendLoad(uint8* readAddr,TSize* readSize,uint8* writeAddr,TSize* writeSize,TRect* imgTRect)
{
	TRect* imgRect = imgTRect;
	if(imgTRect == NULL) //null 就是全部 
	{
		TRect r(0,0,imgW(),imgH());
		imgRect = &r;
	}
		 
	if(readSize->width() < imgRect->width() || readSize->height() < imgRect->height() ||
		 writeSize->height() < imgRect->height() ||writeSize->width() < imgRect->width() )
		return;

	if(imgType == T_PNG )
	{
		uint32 point ,color = 0;
		uint8* imgaddr = imgBufAddr;
		uint8  a = 255; //前景透明色
		uint32 r,g,b; 
		uint32 offF = (imgRect->x() + imgRect->y() * width)*GUI_PIXELSIZE; //开始的地址
		if(imgType == T_PNG) //RGBA
		{
			for(int i=0;i<imgRect->height();i++)
			{
				for(int j=0;j< imgRect->width() ;j++)
				{
					point = *(readAddr + (j + i * readSize->width()) * GUI_PIXELSIZE); //读point

					a = imgaddr[offF + 3];
					r = imgaddr[offF];
					g = imgaddr[offF + 1];
					b = imgaddr[offF + 2];
					color |= point & 0xff000000;
					color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
					color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
					color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

					*(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE) = color; //写point

					color = 0;
					offF += GUI_PIXELSIZE;
				}
				offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
			}
		}
		else //ARGB
		{
			for(int i=0;i< imgRect->height();i++)
			{
				for(int j=0;j< imgRect->width();j++)
				{
					point = *(readAddr +  (j + i * readSize->width()) * GUI_PIXELSIZE);//读point

					a = imgaddr[offF];
					r = imgaddr[offF + 1];
					g = imgaddr[offF + 2];
					b = imgaddr[offF + 3];
					color |= point & 0xff000000;
					color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
					color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
					color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);

					*(writeAddr + (j + i * writeSize->width()) * GUI_PIXELSIZE) = color;//写point

					color = 0;
					offF += GUI_PIXELSIZE;
				}
				offF +=  (width - imgRect->width() ) * GUI_PIXELSIZE;
			}
		}
	}
}

void TImage::ImgLoad(int32 offX, int32 offY)
{
	if(GUI_WIDTH  < width + offX )
		return ;
	if(GUI_HIGH < height + offY)
		return ;
	if(imgType == T_PNG ) 
	{
		ImgBlendLoad(offX,offY);
	}
	else		//其他图片解码都是经过 gui 的绘图函数填充的 ，所以可以直接覆盖即可--快
	{
		uint8* des_addr = (uint8*)GUI_FG_BUFADDR + (offX + offY * GUI_WIDTH) * GUI_PIXELSIZE;
		uint8* src_addr = imgBufAddr;
		for(int i = 0;i < height;  i++)
		{
			gui_memcpy(des_addr,src_addr,width * GUI_PIXELSIZE);
			src_addr += width * GUI_PIXELSIZE;
			des_addr += GUI_WIDTH * GUI_PIXELSIZE;
		}
	}
}


void TImage::ImgLoad(int32 offX, int32 offY,int32 ndW, int32 ndH,TBuffer* buf)
{
	if(buf->getBufW()  < width + offX )
		return ;
	if(buf->getBufH()  < height + offY)
		return ;
	if(ndW > width)
		ndW = width;
	if(ndH > height)
		ndH = height;

	if(imgType == T_PNG ) 
	{
		ImgBlendLoad(offX,offY,ndW,ndH,buf);	
	}
	else		//其他图片解码都是经过 gui 的绘图函数填充的 ，所以可以直接覆盖即可--快
	{
		uint8* des_addr = buf->getBufAddr() + (offX + offY * buf->getBufW()) * GUI_PIXELSIZE;
		uint8* src_addr = imgBufAddr;
		for(int i = 0;i < ndH;  i++)
		{
			gui_memcpy(des_addr,src_addr,ndW * GUI_PIXELSIZE);
			src_addr += ndW * GUI_PIXELSIZE;
			des_addr += buf->getBufW() * GUI_PIXELSIZE;
		}
	}
}

//只针对于 ARGB8888
void TImage::ImgBlendLoad(int32 offX, int32 offY,TBuffer* buf)
{

#if defined ARGB_8888
	uint32 point ,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 
	uint32 offF = 0;
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				point = buf->readPoint(j + offX,i + offY);
				a = imgaddr[offF + 3];
				r = imgaddr[offF];
				g = imgaddr[offF + 1];
				b = imgaddr[offF + 2];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				buf->writePoint(j + offX,i + offY,color);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
		}
	}
	else //ARGB
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				point = buf->readPoint(j + offX,i + offY);
				a = imgaddr[offF];
				r = imgaddr[offF + 1];
				g = imgaddr[offF + 2];
				b = imgaddr[offF + 3];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				buf->writePoint(j + offX,i + offY,color);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
		}
	}
#elif defined  ARGB_1555


#endif
}

void TImage::ImgBlendLoad(int32 offX, int32 offY)
{
#if defined ARGB_8888
	uint32 point ,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 
	uint32 offF = 0;
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				point =  *(uint32_t* )(((uint32)GUI_FG_BUFADDR) + ((i + offY) * GUI_WIDTH + j + offX) * GUI_PIXELSIZE);
				a = imgaddr[offF + 3];
				r = imgaddr[offF];
				g = imgaddr[offF + 1];
				b = imgaddr[offF + 2];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				gui_set_rect((uint32_t*)GUI_FG_BUFADDR,GUI_WIDTH,color,j + offX, i + offY ,1,1);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
		}
	}
	else //ARGB
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				point =  *(uint32_t* )(((uint32)GUI_FG_BUFADDR) + ((i + offY )* GUI_WIDTH + j + offX) * GUI_PIXELSIZE);
				a = imgaddr[offF];
				r = imgaddr[offF + 1];
				g = imgaddr[offF + 2];
				b = imgaddr[offF + 3];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				gui_set_rect((uint32_t*)GUI_FG_BUFADDR,GUI_WIDTH,color,j + offX , i + offY ,1,1);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
		}
	}
#elif defined  ARGB_1555


#endif 


}




void TImage::ImgBlendLoad(int32 offX, int32 offY,int32 ndW, int32 ndH,TBuffer* buf)
{

#if defined ARGB_8888
	uint32 point ,color = 0;
	uint8* imgaddr = imgBufAddr;
	uint8  a = 255; //前景透明色
	uint32 r,g,b; 
	uint32 offF = 0;
	if(imgType == T_PNG) //RGBA
	{
		for(int i=0;i<ndH;i++)
		{
			for(int j=0;j<ndW;j++)
			{
				point =    buf->readPoint(j + offX,i + offY);
				a = imgaddr[offF + 3];
				r = imgaddr[offF];
				g = imgaddr[offF + 1];
				b = imgaddr[offF + 2];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				buf->writePoint(j + offX,i + offY,color);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
				offF += (width - ndW  ) * GUI_PIXELSIZE;
		}
	}
	else //ARGB
	{
		for(int i=0;i<ndH;i++)
		{
			for(int j=0;j<ndW;j++)
			{
				point = buf->readPoint(j + offX,i + offY);
				a = imgaddr[offF];
				r = imgaddr[offF + 1];
				g = imgaddr[offF + 2];
				b = imgaddr[offF + 3];
				color |= point & 0xff000000;
				color |= ((((point >> 16) & 0xff)  * (0xff - a) + r * a)  >> 8) << 16;
				color |= ((((point >> 8) & 0xff ) * (0xff - a) + g * a)  >> 8) << 8;
				color |= (((point & 0xff) * (0xff - a) + b * a)  >> 8);
				buf->writePoint(j + offX,i + offY,color);
				color = 0;
				offF += GUI_PIXELSIZE;
			}
				offF += (width - ndW ) * GUI_PIXELSIZE;
		}
	}
#elif defined  ARGB_1555


#endif


}


uint8 TImage::ObFileType(const char *filename)
{
	uint8 *fname = (uint8 *)filename;
	uint8 tbuf[5];
	uint8 *attr='\0';//后缀名
	uint8 i=0;
	while(i<250)
	{
		i++;
		if(*fname=='\0')
			break;//偏移到了最后了.
		fname++;
	}
	if(i==250)return 0XFF;//错误的字符串.
 	for(i=0;i<5;i++)//得到后缀名
	{
		fname--;
		if(*fname=='.')
		{
			fname++;
			attr=fname;
			break;
		}
  	}
	strcpy((char *)tbuf,(const char*)attr);//copy
 	for(i=0;i<4;i++)
	 	tbuf[i] = UPPER(tbuf[i]);//全部变为大写 
	if(strcmp("JPG",(const char *)tbuf)==0)
		return 0x0f;
	else if(strcmp("JPEG",(const char *)tbuf)==0)
		return 0x1f;
	else if(strcmp("PNG",(const char *)tbuf)==0)
		return 0x2f;
	else if(strcmp("BMP",(const char *)tbuf)==0)
		return 0x3f;
	else if(strcmp("GIF",(const char *)tbuf)==0)
		return 0x4f;
	else
		return 0Xff;  //没找到	 			   
}	 





