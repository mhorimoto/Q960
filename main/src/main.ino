//#include <Arduino.h>
#include <IRremote.hpp>
#include <IRremote.h>

#define ON  LOW
#define OFF HIGH

IRsend IrSender1;

int SEND_LED_PIN1 = 0;
uint8_t sRepeats = 0;

volatile uint8_t sCommand = 0x10;
volatile int led11;

void setup(void) {
    void chgch(void);
    void allLED(int);

    pinMode(2,INPUT_PULLUP);  // Change Ch Button
    pinMode(3,INPUT_PULLUP);  // U102_1
    pinMode(4,INPUT_PULLUP);  // U102_2
    pinMode(5,INPUT_PULLUP);  // U102_4
    pinMode(6,INPUT_PULLUP);  // U102_8
    pinMode(7,INPUT_PULLUP);  // U103_1
    pinMode(8,INPUT_PULLUP);  // U103_2
    pinMode(9,INPUT_PULLUP);  // U103_4
    pinMode(10,INPUT_PULLUP); // U103_8
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    allLED(OFF);
    led11 = OFF;
    Serial.begin(115200);
    IrSender1.begin(SEND_LED_PIN1);
    delay(700);
    Serial.println("Q960 TEST Version 1.00");
    chgch();
    attachInterrupt(digitalPinToInterrupt(2), chgch, FALLING);
}


void interval_1sec(void) {
    digitalWrite(11,led11);
    led11 = (led11==ON)? OFF : ON;
    digitalWrite(12,led11);
    IrSender1.sendNEC(0x00, sCommand, sRepeats);
}

void allLED(int s) {
    digitalWrite(11,s);
    digitalWrite(12,s);
    digitalWrite(13,s);
}
int u_enc(int u) {
    int uv,a;
    int i;
    uv = 0;
    for(i=0;i<4;i++) {
        a = (digitalRead(i+u)&0x1) ? 0 : 1;
        uv += a << i;
    }
    return(uv);
}

volatile int u102,u103,ch;

void chgch(void) {
    int u102v,u103v,chv;
    u102v = u_enc(3);
    u103v = u_enc(7);
    chv = u102v*10 + u103v;
    if (chv!=ch) {
        digitalWrite(12,ON);
        Serial.print("Change CH=");
        Serial.println(chv);
        ch = chv;
        sCommand = ch;
    }
    allLED(OFF);
}

void loop(void) {
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastTime >= 1000) { // 1秒間隔
        lastTime = currentTime;
        interval_1sec();
    }
}
