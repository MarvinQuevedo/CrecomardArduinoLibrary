/*
 * CrecoSensor.cpp
 *
 *  Created on: 14 sep. 2018
 *      Author: marvin
 */

#include <TimerTask.h>

TimerTask::TimerTask(long waitTime){

	this->waitTime = waitTime;
	this->lastCall = 0;
}
bool TimerTask::isReady(){
    long now = millis();
    if((now -this->lastCall)>=waitTime){
        this->lastCall = now;
        return true;
    }else{
        return false;
    }
}

TimerTask::~TimerTask() {
	// TODO Auto-generated destructor stub
}

