#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
Servo servo;
String incomingString = "";

void setup() {
  // put your setup code here, to run once:
  servo.attach(6);
  servo.write(90);

  Serial.begin(115200);
  mySerial.begin(115200);

}
void processCmd(String cmd) {
  if (cmd == "Right")
  {
    servo.attach(6);
    servo.write(0);
  } else if (cmd == "Left")
  {
    servo.attach(6);
    servo.write(180);
  }
}

int i = 0;
void loop() {

  if (mySerial.available()) {
    servo.detach(); //!!!!CONFLICT!!!!IMPORTANT

    incomingString = mySerial.readString();
    //get real cmd starts/ends with "#"
    //call processCmd function
    if(i == 0){
      processCmd("Right");
      i++;
    } else {
      processCmd("Left");
      i--;
    }
    Serial.println("0_" + incomingString + "_0");
  }
}
