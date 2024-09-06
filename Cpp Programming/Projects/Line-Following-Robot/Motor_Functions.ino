#include <AFMotor.h>
int H_Speed=120;
int L_Speed=180;

AF_DCMotor R_Motor(1);
AF_DCMotor L_Motor(3);

void brake(){
    R_Motor.setSpeed(0);
    L_Motor.setSpeed(0);
}

void forward(){
    R_Motor.setSpeed(H_Speed);
    L_Motor.setSpeed(H_Speed);
    R_Motor.run(FORWARD);
    L_Motor.run(FORWARD);

}

void backward(){
    R_Motor.setSpeed(L_Speed);
    L_Motor.setSpeed(L_Speed);
    R_Motor.run(BACKWARD);
    L_Motor.run(BACKWARD);
}

void turn_180(){
    R_Motor.setSpeed(L_Speed);
    L_Motor.setSpeed(0);
    R_Motor.run(FORWARD);
    
}

void turn_right(){
    R_Motor.setSpeed(L_Speed);
    L_Motor.setSpeed(L_Speed);
    R_Motor.run(FORWARD);
    L_Motor.run(BACKWARD);

}

void turn_left(){
    R_Motor.setSpeed(L_Speed);
    L_Motor.setSpeed(L_Speed);
    R_Motor.run(BACKWARD);
    L_Motor.run(FORWARD);

}
