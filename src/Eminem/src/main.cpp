#include <Arduino.h>
#include <ESP32Servo.h>
#include <RCSwitch.h>
#include <WiFi.h>
#include <string>
#include <PubSubClient.h>

// GPIO Pins
#define LED 13
#define SERVO 25
#define RF 34
// Servo Range
#define SERVOMIN -300
#define SERVOMAX 1000
// Network Credentials
#define SSID "G519A"
#define PASSWORD "Blocklab519a"
// MQTT Broker Settings
#define MQTT_BROKER "192.168.1.41"   // broker is desktop
#define MQTT_PORT 1883               // unencrypted port (8883 if encrypted later on)

int setup_server(const char *ssid, const char *pass);
int run_server();

// Servo
Servo servo;
int pos = 0;
int ADC_MAX = 4096; // default ADC max value; ESP32s have a 12-bit ADC width opposed to Arduinos' 10-bit
// RCSwitch rfReceiver = RCSwitch(); // RF Receiver

// WiFi and MQTT
WiFiClient espClient;
PubSubClient client(espClient);
bool activated = false;
const char* mqtt_topic_sub = "esp32/motor";
const char* mqtt_topic_pub = "esp32/doorbell";

// Function Prototypes
void setup_wifi();
void mqtt_callback(char* topic, byte* message, unsigned int length);
void reconnect();

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    servo.attach(SERVO, SERVOMIN, SERVOMAX);
    pinMode(RF, INPUT);
    // rfReceiver.enableReceive(digitalPinToInterrupt(RF));
    digitalWrite(LED, HIGH); // turn on LED

    // WiFi connection
    setup_wifi();
    client.setServer(MQTT_BROKER, MQTT_PORT);
    client.setCallback(mqtt_callback);
}

void loop() {
     // Ensure MQTT stays connected
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    client.publish(mqtt_topic_pub, "this is the msg from rf receiver");

    // Motor Logic
    if (activated) {
        digitalWrite(LED, HIGH);
        for (pos = 0; pos <= 180; pos += 1) {
            servo.write(pos);
            delay(10);
        }
        digitalWrite(LED, LOW);
        activated = false;
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

// MQTT Message Callback
void mqtt_callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
        messageTemp += (char)message[i];
    Serial.println(messageTemp);

    // Motor control
    if (String(topic) == mqtt_topic_sub) {
        if (messageTemp == "on") {
            Serial.println("Turning motor ON");
            activated = true;
        } else if (messageTemp == "off") {
            Serial.println("Turning motor OFF");
            activated = false;
        }
    }
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
