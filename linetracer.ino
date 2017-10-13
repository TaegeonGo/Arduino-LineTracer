//HC02-48
#define TRIG 10
#define ECHO 11
//CDS
int bright = 0;
//TCRT5000-MODULE
int leftIR = 0; //left motor
int rightIR = 0; //right motor
//LED
int LED = 12;
//motor speed
int speedmotor = 90;
int cornerspeed = 100;
int lowerspeed = 50;
//motor stop
#define STOP 0

void setup() {
  //Serial start
  Serial.begin(9600);
  //CDS
  pinMode(16, INPUT);
  //HC02-48
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  //Ultrasonic Raning Module
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  //LED
  pinMode(LED, OUTPUT);
  //L298N-Module
  pinMode(3, OUTPUT); //left speed
  pinMode(4, OUTPUT); //left motor
  pinMode(5, OUTPUT); //left motor
  pinMode(6, OUTPUT); //right speed
  pinMode(7, OUTPUT); //right motor
  pinMode(9, OUTPUT); //right motor
}

void loop() {
  //CDS
  bright = analogRead(16);
  
  Serial.print(bright); //print CDS
  Serial.print("|");
  //HC02-48
  digitalWrite(TRIG, LOW);
  delay(0.0002);
  digitalWrite(TRIG, HIGH);
  delay(0.001);
  digitalWrite(TRIG, LOW);

  long distance = pulseIn(ECHO, HIGH)/58.2;
  Serial.print(distance); //print HC02-48
  Serial.print("|");
  //Ultrasonic Ranging Module
  rightIR = analogRead(15);
  leftIR = analogRead(14);
  Serial.print(rightIR); //print right motor
  Serial.println(" ");
  Serial.print(leftIR); //print left motor
  Serial.print(" ");
  
 
  stopmotor(); //motor stop
  if(bright > 190) { //when it's not tunnel
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }
  if(distance > 15){ //when it's tunnel
    if(leftIR > 400 && rightIR > 400){ //on a straight road
      //go straight
      go();
    }
    if(leftIR < 400 && rightIR > 400) { //on the left side of the road 
      //turn left
      leftTurn();
      
    }
    if(leftIR > 400 && rightIR < 400) { //on the right side of the road
      //turn right
      rightTurn();
      
    }
  }
}


void stopmotor() {
  //left motor
  analogWrite(3, STOP); //speed
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  //right motor
  analogWrite(9, STOP); //speed
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
void go() {
  //left motor
  analogWrite(3, speedmotor); //speed
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  //right motor
  analogWrite(9, speedmotor); //speed
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void leftTurn() {
  //left motor
  analogWrite(3,  lowerspeed); //speed
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  //right motor
  analogWrite(9, cornerspeed); //speed
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void rightTurn() {
  //left motor
  analogWrite(3, cornerspeed); //speed
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  //right motor
  analogWrite(9, lowerspeed); //speed
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
