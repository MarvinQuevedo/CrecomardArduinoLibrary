/*
 * CrecoSensor.h
 *
 *  Created on: 14 sep. 2018
 *      Author: marvin
 */

#ifndef LIBRARIES_CRECOMARD_TIMERTASK_H_
#define LIBRARIES_CRECOMARD_TIMERTASK_H_
#include "Arduino.h"

class TimerTask {
private:
	long lastCall;
	long waitTime;


public:
    bool isReady();
	TimerTask(long waitTime);
	virtual ~TimerTask();
};

#endif /* LIBRARIES_CRECOMARD_CRECOSENSOR_H_ */
