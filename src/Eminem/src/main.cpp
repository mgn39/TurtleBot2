#include <Arduino.h>
#include <ESP32Servo.h>
#include <RCSwitch.h>
#include <WiFi.h>
#include <string>
#include <PubSubClient.h>

// GPIO Pins
#define LED_PIN 13
#define SERVO_PIN 25
#define RF_PIN 7
// Servo Range
#define SERVOMIN -300
#define SERVOMAX 1000
// Network Credentials
#define SSID "G519A"
#define PASSWORD "Blocklab519a"
// MQTT Broker Settings
#define MQTT_BROKER "192.168.0.41"   // broker is desktop
#define MQTT_PORT 1883               // unencrypted port (8883 if encrypted later on)

int setup_server(const char *ssid, const char *pass);
int run_server();

// Servo
Servo servo;
int pos = 0;
int ADC_MAX = 4096; // default ADC max value; ESP32s have a 12-bit ADC width opposed to Arduinos' 10-bit
RCSwitch mySwitch = RCSwitch();

// WiFi and MQTT
WiFiClient espClient;
PubSubClient client(espClient);
bool activated = false;
const char* mqtt_topic_sub = "esp32/door";
const char* mqtt_topic_pub = "esp32/doorbell";

// Function Prototypes
void setup_wifi();
void mqtt_callback(char* topic, byte* message, unsigned int length);
void reconnect();

// Misc
unsigned long startTime = millis();
unsigned long currTime = startTime;
const unsigned int interval = 5000; // in ms

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    servo.attach(SERVO_PIN, SERVOMIN, SERVOMAX);
    mySwitch.enableReceive(RF_PIN);

    // WiFi connection
    setup_wifi();
    client.setServer(MQTT_BROKER, MQTT_PORT);
    client.setCallback(mqtt_callback);
}

void loop() {
    currTime = millis();

     // MQTT
    if (!client.connected()) // ensures MQTT remains connected
        reconnect();
    client.loop();
    if (currTime - startTime > interval) {  // for testing purposes, send signal every 2s
        client.publish(mqtt_topic_pub, "beep");
        Serial.println("beep sent");
        startTime = currTime;
    }

    // Servo
    if (activated) {
        digitalWrite(LED_PIN, HIGH);
        for (pos = 0; pos <= 180; pos += 1) {
            servo.write(pos);
            delay(10);
        }
        digitalWrite(LED_PIN, LOW);
        activated = false;
    }

    // RF Receiver
    if (mySwitch.available()) {
        Serial.print("zamn");
        long receivedValue = mySwitch.getReceivedValue();
        
        if (receivedValue != 0) {
            Serial.print("Received Signal: ");
            Serial.print(receivedValue);
            Serial.print(" / ");
            Serial.print(mySwitch.getReceivedBitlength());
            Serial.print("bit ");
            Serial.print("Protocol: ");
            Serial.println(mySwitch.getReceivedProtocol());
            
            mySwitch.resetAvailable();
        }
    }
}

// Connect to WiFi
void setup_wifi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi!");
}

// Message callback
void mqtt_callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);

    // There's only one message that'll ever be received, which is to open the door
    if (topic == mqtt_topic_sub)
        activated = true;
}

// Reconnect to MQTT Broker
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
            client.subscribe(mqtt_topic_sub); // Subscribe to the control topic
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
