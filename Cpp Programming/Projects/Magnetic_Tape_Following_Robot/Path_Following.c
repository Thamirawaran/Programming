#include <avr/io.h>
#include <util/delay.h>

// Sensor pins on Arduino Mega
#define SENSOR1_PIN PD2  // Pin 8
#define SENSOR2_PIN PD3  // Pin 9
#define SENSOR3_PIN PE5  // Pin 10
#define SENSOR4_PIN PE4  // Pin 11

// Motor control pins
#define LEFT_MOTOR_PIN PD5   // Pin 5
#define RIGHT_MOTOR_PIN PD6  // Pin 6

// PID Constants
float Kp = 1.0; // Proportional
float Ki = 0.0; // Integral
float Kd = 0.0; // Derivative

// PID Variables
int16_t previous_error = 0;
int16_t integral = 0;

int max_pwm = 80;
int base_pwm = 20;

int offset = 10; // Positive value adjusts for left turning bias

// UART setup for serial communication
void uart_init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Enable transmitter
    UCSR0B = (1 << TXEN0);
    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to transmit a byte via UART
void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// Function to transmit a string via UART
void uart_transmit_string(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

// Function to transmit an integer via UART
void uart_transmit_int(int value) {
    char buffer[8];
    itoa(value, buffer, 10);
    uart_transmit_string(buffer);
}

// Setup motor pins
void setup_motors() {
    DDRD |= (1 << LEFT_MOTOR_PIN) | (1 << RIGHT_MOTOR_PIN); // Set motor pins as output
}

void setup_pwm() {
    // Set pins PH6 (OC2B), PH5 (OC4C), PH3 (OC4A), and PH4 (OC4B) as outputs
    DDRH |= (1 << PH6) | (1 << PH5) | (1 << PH3) | (1 << PH4);  // Set PH6, PH5, PH3, and PH4 as outputs

    // Configure Timer 2 for Fast PWM mode
    TCCR2A = (1 << WGM20) | (1 << COM2B1);  // Fast PWM, 8-bit, non-inverting mode for OC2B
    TCCR2B = (1 << CS21);    // Prescaler 8

    // Configure Timer 4 for Fast PWM mode, 8-bit
    TCCR4A = (1 << WGM40) | (1 << COM4A1) | (1 << COM4B1);  // Fast PWM, 8-bit, non-inverting modes for OC4A and OC4B
    TCCR4B = (1 << WGM42) | (1 << CS41);    // Fast PWM, prescaler 8

    // Initialize PWM duty cycles to 0
    OCR2B = 0;  // Forward PWM for left motor
    OCR4C = 0;  // Backward PWM for left motor
    OCR4A = 0;  // Forward PWM for right motor
    OCR4B = 0;  // Backward PWM for right motor
}


// Read sensor values and calculate the error
int16_t read_sensors() {
    uint8_t s1 = (PIND & (1 << SENSOR1_PIN)) ? 1 : 0;
    uint8_t s2 = (PIND & (1 << SENSOR2_PIN)) ? 1 : 0;
    uint8_t s3 = (PINE & (1 << SENSOR3_PIN)) ? 1 : 0;
    uint8_t s4 = (PINE & (1 << SENSOR4_PIN)) ? 1 : 0;

    int16_t error = (-15 * s1) + (-5 * s2) + (5 * s3) + (15 * s4);
    return error;
}

// Set motor speeds based on PID output
void set_motors(int16_t pid_output) {
    int16_t left_motor_speed = base_pwm - pid_output + offset;
    int16_t right_motor_speed = base_pwm + pid_output - offset;

    left_motor_speed = (left_motor_speed < 0) ? 0 : (left_motor_speed > max_pwm ? max_pwm : left_motor_speed);
    right_motor_speed = (right_motor_speed < 0) ? 0 : (right_motor_speed > max_pwm ? max_pwm : right_motor_speed);

    OCR0B = left_motor_speed;
    OCR0A = right_motor_speed;

    // Serial print for debugging
    uart_transmit_string("Error: ");
    uart_transmit_int(previous_error);
    uart_transmit_string(" | Left: ");
    uart_transmit_int(left_motor_speed);
    uart_transmit_string(" | Right: ");
    uart_transmit_int(right_motor_speed);
    uart_transmit_string("\r\n");
}

// void setup_pwm() {
//     // Setup Timer 0 for Fast PWM on Pins 5 and 6 (PD5, PD6)
//     TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);  // Fast PWM mode
//     TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler 64
// }

void set_right_motor_speed(int8_t speed) {
    if (speed >= 0) {
        // Forward direction
        OCR2B = (uint8_t)((speed / 100.0) * 255.0);  // Set forward PWM duty cycle
        OCR4C = 0;  // Set backward PWM duty cycle to 0
    } else {
        // Backward direction
        OCR2B = 0;  // Set forward PWM duty cycle to 0
        OCR4C = (uint8_t)((-speed / 100.0) * 255.0);  // Set backward PWM duty cycle
    }
}

void set_left_motor_speed(int8_t speed) {
    if (speed >= 0) {
        // Forward direction
        OCR4A = (uint8_t)((speed / 100.0) * 255.0);  // Set forward PWM duty cycle
        OCR4B = 0;  // Set backward PWM duty cycle to 0
    } else {
        // Backward direction
        OCR4A = 0;  // Set forward PWM duty cycle to 0
        OCR4B = (uint8_t)((-speed / 100.0) * 255.0);  // Set backward PWM duty cycle
    }
}


int main(void) {
    uart_init(8); // UBRR value for 115200 baud rate at 16 MHz
    setup_motors();
    setup_pwm();

    // Set sensor pins as input
    DDRD &= ~((1 << SENSOR1_PIN) | (1 << SENSOR2_PIN)); // Set pins 8 and 9 as input
    DDRE &= ~((1 << SENSOR3_PIN) | (1 << SENSOR4_PIN)); // Set pins 10 and 11 as input

    // Set pins 24, 25, 26, and 27 as outputs
    DDRA |= (1 << DDA4) | (1 << DDA5) | (1 << DDA2) | (1 << DDA3);  // Set PA4 and PA5 as outputs

    // Set pins 24, 25, 26, and 27 high
    PORTA |= (1 << PORTA4) | (1 << PORTA5) | (1 << PORTA2) | (1 << PORTA3);  // Set PA4 and PA5 high


    while (1) {
        int16_t error = read_sensors();

        integral += error;
        int16_t derivative = error - previous_error;
        int16_t pid_output = (Kp * error) + (Ki * integral) + (Kd * derivative);

        // set_motors(pid_output);

        set_left_motor_speed(base_pwm + pid_output);  // Set left motor speed to 20% forward
        set_right_motor_speed(base_pwm - pid_output); // Set right motor speed to 30% forward


        previous_error = error;

        _delay_ms(50);
    }
}
