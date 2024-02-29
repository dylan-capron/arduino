#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LED        23
#define NUMPIXELS      16
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1

Adafruit_BME280 bme;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  pixels.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Temperature: " + String(temperature) + " C");
  display.println("Humidity: " + String(humidity) + " %");
  display.println("Pressure: " + String(pressure) + " hPa");
  display.display();

  displayBarGraph(temperature, pixels.Color(255, 0, 0)); // Red for temperature
  delay(5000); // Wait for 5 seconds

  displayBarGraph(humidity, pixels.Color(0, 0, 255)); // Blue for humidity
  delay(5000); // Wait for 5 seconds

  displayBarGraph(pressure, pixels.Color(0, 255, 0)); // Green for pressure
  delay(5000); // Wait for 5 seconds
}

void displayBarGraph(float value, uint32_t color) {
  int pixelsToLight = map(value, 0, 100, 0, NUMPIXELS);

  pixels.clear();

  for (int i = 0; i < pixelsToLight; i++)
    pixels.setPixelColor(i, color);

  pixels.show();
}
