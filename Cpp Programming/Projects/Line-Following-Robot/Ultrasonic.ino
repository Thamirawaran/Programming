#include <NewPing.h>

#define TigFF  18
#define EchoFF    16
#define MDisFF 400 // Maximum distance we want to measure (in centimeters).

#define TigFR  18
#define EchoFR    16
#define MDisFR 400

#define TigFL  18
#define EchoFL    16
#define MDisFL 400

#define TigSR  18
#define EchoSR    16
#define MDisSR 400

#define TigSL  18
#define EchoSL    16
#define MDisSL 400


NewPing sonarFF(TigFF,EchoFF,MDisFF);
NewPing sonarFR(TigFR,EchoFR,MDisFR);
NewPing sonarFL(TigFL,EchoFL,MDisFL);
NewPing sonarSR(TigSR,EchoSR,MDisSR);
NewPing sonarSL(TigSL,EchoSL,MDisSL);

int DisFF,DisFL,DisFR,DisSR,DisSL;

int RMotor_1 =5;
int RMotor_2 =6;
int Rspeed=7;

int LMotor_1 =10;
int LMotor_2 =9;
int Lspeed=12;

int speedx=255;
int speedy=100;

void setup(){

    pinMode(RMotor_1,OUTPUT);
    pinMode(RMotor_2,OUTPUT);
    pinMode(LMotor_1,OUTPUT);
    pinMode(LMotor_2,OUTPUT);
    pinMode(Rspeed,OUTPUT);
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
    delay(800);

}

void loop(){
    forward();
   DisFF = sonarFF.ping_cm();
   DisFL = sonarFL.ping_cm();
   DisFR = sonarFR.ping_cm();
   DisSR = sonarSR.ping_cm();
   DisSL = sonarSL.ping_cm();

   if (DisFF <8 || DisFL < 8 || DisFR <8){
    if (DisFF >=8 && DisFL >=8){
        turn_left();
        delay(200);
    }
    else if (DisFF>=8 && DisFR >=8){
        turn_right();
        delay(200);
    }
    else if (DisFL >=8 && DisSL >=8){
        turn_left();
        delay(400);
    }
    else if (DisFR >=8 && DisSR>=8){
        turn_right();
        delay(400);
    }
    else{
        backward();
        delay(200);
        turn_180();

    }


    }

}
