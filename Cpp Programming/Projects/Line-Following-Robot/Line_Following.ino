#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4 
#define IR6 A5

#define RMotorA 2
#define RMotorB 3
#define RMotorPWM 9

#define LMotorA 4
#define LMotorB 5
#define LMotorPWM 10

include <NewPing.h>

#define TigFF  28
#define EchoFF    29
#define MDisFF 400 // Maximum distance we want to measure (in centimeters).

#define TigFR  30
#define EchoFR   31
#define MDisFR 400

#define TigFL  13
#define EchoFL   12
#define MDisFL 400

#define TigSR  34
#define EchoSR   35
#define MDisSR 400

#define TigSL  32
#define EchoSL   33
#define MDisSL 400


NewPing sonarFF(TigFF,EchoFF,MDisFF);
NewPing sonarFR(TigFR,EchoFR,MDisFR);
NewPing sonarFL(TigFL,EchoFL,MDisFL);
NewPing sonarSR(TigSR,EchoSR,MDisSR);
NewPing sonarSL(TigSL,EchoSL,MDisSL);

int DisFF,DisFL,DisFR,DisSR,DisSL;

int RMotor_1 =3;
int RMotor_2 =4;
int Rspeed=2;

int LMotor_1 =5;
int LMotor_2 =6;
int Lspeed=7;

int speedx=120;
int speedy=70;


//int MotorBaseSpeed = 100;
//int MaxSpeed= 150;

int IR_val[6]={0,0,0,0,0,0};
int IR_Weight= {-20, -10, -5, 5, 10, 20};

int LMotorSpeed =0;
int RMotorSpeed =0;
int SpeedAdjust=0;

float P,I,D;
float Error=0;
float PreviousError=0;
float Kp=0;
float Kd=0;
float Ki=0;


void setup(){
    Serial.begin(9600);
    pinMode(IR1,INPUT);
    pinMode(IR2,INPUT);
    pinMode(IR3,INPUT);
    pinMode(IR4,INPUT);
    pinMode(IR5,INPUT);
    pinMode(IR6,INPUT);

    pinMode(RMotor_1,OUTPUT);
    pinMode(RMotor_2,OUTPUT);
    pinMode(Rspeed,OUTPUT);

    pinMode(LMotor_1,OUTPUT);
    pinMode(LMotor_2,OUTPUT);
    pinMode(Lspeed,OUTPUT);
}

void forward(){
    analogWrite(Rspeed,speedx);
    analogWrite(Lspeed,speedx);

    digitalWrite(RMotor_1,HIGH);
    digitalWrite(RMotor_2,LOW);
    digitalWrite(LMotor_1,HIGH);
    digitalWrite(LMotor_2,LOW);
}

void turn_right(){
    analogWrite(Rspeed,speedy);
    analogWrite(Lspeed,speedy);

    digitalWrite(RMotor_1,HIGH);
    digitalWrite(RMotor_2,LOW);
    digitalWrite(LMotor_1,LOW);
    digitalWrite(LMotor_2,HIGH);    

}

void turn_left(){
    analogWrite(Rspeed,speedy);
    analogWrite(Lspeed,speedy);

    digitalWrite(RMotor_1,LOW);
    digitalWrite(RMotor_2,HIGH);
    digitalWrite(LMotor_1,HIGH);
    digitalWrite(LMotor_2,LOW);
}

void backward(){
    analogWrite(Rspeed,speedy);
    analogWrite(Lspeed,speedy);

    digitalWrite(RMotor_1,LOW);
    digitalWrite(RMotor_2,HIGH);
    digitalWrite(LMotor_1,LOW);
    digitalWrite(LMotor_2,HIGH);
}



void brake(){
    analogWrite(Rspeed,0);
    analogWrite(Lspeed,0);

    digitalWrite(RMotor_1,LOW);
    digitalWrite(RMotor_2,LOW);
    digitalWrite(LMotor_1,LOW);
    digitalWrite(LMotor_2,LOW);
    delay(400);
    
}
void turn_180(){
    analogWrite(Rspeed,speedy);
    analogWrite(Lspeed,speedy);

    digitalWrite(RMotor_1,LOW);
    digitalWrite(RMotor_2,HIGH);
    digitalWrite(LMotor_1,HIGH);
    digitalWrite(LMotor_2,LOW);
    delay(1200);

}


void PID_control(){
    Error=0;
    for(int i=0;i<6;i++){
        Error += IR_Weight[i]*IR_val[i];  
          }
    P=Error;
    I= I+Error;
    D=  Error - PreviousError;
    PreviousError = Error;

    SpeedAdjust=(Kp*p + Ki*I + Kd*D);
    LMotorSpeed = speedy - SpeedAdjust;
    RMotorSpeed = speedy + SpeedAdjust;

    if (LMotorSpeed <0 ){
        LMotorSpeed =0;
    }
    if (RMotorSpeed<0){
        RMotorSpeed=0;
    }
    if (LMotorSpeed > speedy){
        LMotorSpeed = speedy;
    }
    if (RMotorSpeed > speedy){
        RMotorSpeed > speedy;
    }
    analogWrite(Rspeed,RMotorSpeed);
    analogWrite(Lspeed,LMotorSpeed);

}
 
void read_IR(){
    IR_val[0] = digitalRead(IR1);
    IR_val[1] = digitalread(IR2);
    IR_val[2] = digitalRead(IR3);
    IR_val[3] = digitalRead(IR4);
    IR_val[4] = digitalRead(IR5);
    IR_val[5] = digitalRead(IR6);

} 



void loop() {

    read_IR();
   // if (IR_val[0]==0 && IR_val[1]==0 && IR_val[2]==0 && IR_val[3]==0 && IR_val[4]==0 && IR_val[5]==0 ){
   //     brake();
        //while(1){}

            }
    PID_control();

}

/*
void set_speed(){
    analogWrite(Rspeed,RMotorSpeed);
    analogWrite(Lspeed,LMotorSpeed);
}
*/
