/*
 * ExtraFunction.cpp
 *
 *  Created on: 19 may. 2017
 *      Author: marvin
 */

#include "ExtraFunction.h"
ExtraFunction::ExtraFunction(String function, String val, String ext)
{
	this->_function = function;
	this->_val = val;
	this->_ext = ext;
 this->_ready = false;
}

bool ExtraFunction::isReady()
{
	if(_ready){
		this->_ready = false;
		return true;
	}else{
		return false;
	}

}
