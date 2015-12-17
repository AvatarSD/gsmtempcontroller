/*
 * mainBuff.h
 *
 *  Created on: 17 груд. 2015
 *      Author: sd
 */

#ifndef MAINBUFF_MAINBUFF_H_
#define MAINBUFF_MAINBUFF_H_
#include "../config.h"
#include "../DallasOneWire/DallasSensorData.h"

class MainBuff
{
public:
	MainBuff();

	DallasSensorData * getMainbuff();
	void writeTemp(DallasSensorData data);
	uint16_t size();
	DallasSensorData & operator [](uint16_t num);

private:
	uint16_t sensorCount;
	DallasSensorData buff[MAINBUFF_SIZE];

};

extern MainBuff mainBuff;

#endif /* MAINBUFF_MAINBUFF_H_ */
