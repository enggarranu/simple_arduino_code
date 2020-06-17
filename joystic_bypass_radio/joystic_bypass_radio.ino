#include <SPI.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;

struct Signal
{
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};

Signal data;

void ResetData()
{
  data.throttle = 127; // Motor Stop (254/2=127)| Motor Kapalı (Signal lost position | sinyal kesildiğindeki pozisyon)
  data.pitch = 127;    // Center | Merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
  data.roll = 127;     // Center | merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
  data.yaw = 127;      // Center | merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
}

void setup()
{
  //    Serial.begin(9600);

  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);

  ResetData();
}

// Joystick center and its borders | Joystick merkez ve sınırları
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if (val < middle)
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return (reverse ? 255 - val : val);
}

void loop()
{
  // Control Stick Calibration | Kumanda Kol Kalibrasyonları
  // Setting may be required for the correct values of the control levers. | Kolların doğru değerleri için ayar gerekebilir.
  data.throttle = mapJoystickValues(analogRead(A0), 524, 524, 1015, true);
  data.roll = mapJoystickValues(analogRead(A1), 12, 524, 1020, true); // "true" or "false" for servo direction | "true" veya "false" servo yönünü belirler
  data.pitch = mapJoystickValues(analogRead(A2), 2, 515, 1022, true); // "true" or "false" for servo direction | "true" veya "false" servo yönünü belirler
  data.yaw = mapJoystickValues(analogRead(A3), 12, 524, 1020, true);  // "true" or "false" for servo direction | "true" veya "false" servo yönünü belirler

  ch_width_1 = map(data.throttle, 0, 255, 1000, 2000); // pin D2 (PWM signal)
  ch_width_2 = map(data.pitch, 0, 255, 750, 2250);     // pin D3 (PWM signal)
                                                       //  ch_width_2 = map(data.pitch, 0, 255, 1000, 2000);    // pin D3 (PWM signal)
  ch_width_3 = map(data.roll, 0, 255, 1000, 2000);     // pin D4 (PWM signal)
  ch_width_4 = map(data.yaw, 0, 255, 1000, 2000);      // pin D5 (PWM signal)

  // Write the PWM signal | PWM sinyaller çıkışlara gönderiliyor
  ch1.writeMicroseconds(ch_width_1);
  ch2.writeMicroseconds(ch_width_2);
  ch3.writeMicroseconds(ch_width_3);
  ch4.writeMicroseconds(ch_width_4);
  //    Serial.println(analogRead(A2));
}
