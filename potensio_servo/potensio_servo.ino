/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int mid = 90; //middle

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 250;           // interval at which to blink (milliseconds)

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(LED_BUILTIN, OUTPUT);
  //  Serial.begin(9600);
}

void blink() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BUILTIN, ledState);
  }
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(10);// waits for the servo to get there
  //  Serial.println(val);

  if (val < (mid - 10)) {
    blink();
  }
  else if (val > (mid + 10)) {
    blink();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
