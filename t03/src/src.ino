void setup(void) {
    void chgch(void);

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
    digitalWrite(11,LOW);
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);

    Serial.begin(115200);
    delay(700);
    Serial.println("Q960 TEST Version 0.22");
    chgch();
    attachInterrupt(digitalPinToInterrupt(2), chgch, FALLING);
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
void loop(void) {
}

volatile int u102,u103,ch;

void chgch(void) {
    int u102v,u103v,chv;
    u102v = u_enc(3);
    u103v = u_enc(7);
    chv = u102v*10 + u103v;
    if (chv!=ch) {
        digitalWrite(LED_BUILTIN,HIGH);
        Serial.print("Change CH=");
        Serial.println(chv);
        ch = chv;
    }
    digitalWrite(LED_BUILTIN,LOW);
}