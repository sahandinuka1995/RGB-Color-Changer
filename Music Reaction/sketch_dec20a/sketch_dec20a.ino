int soundsensor = 3;
int led1 = 9;
int led2 = 10;
int led3 = 11;      

int counter = 1;

// defining pin numbersvoid setup() 
void setup(){ 
  pinMode (soundsensor, INPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
}

void loop()
{
  int sensorvalue = digitalRead (soundsensor);            //if the sound intensity is higher than threshold which is set by us, 
  

  if(counter == 1){
    if (sensorvalue == 1){
     counter=counter+1; 
    digitalWrite(led1, LOW);
  }else{
    digitalWrite(led1, HIGH);
    delay(30);
  }
    }
    else if(counter == 2){
      if (sensorvalue == 1){
        counter=counter+1;
    digitalWrite(led2, LOW);
  }else{
    digitalWrite(led2, HIGH);
    delay(30);
  }
      }else if(counter == 3){
      if (sensorvalue == 1){
        counter=1;
    digitalWrite(led3, LOW);
  }else{
    digitalWrite(led3, HIGH);
    delay(30);
  }
      }
                                                          
                                                          
                                                       //then sensor would return the value as 1
  
  
}
