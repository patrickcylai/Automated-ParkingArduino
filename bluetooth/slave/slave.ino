#include <SoftwareSerial.h>   //Software Serial Port
#include<Servo.h>

#define RxD 7
#define TxD 6

#define DEBUG_ENABLED  1

SoftwareSerial blueToothSerial(RxD,TxD);

Servo right;
Servo left;
const int leftPin = 13; 
const int rightPin = 12;
const int speedRight = 1000; // Range: 1500(Stop)~1000(Full speed)
const int speedLeft = 2000; // Range: 1500(Stop)~2000(Full speed)
const int revRight = 2000; // Range: 1500(Stop)~2000(Full speed)
const int revLeft = 1000; // Range: 1500(Stop)~1000(Full speed)

void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  //wait 1s and flush the serial and btooth buffers
  delay(1000);
  Serial.flush();
  blueToothSerial.flush();
  pinMode(3, OUTPUT); //Left reciever
  pinMode(4, INPUT); // Left IR LED
  pinMode(10, INPUT); // Right IR LED
  pinMode(11, OUTPUT); // Right reciever
  right.attach(rightPin);
  left.attach(leftPin);

} 

void loop() 
{ 
//  char recvChar;
  char command;
  Serial.print("jgrdfgdfgn");

  // Infinite loop
  while(1){
    // If there is data ready in the btooth
    if(blueToothSerial.available())
    {
//      // Read, turn to uppercase if appropriate and send back
//      recvChar = blueToothSerial.read();
//      Serial.print("Slave Received: ");
//      Serial.print(recvChar);
//      Serial.print("\n");
//      if (recvChar >= 'a' && recvChar <= 'z')
//      {
//        // Make the character upper case
//        recvChar -= 32;
//      }
//      // Send back
//      blueToothSerial.print(recvChar);
//      Serial.print("Slave Transmitted: ");
//      Serial.print(recvChar);
//      Serial.print("\n");
  Serial.print("jgrdfgdfgn");

        command = blueToothSerial.read();
          Serial.print(command);
          Serial.print("\n");
        if (command == 'a') {
          goLeft();
          delay(500);
        }
        if (command == 'd') {
          goRight();
          delay(500);        
        } 
        if (command == 'w') {
          goForward();
          delay(500);
        }
        if (command == 's') {
          reverse();
          delay(500);
        }
        if (command == ' ') {
          stopAll();
          delay(500);
        }
        if (command == 'q') {
          //turnOnSpotLeft();
          right.write(180);
          left.write(180);
          delay(795);
        }
        if (command == 'e') {
          turnOnSpotRight();
          delay(500);
        }
        
        while(
    }
  }
} 

void setupBlueToothConnection()
{
  //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.begin(38400);
  //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STWMOD=0\r\n");
  //set the bluetooth name (irrelevant)
  blueToothSerial.print("\r\n+STNA=Slave20\r\n"); 
  // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STOAUT=1\r\n");
  // Auto-connection is not allowed
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); 
  delay(2000); // This delay is required.
  //make the slave bluetooth inquirable 
  blueToothSerial.print("\r\n+INQ=1\r\n");
  delay(2000); // This delay is required.
}

// Movement Methods - MUST INSERT DELAY AFTER EACH MOVEMENT FOR PROPER OPERTATION
void goForward() {
  right.writeMicroseconds(speedRight);
  left.writeMicroseconds(speedLeft);
}

void stopAll() {
  right.writeMicroseconds(1500);
  left.writeMicroseconds(1500);
}

void goLeft() {
  left.writeMicroseconds(1500);
  right.writeMicroseconds(speedRight);
}

void goRight() {
  right.writeMicroseconds(1500);
  left.writeMicroseconds(speedLeft);
}

void reverse() {
  right.writeMicroseconds(2000);
  left.writeMicroseconds(1000);
}

void reverseLeft() {
  left.writeMicroseconds(1500);
  right.writeMicroseconds(revRight);
}

void reverseRight() {
  right.writeMicroseconds(1500);
  left.writeMicroseconds(revLeft);
}

void turnOnSpotLeft() {
  right.writeMicroseconds(speedRight);
  left.writeMicroseconds(revLeft);
}

void turnOnSpotRight() {
  right.writeMicroseconds(revRight);
  left.writeMicroseconds(speedLeft);
}

void detachAll() {
  right.detach();
  left.detach();
}
