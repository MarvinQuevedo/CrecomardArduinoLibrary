#include "Crecomard.h"
Crecomard crecomard(&Serial2);
void setup(){
	pinMode(13, OUTPUT);
	crecomard.begin();
}

void loop(){
	crecomard.listen();
}
