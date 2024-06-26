#include <Servo.h>

#include <IRremote.h>

const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
Servo servo1;
Servo servo2;

int pos = 0;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  servo1.attach(11);
  servo2.attach(10);
}

void loop() {
  if (irrecv.decode(&results)) {

    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch (results.value) {
      case 0xFFA25D:
        Serial.println("CH-");
        break;
      case 0xFF629D:
        Serial.println("CH");
        break;
      case 0xFFE21D:
        Serial.println("CH+");
        break;
      case 0xFF22DD:
        Serial.println("|<<");
        break;
      case 0xFF02FD:
        Serial.println(">>|");
        break;
      case 0xFFC23D:
        Serial.println(">|");
        break;
      case 0xFFE01F:
        Serial.println("-");
        break;
      case 0xFFA857:
        Serial.println("+");
        break;
      case 0xFF906F:
        Serial.println("EQ");
        break;
      case 0xFF6897:
        Serial.println("0");
        break;
      case 0xFF9867:
        Serial.println("100+");
        break;
      case 0xFFB04F:
        Serial.println("200+");
        break;
      case 0xFF30CF:
        Serial.println("1");
        for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          servo1.write(pos);  // tell servo to go to position in variable 'pos'
          delay(15);          // waits 15 ms for the servo to reach the position
        }
        for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
          servo1.write(pos);                   // tell servo to go to position in variable 'pos'
          delay(15);                           // waits 15 ms for the servo to reach the position
        }
        break;
      case 0xFF18E7:
        Serial.println("2");
        servo2.write(0);
        delay(500);
        servo2.write(90);
        delay(500);
        servo2.write(0);
        delay(500);
        servo2.write(90);
        delay(500);
        servo2.write(0);
        delay(500);
        servo2.write(90);
        delay(500);
        break;
      case 0xFF7A85:
        Serial.println("3");
        break;
      case 0xFF10EF:
        Serial.println("4");
        break;
      case 0xFF38C7:
        Serial.println("5");
        break;
      case 0xFF5AA5:
        Serial.println("6");
        break;
      case 0xFF42BD:
        Serial.println("7");
        break;
      case 0xFF4AB5:
        Serial.println("8");
        break;
      case 0xFF52AD:
        Serial.println("9");
        break;
    }
    key_value = results.value;
    irrecv.resume();
  }
}