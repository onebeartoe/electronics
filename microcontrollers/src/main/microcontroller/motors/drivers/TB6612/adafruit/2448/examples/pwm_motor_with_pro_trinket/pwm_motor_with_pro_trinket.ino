
// Setup the motor pins numbers.
#define MOTOR_A_INPUT_1 4
#define MOTOR_A_INPUT_2 8
#define MOTOR_A_PWM A3

// Set the modes for the motor pins.
void setup()
{
    Serial.begin(9600);

    pinMode(MOTOR_A_INPUT_1, OUTPUT);
    pinMode(MOTOR_A_INPUT_2, OUTPUT);

    digitalWrite(MOTOR_A_INPUT_1, HIGH);
    digitalWrite(MOTOR_A_INPUT_2, LOW);

    // set the motor to a low speed
    analogWrite(MOTOR_A_PWM, 135);
    delay(1000);
}

void loop()
{
    Serial.println("top of the loop");

    analogWrite(MOTOR_A_PWM, 255);
    delay(3000);
    
//    analogWrite(MOTOR_A_PWM, 222);
//    delay(4000);
    
    analogWrite(MOTOR_A_PWM, 128);
    delay(3000);
}
