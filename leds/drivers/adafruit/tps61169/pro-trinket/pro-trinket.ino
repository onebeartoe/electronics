
const int potPin = A0;      // Analog pin connected to the potentiometer's middle pin
const int pwmPin = 9;       // Digital PWM pin connected to the TPS61169's CTRL/DIM pin

void setup() {
 pinMode(pwmPin, OUTPUT); // Set the PWM pin as an output
 Serial.begin(9600);      // Initialize serial communication for debugging (optional)
}

void loop() {
 int potValue = analogRead(potPin); // Read the analog value from the potentiometer (0-1023)

 // Map the potentiometer value (0-1023) to the PWM range (0-255)
 int pwmValue = map(potValue, 0, 1023, 0, 255);

 analogWrite(pwmPin, pwmValue); // Write the PWM value to control the TPS61169

 // Optional: Print values to Serial Monitor for verification
// the next printlns are commented, since the Pro Trinket does not have a built in 
// serial connections; you have to connect an FTDI cable to achieve serial communication.
/*
 Serial.print("Potentiometer Value: ");
 Serial.print(potValue);
 Serial.print(", PWM Value: ");
 Serial.println(pwmValue);
*/

 delay(10); // Small delay for stable readings
}

