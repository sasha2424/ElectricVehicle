
int REP = 3; //right encoder
volatile long RC; //right counter
int LEP = 2; //left encoder
volatile long LC; //left counter


int RightWheel1 = 32;
int RightWheel2 = 34;

int RightWheelSpeed = 44;

int LeftWheel1 = 40;
int LeftWheel2 = 42;

int LeftWheelSpeed = 46;

int heart = 13; // heart beat pin
int HEART_STATE = HIGH;
long timer = 0;



void setup() {
  RC = 0;
  LC = 0;

  pinMode(heart,OUTPUT);
   
  pinMode(RightWheel1,OUTPUT);
  pinMode(RightWheel2,OUTPUT);
  pinMode(RightWheelSpeed,OUTPUT);
  
  pinMode(LeftWheel1,OUTPUT);
  pinMode(LeftWheel2,OUTPUT);
  pinMode(LeftWheelSpeed,OUTPUT);
  
  pinMode(REP,INPUT_PULLUP);
  pinMode(LEP,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REP),rightCounter,CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEP),leftCounter,CHANGE);

  rightWheelStop();
  leftWheelStop();
  forward(rotationToTick(10),1000,1000,1.04);

}

void loop() {
  
  if(millis() - timer > 1000){
    timer = millis();
    HEART_STATE = HIGH + LOW - HEART_STATE;
    digitalWrite(heart,HEART_STATE);
  }
  
}


int rotationToTick(int k){
  return k*40;
}

void forward(int k,double speeduptime, double slowdowntime, double p){
  speedupwheels(speeduptime,p);

  double rightWheelScale=1;
  double leftWheelScale=1;
  if(p>1){
    leftWheelScale= 1-(p-1);
  } else{
    rightWheelScale=p;
  }
  
  int t = RC + LC;
  rightWheelForward(rightWheelScale);
  leftWheelForward(leftWheelScale);
  while(RC+LC - 2*t < k){
    
  }
  
  slowwheels(slowdowntime,p);
}


void speedupwheels(double t, double p){
  digitalWrite(LeftWheel1,HIGH);
  digitalWrite(LeftWheel2,LOW);
  digitalWrite(RightWheel1,HIGH);
  digitalWrite(RightWheel2,LOW);

  double rightWheelScale=1;
  double leftWheelScale=1;
  if(p>1){
    leftWheelScale= 1-(p-1);
  } else{
    rightWheelScale=p;
  }
  
  //start wheels at 0 speed
  analogWrite(RightWheelSpeed,0);
  analogWrite(LeftWheelSpeed,0);

  //record starting time
  double start = millis();

  //loop while speeding up wheels over given amount of time
  while(millis() - start < t){
    double f = (millis() - start)/t;
    analogWrite(RightWheelSpeed,((double)255)*f*rightWheelScale);
    analogWrite(LeftWheelSpeed,((double)255)*f*leftWheelScale);
  }

  //set wheels to full speed
  analogWrite(RightWheelSpeed,255*rightWheelScale);
  analogWrite(LeftWheelSpeed,255*leftWheelScale);
}

void slowwheels(double t, double p){

  double rightWheelScale=1;
  double leftWheelScale=1;
  if(p>1){
    leftWheelScale= 1-(p-1);
  } else{
    rightWheelScale=p;
  }
  
  analogWrite(RightWheelSpeed,255*rightWheelScale);
  analogWrite(LeftWheelSpeed,255*leftWheelScale);
  
  double start = millis();
  
  while(millis() - start < t){
    double f = (millis() - start)/t;
    f = 1-f;
    analogWrite(RightWheelSpeed,((double)255)*f*rightWheelScale);
    analogWrite(LeftWheelSpeed,((double)255)*f*rightWheelScale);
  }
  
  //set wheel speed to 0
  analogWrite(RightWheelSpeed,0);
  analogWrite(LeftWheelSpeed,0);

  //turn off both wheels
  digitalWrite(RightWheel1,LOW);
  digitalWrite(RightWheel2,LOW);
  digitalWrite(LeftWheel1,LOW);
  digitalWrite(LeftWheel2,LOW);
}

void stopWheels(){
  rightWheelStop();
  leftWheelStop();
}

void rightRotate(int k, double p){
  int t = RC;
  rightWheelForward(p);
  while(RC-t < k){
    
  }
  rightWheelStop();
}

void leftRotate(int k, double p){
  int t = LC;
  leftWheelForward(p);
  while(LC-t < k){
    
  }
  leftWheelStop();
}

void rightWheelStop(){
  digitalWrite(RightWheel1,LOW);
  digitalWrite(RightWheel2,LOW);
}

void leftWheelStop(){
  digitalWrite(LeftWheel1,LOW);
  digitalWrite(LeftWheel2,LOW);
}

void rightWheelForward(double p){
  analogWrite(RightWheelSpeed,255*p);
  digitalWrite(RightWheel1,HIGH);
  digitalWrite(RightWheel2,LOW);
}

void leftWheelForward(double p){
  analogWrite(LeftWheelSpeed,255*p);
  digitalWrite(LeftWheel1,HIGH);
  digitalWrite(LeftWheel2,LOW);
}

void rightWheelBackward(){
  digitalWrite(RightWheel1,LOW);
  digitalWrite(RightWheel2,HIGH);
}

void leftWheelBackward(){
  digitalWrite(LeftWheel1,LOW);
  digitalWrite(LeftWheel2,HIGH);
}

void rightCounter(){
  RC++;
}

void leftCounter(){
  LC++;
}

