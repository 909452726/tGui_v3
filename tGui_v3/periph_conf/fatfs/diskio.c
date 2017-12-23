/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "fatfs/diskio.h"		/* FatFs lower layer API */
#include "flash/flash_conf.h"

/* Definitions of physical drive number for each drive */
#define DEV_SD			0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_FLASH		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_SD :
		

		return stat;

	case DEV_FLASH :
		if (sFLASH_ID == SPI_FLASH_ReadID())
		{
		  /* �豸ID��ȡ�����ȷ */
			stat &= ~STA_NOINIT;
		}
		else
		{
		  /* �豸ID��ȡ������� */
			stat = STA_NOINIT; 
			;
		}

		return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	int16_t i=0;
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_SD :
		
		return stat;

	case DEV_FLASH :
		/* ��ʼ��SPI Flash */
		FLASHConfig();
		/* ��ʱһС��ʱ�� */
		i = 500;
		while (--i)
			;	
	  /* ����SPI Flash */
		SPI_Flash_WAKEUP();
	  /* ��ȡSPI FlashоƬ״̬ */
		stat = disk_status(DEV_FLASH);
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_SD :

		return res;

	case DEV_FLASH :
		
 /* ����ƫ��6MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����10MB�ռ� */
		sector += 1536;      
		SPI_FLASH_BufferRead(buff, sector << 12, count << 12);
		res = RES_OK;
		return res;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	uint32_t write_addr; 
	DRESULT status = RES_PARERR;
	if (!count) {
		return RES_PARERR;		/* Check parameter */
	}

	switch (pdrv) {
	case DEV_SD :

		return res;

	case DEV_FLASH :
		 /* ����ƫ��6MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����10MB�ռ� */
		sector += 1536;
		write_addr = sector << 12;    
		SPI_FLASH_SectorErase(write_addr);
		SPI_FLASH_BufferWrite((u8 *)buff, write_addr, count << 12);
		status = RES_OK;
		return res;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_SD :

		return res;

	case DEV_FLASH :
		switch (cmd) {
        /* ����������2560*4096/1024/1024=10(MB) */
		case GET_SECTOR_COUNT:
			*(DWORD *)buff = 2560;		
			break;
			/* ������С  */
		case GET_SECTOR_SIZE :
			*(WORD *)buff = 4096;
			break;
			/* ͬʱ������������ */
		case GET_BLOCK_SIZE :
			*(DWORD *)buff = 1;
			break;        
		}
		res = RES_OK;
		return res;

	}
	return RES_PARERR;
}

DWORD get_fattime(void) {
	/* ���ص�ǰʱ��� */
	return ((DWORD)(2017 - 1980) << 25)		/* Year 2017 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				/* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}