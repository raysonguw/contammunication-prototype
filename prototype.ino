#include <CapacitiveSensor.h>
#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;
CapacitiveSensor  cs_4_2 = CapacitiveSensor(4,2);
CapacitiveSensor  cs_12_13 = CapacitiveSensor(12,13);

int pos = 40;    // variable to store the servo position
int end = 180;
int pos_dip = 12;

void setup() {
  servo1.attach(5);  // 5
  servo2.attach(6);  // 6
  servo3.attach(9);
  servo1.write(pos);
  servo3.write(pos_dip);
  servo2.write(180 - pos);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1
  Serial.begin(9600);
}

void loop() {
  long start = millis();
  long total1 =  cs_4_2.capacitiveSensor(50);
  long total2 =  cs_12_13.capacitiveSensor(50);

  Serial.println(millis() - start);        // check on performance in milliseconds
  Serial.print("total1:");
  Serial.println(total1);
  Serial.print("total2:");
  Serial.println(total2);

  delay(10);

  for (int i = 0; i <= 150; i += 3) {
      servo3.write(180 - pos_dip);
      delay(50);                       // waits 15ms for the servo to reach the position
  }
  // delay(1500);
  if (total1 > 100 && total2 > 100) {
    for (pos = 40; pos <= end - 90; pos += 15) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(pos);
      servo2.write(180 - pos);
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = end - 90; pos <= end; pos += 15) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      servo2.write(180 - pos);
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = end; pos >= 40; pos -= 10) { // goes from 180 degrees to 0 degrees
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      servo2.write(185 - pos);
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(500);
  }
  for (int i = 180; i >= 0; i -= 3) { // goes from 180 degrees to 0 degrees
   servo3.write(pos_dip);
   delay(50);                       // waits 15ms for the servo to reach the position
  }
}