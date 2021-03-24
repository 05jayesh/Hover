
#include<Servo.h>
Servo motor1;
int value=55;
int val=0;
char command;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
motor1.attach(5);
delay(1);
motor1.write(10);
delay(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available()>0)
{
 int command= Serial.read();

  switch(command)
  {
   case 'w':
   value=value+2;
   break;
   case 's':
   value=value-2;
   break;
   case 'x':
   value=value-4;
   break;
   default:
   value=value;
  }
motor1.write(value);
Serial.print(value);
Serial.println();
delay(500);
}
}
