#include "Crecomard.h"
Crecomard crecomard(&Serial2);

void setup(){

  crecomard.begin();
  delay(3000);
  crecomard.showToast("Hello, this message is show in your smarthone");
  delay(3000);
  crecomard.showSnackBar("This is a snackbar :)");
  delay(3000);
  crecomard.showAlert("Hello, this is an alert", "Title of alert");
  delay(3000);
  crecomard.showNotification("Hello, this is an notification", "Title of notification");
}
void loop(){

  crecomard.listen();

}
