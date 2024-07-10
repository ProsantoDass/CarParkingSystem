#include <Servo.h>
#include <SoftwareSerial.h>

Servo rj;
SoftwareSerial bt(6, 7);

int IR1 = 3;
int IR2 = 4;

int Slot = 4;  //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

//char ch;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  rj.attach(9);
  rj.write(160);
  //rj.write(180);

  Serial.begin(115200);
  bt.begin(115200);
}

void loop() {


  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        rj.write(120);
        Slot = Slot - 1;
      }
    } else {
      Serial.println("SORRY , Parking Full !");
      bt.println("SORRY , Parking Full !");
    }
  }

  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      rj.write(120);
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {

    delay(1000);

    rj.write(180);
    flag1 = 0, flag2 = 0;
  }

  //Serial.print("Slot Left : ");
  //Serial.println(Slot);
  bt.print("Slot Left : ");
  bt.println(Slot); 
}