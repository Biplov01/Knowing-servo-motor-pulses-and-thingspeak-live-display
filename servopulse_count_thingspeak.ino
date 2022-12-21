#include <Servo.h>
#include<WiFi.h>
#include<ThingSpeak.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; 
int pin = 7;
int duration;


const char* ssid = "bipov_fiber";   // your network SSID 
const char* password = "kapan0";   // your network password

int dhtPin = 2;
#define dhtType DHT22

unsigned long myChannelNumber = 1790599;
const char* myWriteAPIKey = "Y13ES3PAQ04X46M6";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variables to store temperature and humidity
int temperature;
int humidity;

// Create a sensor object
WiFiClient  client;
void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
   myservo.attach(7);  // attaches the servo on pin 9 to the servo object
}

void loop() {
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees

    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  duration = pulseIn(pin, HIGH);
  Serial.println(duration);


   ThingSpeak.setField(1, duration);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

}
void wifiConnect(){
  Serial.println("Connecting to WiFi!");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}
