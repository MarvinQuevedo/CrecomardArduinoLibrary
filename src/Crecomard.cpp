/*
 * Crecomard.cpp
 *
 *  Created on: 28 abr. 2017
 *      Author: marvin
 */

#include "Crecomard.h"

//Se usa para cuando no se necesita leer una función extra, se manda un objeto vacio y controlado desde aca
ExtraFunction extraTemp("","","");


Crecomard::Crecomard(HardwareSerial *btSerial)
{
	this->_btSerial  = btSerial;
  
  this->_debug = true;
	if(this->_btSerial == &Serial)
	{
		this->_debug = false;
	}
 this->numLen = 0;
 this->valueLen = 0;
  this->extraLen = 0;
  this->endPos = 0;
  this->valuePos = 0;
  this->extraPos = 0;
  this->pin = 0;
  this->act = 0;
  this->act2 = "";
  this->p = "";
  this->fun = "";
  this->val = "";
  this->ext = "";
 this->FUN = "{\"f\":\"";
 this->VALUE  = "\",\"v\":\"";
 this->EXTRA   = "\",\"e\":\"";
 this->END = "\"}";

}
void Crecomard::begin(){
	this->_btSerial->begin(9600);
	if(this->_debug){
		Serial.begin(9600);
		//Serial.println("Timbre automatizado");
		this->sendMessage("ARD_START", "Arduino ha iniciado", 0);
	}
}
void Crecomard::resetValues()
{
	this->numLen = 0;
	this->valueLen = 0;
	this->extraLen = 0;
	this->endPos = 0;
	this->valuePos = 0;
	this->extraPos = 0;
	this->pin = 0;
	this->act = 0;
	this->act2 = "";
}

void Crecomard::setAsOutput(int *pins, int pSize)
{
	pSize = pSize/sizeof(int);
	  for(int i = 0;i<pSize;i++){
		  pinMode(pins[i], OUTPUT);

		  this->printDebug("OUTPUT:");this->printlnDebug(String(pins[i]));
		}
}
void Crecomard::setAsOutput(int from, int to)
{
	for(int i = from;i<=to;i++){
	  pinMode(i, OUTPUT);
	  this->printDebug("OUTPUT:");this->printlnDebug(String(i));
	}
}

void Crecomard::printDebug(String data)
{
	if(this->_debug)
	{
		Serial.print(data);
	}
}
void Crecomard::printlnDebug(String data)
{
	this->printDebug(data + "\n");
}
void Crecomard::printDebug(char c)
{
	this->printDebug(String(c));
}


void Crecomard::sendMessage(String _id, String message, int pin)
{
	String msg = "{\"_id\":\""+_id +"\",\"msg\":\""+message+"\",\"pin\":\"" + pin + "\"}";
	this->_btSerial->println(msg);
	this->printlnDebug(msg);
}
void Crecomard::notifyEvent(String event, String message)
{
	this->sendMessage(event, message, 0);
}
void Crecomard::sendExternChange(int pin, int state)
{

	String message = "[["+ String(pin)+","+String(state)+"]]";
	this->notifyEvent(PIN_STATES, message);
}
void Crecomard::sendExternChange(int pin, bool digital)
{
	int state = (digital)?digitalRead(pin):analogRead(pin);
	this->sendExternChange(pin, state);
}
void Crecomard::toHigh(int pin)
{
	digitalWrite(pin, HIGH);
	this->sendExternChange(pin, HIGH);
}
void Crecomard::toLow(int pin)
{
	digitalWrite(pin, LOW);
	this->sendExternChange(pin, LOW);
}
void Crecomard::togglePin(int pin)
{
	int read = digitalRead(pin);
	int action = (read == HIGH)?LOW:HIGH;
	digitalWrite(pin, action);
	this->sendExternChange(pin, action);
}
void Crecomard::splitOnOffAll(){


		int c = 0;
		int p = 0;
		int t;
		this->val.remove(0, 1);
		this->val.remove(this->val.length()-1,1);

		int pin = 0;
//		int action = 0;
		int i = 0;
		const int max = this->ext.toInt()*2;
		while(c <= max){
				i++;
				p = this->val.indexOf(',');
				t = this->val.substring(0, p).toInt();
				if((i%2) == 0){
					String info = "DW pin = ";
					info.concat(pin);
					info.concat(", state=");
					info.concat(t);
					this->printlnDebug(info);
					digitalWrite(pin, t);
				}else{
					pin = t;
				}

				this->val = this->val.substring(p+1, this->val.length());
				c++;
			}
		//String event = (action == HIGH)?ON_ALL:OFF_ALL;
		this->notifyEvent(TASK_DONE, "done");
}

void Crecomard::splitDrAll(){


	String message = "[";
	int size = this->ext.toInt();
	int c = 0;
	int p = 0;
	int t;

	this->val.remove(0, 1);
	this->val.remove(this->val.length()-1,1);

	while(c <= size){
			p = this->val.indexOf(',');

			t = this->val.substring(0, p).toInt();
			if(t>0 && t<100){
				if(c < size){

					  message += "["+ String(t) +","+ String(digitalRead(t)) + "],";
				  }else{
					  message += "["+ String(t) +","+ String(digitalRead(t)) + "]";
				  }
			}
			c++;
			this->val = this->val.substring(p+1, this->val.length());

		}
	message+= "]";
	this->notifyEvent(PIN_STATES, message);
}
void Crecomard::process(ExtraFunction *extra)
{

	  this->printDebug("\nData: ");this->printlnDebug(this->p);
	  if(this->p.indexOf(IS_READY_TEST)>-1){
	  		  this->_btSerial->print("true");
	  		  this->printlnDebug("Ready test");
	  		  return;
	  }

	  this->numLen = this->FUN.length();
	  this->valueLen = this->VALUE.length();
	  this->extraLen = this->EXTRA.length();
	  this->endPos = this->p.indexOf(END);
	  this->valuePos = this->p.indexOf(VALUE);
	  this->extraPos = this->p.indexOf(EXTRA);

	  if(this->endPos == -1 || this->valuePos == -1 || this->extraPos == -1){
		  this->printlnDebug("No hay valores usables");
		  return;
	  }

	  this->fun = this->p.substring(this->numLen,this->valuePos);
	  this->val = this->p.substring(this->valuePos + this->valueLen, this->extraPos);
	  this->ext = this->p.substring(this->extraPos + this->extraLen, this->endPos);


	  if(this->fun.equals(DW) || this->fun.equals(AW)){
		  this->pin = this->ext.toInt();
		  this->act = this->val.toInt();
		  if((this->act == LOW || this->act == HIGH) || this->fun.equals(AW)){
			  //pinMode(pin, OUTPUT);
			  if(this->fun.equals(DW)){
				  digitalWrite(this->pin, this->act);
			  }else{
				  analogWrite(this->pin, this->act);
			  }
		  }else{
			  this->printlnDebug("The action is not LOW or HIGH, break");
		  }
	  }else if (this->fun.equals(PM_CHANGE)) {
		  this->pin = this->ext.toInt();
		  this->act2 = this->val;
		  if(this->act2.equals(PM_OUT)){
			  pinMode(this->pin, OUTPUT);
		  }else if(this->act2.equals(PM_IN)){
			  pinMode(this->pin, INPUT);
		  }
	  }
	  else if(this->fun.equals(DR)){
		  this->pin = this->ext.toInt();
		  int r = digitalRead(this->pin);
		  this->sendMessage(this->val, String(r), this->pin);
	  }else if(this->fun.equals(AR)){
		  this->pin = this->ext.toInt();
	      float r = analogRead(this->pin) * (5.0 / 1023.0);;
	      this->sendMessage(this->val, String(r), this->pin);
	    }else if(this->fun.equals(DR_ALL)){
	    	this->splitDrAll();

	    }else if(this->fun.equals(DW_ALL)){
	    	this->splitOnOffAll();

	    }else{
	    	extra->setFunction(this->fun);
	    	extra->setVal(this->val);
	    	extra->setExt(this->ext);
	    	extra->setIsReady(true);

	    }
	    this->resetValues();
}

void Crecomard::listen(ExtraFunction *extra)
{
	 while(this->_btSerial->available()) {
	    // get the new byte:
	    char inChar = (char)this->_btSerial->read();
	    this->printDebug(inChar);
	    // add it to the string:
	    this->p += inChar;
	    // if the incoming character is a newline, set a flag
	    // so the main loop can do something about it:
	    extra->setIsReady(false);
	    if (inChar == '}' || inChar == '\n') {
	      this->process(extra);
	      this->p = "";
	      break;
	    }
	  }
}
void Crecomard::listen()
{
	this->listen(&extraTemp);
}
void Crecomard::sendSms(String number, String message){
  //create a command, the Crecomard APP process this
  String msg = F("{\"_id\":\"SMS\",\"msg\":\"");
    msg.concat(message);
    msg.concat(F("\",\"pin\":\""));
    msg.concat(number);
    msg.concat(F("\"}"));
    this->_btSerial->println(msg);
    this->printlnDebug(msg);
}
void Crecomard::doCall(String number, long timeout){  
  //create a command, the Crecomard APP process this
  String msg = F("{\"_id\":\"CALL\",\"msg\":\"");
    msg.concat(timeout);
    msg.concat(F("\",\"pin\":\""));
    msg.concat(number);
    msg.concat(F("\"}"));
    this->_btSerial->println(msg);
    this->printlnDebug(msg);
}
void Crecomard::sendEmail(String email, String message){  
  //create a command, the Crecomard APP process this
    String msg = F("{\"_id\":\"SMAIL\",\"msg\":\"");
    msg.concat(message);
    msg.concat(F("\",\"pin\":\""));
    msg.concat(email);
    msg.concat(F("\"}"));
    this->_btSerial->println(msg);
    this->printlnDebug(msg);
}
void Crecomard::showToast(String message, bool toastShort){  
  //create a command, the Crecomard APP process this
  this->sendMessage(F("TOAST"), message, (toastShort)?0:1); 
}
void Crecomard::showToast(String message){  
  //create a command, the Crecomard APP process this
  this->sendMessage(F("TOAST"), message, true); 
}
void Crecomard::showSnackBar(String message){  
  //create a command, the Crecomard APP process this
  this->sendMessage(F("SNACK"), message, 0); 
}
void Crecomard::showAlert(String message, String title){  
  //create a command, the Crecomard APP process this
   String msg = F("{\"_id\":\"ALERT\",\"msg\":\"");
    msg.concat(message);
    msg.concat(F("\",\"pin\":\""));
    msg.concat(title);
    msg.concat(F("\"}"));
    this->_btSerial->println(msg);
    this->printlnDebug(msg);
}
void Crecomard::showNotification(String message, String title){  
  //create a command, the Crecomard APP process this
   String msg = F("{\"_id\":\"NOTIS\",\"msg\":\"");
    msg.concat(message);
    msg.concat(F("\",\"pin\":\""));
    msg.concat(title);
    msg.concat(F("\"}"));
    this->_btSerial->println(msg);
    this->printlnDebug(msg);
}
