/*
ENA:pin36
IN1:38
IN2:40
OpenSwitch:24
CloseSwitch:26
LED_G:30
LED_R:31
LED_W:28
Left-LimitSwitch:32 closed // N/C
Right-LimitSwitch:33 opened// N/C
AdultSensor:48
ChildSensor:49
Open window : in1 HIGH
Close window : in2 HIGH
*/

#define enA 36
#define in1 38
#define in2 40

#define OpenSwitch 24
#define CloseSwitch 26
#define L_Limit 32
#define R_Limit 33

#define LED_G 30
#define LED_R 31
#define LED_W 28

#define A_Sensor 48
#define C_Sensor 49

int motorSpeed = 0;


void setup() {
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_W,OUTPUT);
  
  pinMode(OpenSwitch,INPUT);
  pinMode(CloseSwitch,INPUT);
  pinMode(L_Limit,INPUT);
  pinMode(R_Limit,INPUT);
  pinMode(A_Sensor,INPUT);
  pinMode(C_Sensor,INPUT);

}

//my function//
void StopMotor(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_W, LOW);

  motorSpeed = 0;
  analogWrite(enA, motorSpeed);
}




//
void loop() {
  //digitalWrite(LED_G, LOW);
  //digitalWrite(LED_R, LOW);
  //digitalWrite(LED_W, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(A_Sensor, LOW);
  digitalWrite(C_Sensor, LOW);

  analogWrite(enA, motorSpeed);

////////////////////////////////////////////////////////////////////////////////////////
  //when turn on the power, if window at half way, the window will close first
  if ((digitalRead(OpenSwitch) == false) && (digitalRead(CloseSwitch) == false) && (digitalRead(L_Limit) == true) && (digitalRead(R_Limit) == true)){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_W, HIGH);

    motorSpeed = 255;
    analogWrite(enA, motorSpeed);
    //when window close, motor stop
    if (digitalRead(L_Limit) == false) {
      StopMotor();
      
    }
    
  }
  /*//if user did not close the window, after 5mins window will auto-close
  if ((digitalRead(OpenSwitch) == false) && (digitalRead(CloseSwitch) == false) && (digitalRead(AdultSensor) == false) && (digitalRead(ChildSensor)== false) && (digitalRead(L_Limit) == true) && (digitalRead(R_Limit) == false)){
    delay(5*60*1000);//delay 2mins
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,LOW);
    digitalWrite(LED_W,LOW);

    motorSpeed = 150;
    analogWrite(enA, motorSpeed);
    
  }*/
  //if window is closed, then do nothing
  if ((digitalRead(OpenSwitch) == false) && (digitalRead(CloseSwitch) == false) && (digitalRead(L_Limit) == false) && (digitalRead(R_Limit)== true)){
    StopMotor();
    
  }
  
  //when only use open switch to open the window
  if ((digitalRead(OpenSwitch) == true) && (digitalRead(CloseSwitch) == false) && (digitalRead(L_Limit) == false) && (digitalRead(R_Limit)== true)){
    
    //when the window hit the open limit switch, motor stopped
    while((digitalRead(R_Limit) == true)){
      
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);

      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_W, LOW);

      motorSpeed = 255;
      analogWrite(enA, motorSpeed);
      
    }
    StopMotor();
  }
  //when only use close switch to close window
  if ((digitalRead(OpenSwitch) == false) && (digitalRead(CloseSwitch) == true) && (digitalRead(L_Limit) == true) && (digitalRead(R_Limit)== false)){

    //when window closed, motor stopped
    while (digitalRead(L_Limit) == true){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_W, LOW);

      motorSpeed = 255;
      analogWrite(enA, motorSpeed);
    }
    StopMotor();
  }
  /*//when only adult pass 
  if ((digitalRead(OpenSwitch) == false) && (digitalRead(CloseSwitch) == false) && (digitalRead(A_Sensor) == false) && (digitalRead(C_Sensor)== false)){

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_W, HIGH);

    motorSpeed = 0;
    analogWrite(enA, motorSpeed);
  }*/
  /*//when only child pass, window close
  if ((digitalRead(R_Limit)== false) &&(digitalRead(A_Sensor) == false) && (digitalRead(C_Sensor)== true)){
    
    while (digitalRead(L_Limit) == true){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_W, HIGH);

      motorSpeed = 255;
      analogWrite(enA, motorSpeed);
    }
    StopMotor();
    
    
  }*/


}





















