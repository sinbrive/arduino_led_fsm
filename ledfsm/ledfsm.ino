#include "fsm.h"

Led myled(13);

void setup() {
  Serial.begin(9600);
  // myled.blink(500);
  //    myled.off();
  //    myled.on();
  myled.animation(3, 500, 2000);

}

void loop() {
  myled.fsm();
}
