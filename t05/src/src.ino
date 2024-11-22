#include <IRremote.hpp>
#include <IRremote.h>

int value = 2;
int SEND_LED_PIN1 = 0;

IRsend IrSender1;

uint8_t sCommand1 = 0x10;
uint8_t sRepeats = 0;

void setup(){
  Serial.begin(115200);
  IrSender1.begin(SEND_LED_PIN1);
}

void loop(){
  switch(value) {
  case 1:
    IrSender1.sendNEC(0x00, sCommand1, sRepeats);
    Serial.print("0xEF10FF00 ");
    Serial.println("steet1");
    break;
  case 2:
    IrSender1.sendNEC(0x00, sCommand1, sRepeats);
    Serial.print("0xEE11FF00 ");
    Serial.println("street2");
    break;
  }
  delay(100);
}
