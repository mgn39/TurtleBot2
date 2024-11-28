#include <Arduino.h>
#include <ESP32Servo.h>
#include <RCSwitch.h>
#include <WiFi.h>
#include <string>

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

int setup_server(const char *ssid, const char *pass);
int run_server();

// servo
Servo servo;
int pos = 0;
int ADC_MAX = 4096; // default ADC max value; ESP32s have a 12-bit ADC width opposed to Arduinos' 10-bit

// RF receiver
RCSwitch mySwitch = RCSwitch();

// web server
WiFiServer server(80); // init on port 80
String header; // request header

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutConnectTime = 15000; // in ms
const long timeoutTime = 2000; // in ms

bool motorState = false;

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    servo.attach(SERVO, SERVOMIN, SERVOMAX);
    pinMode(RF, INPUT);
    mySwitch.enableReceive(digitalPinToInterrupt(RF));
    digitalWrite(LED, HIGH); // turn on LED

    // WiFi connection
    setup_server(SSID, PASSWORD);
}

void loop()
{
    // if (!moving && run_server() == 0) {
    //     Serial.println("Activating motor...");
    //     moving = true;
    // }
    run_server();
    
    // Switch
    Serial.println(digitalRead(21));
    if (mySwitch.available())
    {
        Serial.println("RF switch detected!");
        int value = mySwitch.getReceivedValue();
        if (value == 0)
        {
            Serial.println("Unknown signal");
        }
        else
        {
            Serial.print("Received value: ");
            Serial.println(value);
        }
        mySwitch.resetAvailable();
    }
    
    // Motor
    if (motorState) {
        digitalWrite(LED, HIGH);
        for (pos = 0; pos <= 180; pos += 1) {
            servo.write(pos);
            delay(10);
        }
        digitalWrite(LED, LOW);
        motorState = false;
    }
}

int setup_server(const char *ssid, const char *pass)
{
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    currentTime = millis();
    previousTime = currentTime;
    while (WiFi.status() != WL_CONNECTED && currentTime - previousTime <= timeoutConnectTime)
    {
        delay(500);
        Serial.print(".");
        currentTime = millis();
        if (currentTime - previousTime > timeoutConnectTime) {
            Serial.println("[ERROR] Cannot connect to WiFi.");
            return 1;
        }
    }
    Serial.print("Successfully connected to WiFi! \n IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    return 0;
}

int run_server() {
    WiFiClient client = server.available();   // Listen for incoming clients
    if (client) {                             // If a new client connects,
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
            currentTime = millis();
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) { // here we send an entire HTML response
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        // Turn GPIO on/off
                        if (header.indexOf("GET /actuate") >= 0 && !motorState) {
                            Serial.println("actuating...");
                            motorState = true;
                        }
                        
                        // HTML Head
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");

                        // HTML Body
                        client.println("<body><h1>ESP32 Web Server</h1>");
                        // Display current state and ON/OFF buttons
                        client.println("<p>Actuated: " + String(motorState) + "</p>");   
                        if (motorState) {
                            client.println("<p><a href=\"/26/off\"><button class=\"button\">ON</button></a></p>");
                        } else {
                            client.println("<p><a href=\"/26/on\"><button class=\"button button2\">OFF</button></a></p>");
                        } 
                        
                        // The HTTP response ends with another blank line
                        client.println();
                        break;
                    } else { // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    } else {
        return 1;
    }
    return 0;
}