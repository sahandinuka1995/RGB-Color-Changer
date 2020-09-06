#include <SoftwareSerial.h>

int soundsensor = 3;

int counter = 1;

SoftwareSerial BLU(0,1); // RX , TX

#define redPin 9
#define greenPin 10
#define bluePin 11

void setup() {
  //Serial setup
  Serial.begin(9600);
  Serial.println("-= HC-05 Bluetooth RGB LED =-");


  BLU.begin(9600);
  BLU.println("-= HC-05 Bluetooth RGB LED =-");
  
 pinMode (soundsensor, INPUT);
 



  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);


  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
  setColor(255, 255, 255);
  
}

void loop() {


    int inByte = Serial.read();
    
    switch (inByte) {
      case 'n':

      Serial.println("Normal Mode");
        
  while (Serial.available() > 0)
  {
    int redInt = BLU.parseInt();
    int greenInt = BLU.parseInt();
    int blueInt = BLU.parseInt();

    redInt = constrain(redInt, 0, 255);
    greenInt = constrain(greenInt, 0, 255);
    blueInt = constrain(blueInt, 0, 255);

    char c = BLU.read();
    char d = Serial.read();
    
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

      BLU.flush();
    }
  }
  
        break;
      case 'm':

      Serial.println("Music Mode");

    int sensorvalue = digitalRead (soundsensor);            //if the sound intensity is higher than threshold which is set by us, 
  

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
      
        break;
      
     
    }
  
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
