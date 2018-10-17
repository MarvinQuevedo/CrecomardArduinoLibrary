/*
 * CrecomardSoftware.h
 *
 *  Created on: 17 oct. 2018
 *      Author: marvin
 */
#include "Crecomard.h"
#include <SoftwareSerial.h>

#ifndef CRECOMARD_SRC_CRECOMARDSOFTWARE_H_
#define CRECOMARD_SRC_CRECOMARDSOFTWARE_H_

class CrecomardSoftware {
public:
	CrecomardSoftware(SoftwareSerial *btSerial);
	void printDebug(String data);
	void printDebug(char c);
	void printlnDebug(String data);
	void notifyEvent(String event, String message);
	void setAsOutput(int *pins, int pSize);
	void setAsOutput(int from, int to);
	void sendPinStates(int *pins, int size);
	void sendExternChange(int pin, bool digital);
	void sendExternChange(int pin, int state);
	void toHigh(int pin);
	void toLow(int pin);
	void togglePin(int pin);
	void listen(ExtraFunction *extra);
	void listen();
	void begin();
	void sendMessage(String _id, String message, int pin);
  //Especials controls
  void sendSms(String number, String message);
  void doCall(String number, long timeout);
  void sendEmail(String email, String message);
  void showToast(String message, bool toastShort);
  void showToast(String message);
  void showSnackBar(String message);
  void showAlert(String message, String title);
  void showNotification(String message, String title);
private:
	 String FUN;
	 String VALUE;
	 String EXTRA;
	 String END;
	bool _debug;
	SoftwareSerial *_btSerial;
	int numLen;
	int valueLen;
	int extraLen;
	int endPos;
	int valuePos;
	int extraPos;
	int pin;
	int act;
	String act2;
	String p;
	String fun;
	String val;
	String ext;

	void resetValues();
	void process(ExtraFunction *extra);

	void splitOnOffAll();
	void splitDrAll();
};

#endif /* CRECOMARD_SRC_CRECOMARDSOFTWARE_H_ */
