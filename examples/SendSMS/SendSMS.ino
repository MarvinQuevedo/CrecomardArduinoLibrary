#include "Crecomard.h"
Crecomard crecomard(&Serial2);

void setup(){

  crecomard.begin();
  delay(5000);
  crecomard.sendSms("##NUMBER##","MESSAGE");
}
void loop(){

  crecomard.listen();

}
