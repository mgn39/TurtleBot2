#include <Arduino.h>
#include <ESP32Servo.h>

#define LED 13
#define SERVOMIN -300
#define SERVOMAX 1000

int blink_loop();     // in case we want it, eh

Servo servo;
int servo_pin = 25;    // A1, digital out w/ GPIO 2
int pos = 0;
int ADC_MAX = 4096;   // default ADC max value; ESP32s have a 12-bit ADC width opposed to Arduinos' 10-bit

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  servo.attach(servo_pin, SERVOMIN, SERVOMAX);
}

void loop() {
  // 0 to 180 degrees, will be triggered by a received signal
	for (pos = 0; pos <= 180; pos += 1) {
		servo.write(pos);
		delay(10);
	}
  Serial.println("resetting...");
}

// Function definitions
int blink_loop() {
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(1000);
}