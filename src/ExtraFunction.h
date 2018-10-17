/*
 * ExtraFunction.h
 *
 *  Created on: 19 may. 2017
 *      Author: marvin
 */

#include "TimerTask.h"
#ifndef BLUINODROID_EXTRAFUNCTION_H_
#define BLUINODROID_EXTRAFUNCTION_H_

class ExtraFunction {
public:
	ExtraFunction(String function, String val, String ext);

	const String& getFunction() const {
			return _function;
		}

	void setFunction(const String& function) {
		_function = function;
	}

	const String& getVal() const {
		return _val;
	}

	void setVal(const String& val) {
		_val = val;
	}

	const String& getExt() const {
		return _ext;
	}

	void setExt(const String& ext) {
		_ext = ext;
	}

	boolean isReady();

	void setIsReady(boolean ready) {
		_ready = ready;
	}

private:
	String _function;
	String _val;
	String _ext;
	boolean _ready;
};

#endif /* BLUINODROID_EXTRAFUNCTION_H_ */
