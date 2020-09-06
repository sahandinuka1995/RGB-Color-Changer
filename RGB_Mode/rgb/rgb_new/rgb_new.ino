#include <SoftwareSerial.h>

int s[] = {0,0,0};

SoftwareSerial BLU(0,1);

#define redPin 9
#define greenPin 10
#define bluePin 11

int soundsensor = 3;
int counter = 1;

#include <IRremote.h>

const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  //Serial setup
  Serial.begin(9600);
  Serial.println("-= HC-05 Bluetooth RGB LED =-");


  BLU.begin(9600);
  BLU.println("-= HC-05 Bluetooth RGB LED =-");
  
 
  pinMode(4, OUTPUT);
 
  digitalWrite(4,HIGH);


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

  irrecv.enableIRIn();
  irrecv.blink13(true);
  
}

int cmd;

void loop()
{
while(Serial.available() > 0){

  cmd = Serial.read();

    switch(cmd){
      case 'n':
      Serial.println("Normal Mode Activated");
      s[1]=0;
      s[2]=0;
      s[0]=1;
      setColor(255, 255, 255);
      normal();
      delay(700);
      break;

      case 'm':
      Serial.println("Music Mode Activated");
      s[0]=0;
      s[2]=0;
      s[1]=1;
      music();
      delay(700);
      break;

      case 'o':
      s[0]=0;
      s[1]=0;
      s[2]=1;
      Serial.println("All Off");
      f3();
      break;
      }
      
  }


      if (irrecv.decode(&results)){
        String c = String(results.value, HEX);
        Serial.println(c);
        char cs;
        
       if(c != "ffffffff"){
         if(c=="f7c03f"){
          cs='b';
          }else{
            }

          if(c=="f7e817"){
          cs='m';
          }else{
            }

          if(c=="f740bf"){
          cs='o';
          }else{
            }

          if(c=="f720df"){
          cs='r';
          }else{
            }

          if(c=="f7a05f"){
          cs='g';
          }else{
            }

          if(c=="f7609f"){
          cs='k';
          }else{
            }

          if(c=="f7e01f"){
          cs='w';
          }else{
            }
        }

          
          irrecv.resume();
          
      switch(cs){
      case 'b':
      Serial.println("Normal Mode Activated");
      s[1]=0;
      s[2]=0;
      s[0]=1;
      
      normal();
      delay(700);
      break;

      case 'm':
      Serial.println("Music Mode Activated");
      s[0]=0;
      s[2]=0;
      s[1]=1;
      music();
      delay(700);
      break;

      case 'o':
      s[0]=0;
      s[1]=0;
      s[2]=1;
      Serial.println("All Off");
      f3();
      break;

      case 'r':
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("Red");
      setColor(255, 0, 0);
      break;

      case 'g':
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("Green");
      setColor(0, 255, 0);
      break;

      case 'k':
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("Blue");
      setColor(0, 0, 255);
      break;

      case 'w':
      s[0]=0;
      s[1]=0;
      s[2]=0;
      Serial.println("White");
      setColor(255, 255, 255);
      break;
      
      }
        
  }
}

void normal(){
  while(s[0]==1){
    while (BLU.available() > 0)
  {
    int redInt = BLU.parseInt();
    int greenInt = BLU.parseInt();
    int blueInt = BLU.parseInt();

    redInt = constrain(redInt, 0, 255);
    greenInt = constrain(greenInt, 0, 255);
    blueInt = constrain(blueInt, 0, 255);

    if (BLU.available() > 0)
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
  loop();
  }
  }

  void music(){
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
