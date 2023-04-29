// Libraries
#include <SoftwareSerial.h>
#include <Servo.h>
#include "TFMini.h"

#include <Wire.h>
#include <HCSR04.h> // Include the HCSR04 header


// Define pins
#define PAN_SERVO 9
#define TILT_SERVO 10
#define TRIG 12
#define ECHO 13

// Globals
int panLim[] = {0,150};
int tiltLim[] = {0,45};

int pan = panLim[0];
int tilt = tiltLim[0];

int panIncrement = 1;
int tiltIncrement = 1;

Servo panServo;
Servo tiltServo;
TFMini tfmini;
SoftwareSerial Serial1(2, 3);  
UltraSonicDistanceSensor ultrasonicSensor(TRIG, ECHO);

void getTFminiData(int* distance, int* strength)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if (SerialTFMini.available())
  {
    rx[i] = SerialTFMini.read();
    if (rx[0] != 0x59)
    {
      i = 0;
    }
    else if (i == 1 && rx[1] != 0x59)
    {
      i = 0;
    }
    else if (i == 8)
    {
      for (j = 0; j < 8; j++)
      {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256))
      {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    }
    else
    {
      i++;
    }
  }
}
 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  panServo.attach(PAN_SERVO); 
  tiltServo.attach(TILT_SERVO); 
  panServo.write(pan);
  tiltServo.write(tilt);
  delay(1000);
  
  Serial1.begin(TFMINI_BAUDRATE);    //Initialize the data rate for the SoftwareSerial port
  Serial1.begin(&SerialTFMini);            //Initialize the TF Mini sensor
  Serial.setTimeout(10);


  // Write header
  Serial.print("Time(s), ");
  Serial.print("Pan(degree), ");
  Serial.print("Tilt(degree), ");
  Serial.print("Ultrasonic(mm), ");
  Serial.print("ToF(mm)");
  Serial.println();

}

 
void loop() {
  
  // Move to new position
  pan = pan + panIncrement;
  panServo.write(pan);  
  if(pan > panLim[1] || pan < panLim[0]){
    panIncrement = -panIncrement;
    tilt = tilt + tiltIncrement;
    tiltServo.write(tilt); 
    if(tilt < tiltLim[0] || tilt > tiltLim[1] ){
      tiltIncrement = -tiltIncrement;
    }
  }
  delay(200); // give a little time to move
   if (Serial1.available()) {  //check if serial port has data input
    if(Serial1.read() == HEADER) {  //assess data package frame header 0x59
      uart[0]=HEADER;
      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) { //save data in array
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          Serial.print("dist = ");
          Serial.print(dist); //output measure distance value of LiDAR
          Serial.print('\t');
          Serial.print("strength = ");
          Serial.print(strength); //output signal strength value
          Serial.print('\n');
        }
      }
    }
  }
  // Current time
  float t = ((float) millis())/1000.0;

  // Ultrasonic
  float usDist = ultrasonicSensor.measureDistanceCm()*10.0; 

  // TOF
  getTFminiData(&distance, &strength);


  // Print result
  Serial.print(t);
  Serial.print(" ");
  Serial.print(pan);
  Serial.print(" ");
  Serial.print(tilt);
  Serial.print(" ");
  Serial.print(usDist);
  Serial.print(" ");
  Serial.print(distance);
  Serial.print(" ");
  Serial.println();

}
