// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
// create servo object to control a servo
// twelve servo objects can be created on most boards


const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

int aX,aY,aZ,temp,gX,gY,gZ;

int pos1=55;
int pos2=55;
int pos3=55;
int pos4=55;
int pos5=55;



char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  //myservo1.attach(6);
  //myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);
  myservo5.attach(3);
  myservo6.attach(5);

  //myservo1.write(0);
  //myservo2.write(0);
  myservo3.write(0);
  myservo4.write(0);
  //myservo5.write(90);
  //myservo6.write(90);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)


  //conversion
  aX = (accelerometer_x / 16384.0)*90;
  aY = (accelerometer_y / 16384.0)*90; 
  aZ = (accelerometer_z / 16384.0)*90;

    if(aX<0 && aZ<0)
  {
    aX=-180-aX;
  }
    if(aX>0 && aZ<0)
  {
    aX=180-aX;
  }
  if(aY<0 && aZ<0)
  {
    aY=-180-aY;
  }
    if(aY>0 && aZ<0)
  {
    aY=180-aY;
  }


  temp=(temperature/340.00+36.53);

  gX = gyro_x / 131.0;
  gY = gyro_y / 131.0; 
  gZ = gyro_z / 131.0;

  
  // print out data
  Serial.print("|##| position(deg) | aX = "); Serial.print(aX);
  Serial.print(" | aY = "); Serial.print(aY);
  Serial.print(" | aZ = "); Serial.print(aZ);
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
//  Serial.print("  |##|  gyro(deg/sec) | gX = "); Serial.print(gX);
  //Serial.print(" | gY = "); Serial.print(gY);
  //Serial.print(" | gZ = "); Serial.print(gZ);
  //Serial.print("  |##|   | temp(deg C) = "); Serial.print(temp);

  Serial.print("  |##|  R1=");Serial.print(pos1);
  Serial.print("  |##|  R2=");Serial.print(pos2);
  Serial.print("  |##|  L1=");Serial.print(pos4);
  Serial.print("  |##|  L2=");Serial.print(pos3);
  
  Serial.println();


  //myservo5.write(90-aX);
  //myservo6.write(90+aY);


 //pos1=pos5;
 //pos2=pos5;
 //pos3=pos5;
 //pos4=pos5;


//myservo1.write(pos1);
//myservo2.write(pos2);
//myservo3.write(pos3);
//myservo4.write(pos4);


if (Serial.available()>0)
{
int command=Serial.read();

switch(command)
{

 case 'a':
 pos1=pos1+1;
 pos4=pos4-1;
 pos2=pos2+1;
 pos3=pos3-1;

 break;


 case 's':
 pos1=pos1+1;
 pos4=pos4+1;
 pos2=pos2-1;
 pos3=pos3-1;

 break;

 case 'd':
 pos1=pos1-1;
 pos4=pos4+1;
 pos2=pos2-1;
 pos3=pos3+1;

 break;

 case 'w':
 pos1=pos1-1;
 pos4=pos4-1;
 pos2=pos2+1;
 pos3=pos3+1;

 break;

 case 'j':
 pos1=pos1+1;
 pos4=pos4+1;
 pos2=pos2+1;
 pos3=pos3+1;
 pos5=pos5+1;

 break;

 case 'n':
 pos1=pos1-1;
 pos4=pos4-1;
 pos2=pos2-1;
 pos3=pos3-1;
 pos5=pos5-1;

 break;

 case 'g':
 pos1=pos1+1;
 pos4=pos4-1;
 pos2=pos2-1;
 pos3=pos3+1;

 break;

 case 'h':
 pos1=pos1-1;
 pos4=pos4+1;
 pos2=pos2+1;
 pos3=pos3-1;

 break;

 //case 'r':
 //pos1=pos5;
 //pos2=pos5;
 //pos3=pos5;
 //pos4=pos5;

// break;
 
 default:
 pos1=pos5;
 pos2=pos5;
 pos3=pos5;
 pos4=pos5;
 
  
}

}



//else
//{ 

//if (aX<0)
//{
  //pos1=pos1+1;
  //pos4=pos4+1;
  //pos2=pos2-1;
  //pos3=pos3-1;
 //myservo1.write(pos1);
 //myservo2.write(pos2);
 //myservo3.write(pos3);
 //myservo4.write(pos4);
  
//}

//if (aX>0)
//{
  //pos1=pos1-1;
  //pos4=pos4-1;
  //pos2=pos2+1;
  //pos3=pos3+1;
 //myservo1.write(pos1);
 //myservo2.write(pos2);
 //myservo3.write(pos3);
 //myservo4.write(pos4);
  
//}


 
//if (aY<0)
//{
  //pos1=pos1-1;
  //pos4=pos4+1;
  //pos2=pos2-1;
  //pos3=pos3+1;
 //myservo1.write(pos1);
 //myservo2.write(pos2);
 //myservo3.write(pos3);
 //myservo4.write(pos4);
  
//}

//if (aY>0)
//{
 // pos1=pos1+1;
  //pos4=pos4-1;
  //pos2=pos2+1;
  //pos3=pos3-1;
 //myservo1.write(pos1);
 //myservo2.write(pos2);
 //myservo3.write(pos3);
 //myservo4.write(pos4);
  
//}
//}


 myservo1.write(pos1);
 myservo2.write(pos2);
 myservo3.write(pos3);
 myservo4.write(pos4);

 
 pos1=pos5;
 pos2=pos5;
 pos3=pos5;
 pos4=pos5;
  

  
  // delay
  delay(100);


}
