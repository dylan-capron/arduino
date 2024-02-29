#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_NeoPixel.h>

#define PIN            23
#define NUMPIXELS      16

Adafruit_BME280 bme;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  pixels.begin();
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  displayBarGraph(map(temperature, 0, 30, 0, NUMPIXELS), pixels.Color(255, 0, 0)); // Red for temperature
  delay(5000); // Wait for 5 seconds

  displayBarGraph(map(humidity, 0, 100, 0, NUMPIXELS), pixels.Color(0, 0, 255)); // Blue for humidity
  delay(5000); // Wait for 5 seconds

  displayBarGraph(map(pressure, 950, 1200, 0, NUMPIXELS), pixels.Color(0, 255, 0)); // Green for pressure
  delay(5000); // Wait for 5 seconds
}

void displayBarGraph(int pixelsToLight, uint32_t color) {
  pixels.clear();

  for(int i=0; i<pixelsToLight; i++)
    pixels.setPixelColor(i, color);

  pixels.show();
}
