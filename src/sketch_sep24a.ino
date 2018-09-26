#include <Arduino.h>


extern HardwareSerial Serial;

#define TRIGGER_PIN   12 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      11 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

void setup() {
    Serial.begin(115200);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    unsigned long pingTime;
    unsigned long maxPingTime = MAX_DISTANCE * 58;
    
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(4);             // Wait for pin to go low.
    digitalWrite(TRIGGER_PIN, HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
    delayMicroseconds(10);            // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
    digitalWrite(TRIGGER_PIN, LOW);
    
    pingTime = pulseIn(ECHO_PIN, HIGH, maxPingTime);
    Serial.println(pingTime/148);
    delay(50);
}

//boolean ping_trigger() {
//    digitalWrite(TRIGGER_PIN, LOW);   // Set the trigger pin low, should already be low, but this will make sure it is.
//    delayMicroseconds(4);             // Wait for pin to go low.
//    digitalWrite(TRIGGER_PIN, HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
//    delayMicroseconds(10);            // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
//    digitalWrite(TRIGGER_PIN, LOW);   // Set trigger pin back to low.
//
//    if (digitalRead(ECHO_PIN)) return false;                // Previous ping hasn't finished, abort.
//    _max_time = micros() + _maxEchoTime + MAX_SENSOR_DELAY; // Maximum time we'll wait for ping to start (most sensors are <450uS, the SRF06 can take up to 34,300uS!)
//    while (!digitalRead(ECHO_PIN))                          // Wait for ping to start.
//        if (micros() > _max_time) return false;             // Took too long to start, abort.
//}
