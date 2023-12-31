// Basic demo for accelerometer readings from Adafruit MPU6050
#include <FastLED.h>
#include <Adafruit_Sensor.h>

// How many leds are in the strip?
#define NUM_LEDS 60
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

sensors_event_t a, g, temp;

void setup(void) {

  setupLed();
  setupSensor();
}

float yaw = 0;
float pitch = 0;
float lastTime = 0;

void loop() {

  float dt = (millis() - lastTime) / 1000.f;
  lastTime = millis();

  yaw = yaw + dt * g.gyro.x * 2 * 3.141;

  // Serial.print("gyro_x:");
  // Serial.print(g.gyro.x);
  // Serial.print(",");
  // Serial.print("angle:");
  // Serial.println(yaw);


  // make all leds black
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB::Black;
  }



  int untilWhite = NUM_LEDS;  // min((int) (abs(g.gyro.x) / 10 * (float)NUM_LEDS), NUM_LEDS);

  for (int index = 0; index < untilWhite; index++) {


    // G, R, B
    leds[index].setHSV(
      int(yaw * 5) % 256,
      255,
      200);

    // leds[index].r = 127 + (g.gyro.x) * 50;
    // leds[index].g = 127 + (g.gyro.y) * 50;
    // leds[index].b = 127 + (g.gyro.z) * 50;
  }


  FastLED.show();
  
  loopSensor();
}