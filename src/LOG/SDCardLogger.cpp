/*
 * SDCardLogger.cpp
 *
 *  Created on: 27 лист. 2015
 *      Author: sd
 */

#include "SDCardLogger.h"
#include "string.h"

SDCardLogger debugSDcardLog;

SDCardLogger::SDCardLogger()
{

}

SDCardLogger::~SDCardLogger()
{

}

void SDCardLogger::putch(char c)
{
	unsigned int ret;
	f_write(&logFile, &c, 1, &ret);
}

int SDCardLogger::write(const unsigned char *outbuf, unsigned int outlen)
{
	unsigned int ret;
	f_write(&logFile, outbuf, outlen, &ret);
	return ret;
}

bool SDCardLogger::preSendHandler()
{
	return true;
}

bool SDCardLogger::postSendHandler()
{
	f_sync(&logFile);
	return true;
}

int SDCardLogger::begin()
{
	end();

	char buf[50] = {"toiooyo"};
	//strcpy(buf, getDateStr());

	if (f_mount(&fatFs, "", 1) != FR_OK)
		return -3;
	if (f_open(&logFile, buf, FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
		return -2;
	if (f_lseek(&logFile, f_size(&logFile)) != FR_OK)
		return -1;
	return 0;
}

int SDCardLogger::end()
{
	f_close(&logFile);

	return 0;
}

/*---------------------------------------------------------*/
/* User Provided RTC Function called by FatFs module       */
/* Used to provide a Timestamp for SDCard files and folders*/

DWORD get_fattime(void)
{
	// Returns current time packed into a DWORD variable
//	return ((DWORD) (2015 - 1980) << 25)	// Year 2013
//	| ((DWORD) 8 << 21)				// Month 7
//			| ((DWORD) 2 << 16)				// Mday 28
//			| ((DWORD) 20 << 11)				// Hour 0..24
//			| ((DWORD) 30 << 5)				// Min 0
//			| ((DWORD) 0 >> 1);				// Sec 0
	return (DWORD)getUnixTime();
}
