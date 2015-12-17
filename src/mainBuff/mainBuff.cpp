/*
 * mainBuff.cpp
 *
 *  Created on: 17 груд. 2015
 *      Author: sd
 */

#include "mainBuff.h"
#include "../LOG/debug.h"

MainBuff mainBuff;

MainBuff::MainBuff()
{
	sensorCount = 0;
}

DallasSensorData * MainBuff::getMainbuff()
{
	return buff;
}

void MainBuff::writeTemp(DallasSensorData data)
{
	for (uint16_t i = 0; i <= sensorCount; i++)
	{
		if (buff[i].getROM() == data.getROM())
		{
			buff[i] = data;
			break;
		}
		else if (buff[i].getROM().isEmpty())
		{
			buff[i] = data;
			if (sensorCount++ < MAINBUFF_SIZE)
			INFO(F("Find new device"));
			INFO(data.getROM().toString());
			break;
		}
	}
}

uint16_t MainBuff::size()
{
	return sensorCount;
}

DallasSensorData & MainBuff::operator [](uint16_t num)
{
	return buff[num];
}
