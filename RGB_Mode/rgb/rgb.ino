int s[] = {0,0,0};

#include <SoftwareSerial.h>
SoftwareSerial BLU(0,1);

#define redPin 9
#define greenPin 10
#define bluePin 11

int soundsensor = 3;
int counter = 1;

/*#include <IRremote.h>
#define off 16575
#define on 49215
#define r 8415
#define g 41055
#define b 24735
#define w 57375
#define smooth 53295

int receiver_pin = 8;

IRrecv receiver(receiver_pin);
decode_results output;*/

void setup() {
  Serial.begin(9600);
  Serial.println("-= HC-05 Bluetooth RGB LED =-");
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode (soundsensor, INPUT);

  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
  setColor(255, 255, 255);

//  receiver.enableIRIn();
}

int cmd;
void loop(){ 

  while(Serial.available() > 0){

  cmd = Serial.read();

    switch(cmd){
      case 'n':
      Serial.println("Normal Mode Activated");
      s[1]=0;
      s[2]=0;
      s[0]=1;
      
      f();
      delay(700);
      break;

      case 'm':
      Serial.println("Music Mode Activated");
      s[0]=0;
      s[2]=0;
      s[1]=1;
      f2();
      delay(700);
      break;

      case 'o':
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("All Off");
      f3();
      break;
      }
      
  }    
/*
  if (receiver.decode(&output)) {
unsigned int value = output.value;

switch(value) {

case off:
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("All Off");
      f3();
break;

case r:
digitalWrite(redPin, HIGH);
break;

case g:
digitalWrite(greenPin, HIGH);
break;

case b:
digitalWrite(bluePin, HIGH);
break;

case w:
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, HIGH);
digitalWrite(bluePin, HIGH);
break;

case smooth:
      Serial.println("Music Mode Activated");
      s[0]=0;
      s[2]=0;
      s[1]=1;
      f2();
      delay(700);
break;
}
Serial.println(value);
receiver.resume();
}
*/
} 

   void f(){
    
    
    while(s[0]==1){
      
  while (Serial.available() > 0)
  {
    int redInt = BLU.parseInt();
    int greenInt = BLU.parseInt();
    int blueInt = BLU.parseInt();

    redInt = constrain(redInt, 0, 255);
    greenInt = constrain(greenInt, 0, 255);
    blueInt = constrain(blueInt, 0, 255);

    if (Serial.available() > 0)
    {
      setColor(redInt, greenInt, blueInt);

      Serial.print("Red: ");
      Serial.print(redInt);
      Serial.print(" Green: ");
      Serial.print(greenInt);
      Serial.print(" Blue: ");
      Serial.print(blueInt);
      Serial.println();

      Serial.flush();
    }
  }
      loop();
      }
   }

   void f2(){
    while(s[1]==1){
      
  int sensorvalue = digitalRead (soundsensor); 
  
  if(counter == 1){
    if (sensorvalue == 1){
     counter=counter+1; 
    digitalWrite(redPin, LOW);
  }else{
    digitalWrite(redPin, HIGH);
    delay(30);
  }
    }
    else if(counter == 2){
      if (sensorvalue == 1){
        counter=counter+1;
    digitalWrite(greenPin, LOW);
  }else{
    digitalWrite(greenPin, HIGH);
    delay(30);
  }
      }else if(counter == 3){
      if (sensorvalue == 1){
        counter=1;
    digitalWrite(bluePin, LOW);
  }else{
    digitalWrite(bluePin, HIGH);
    delay(30);
  }
      }
      
      loop();
      }
   }

      void f3(){
    
      Serial.println("Off");
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      
   }


void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
