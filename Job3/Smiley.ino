#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largeur de l'afficheur OLED, en pixels
#define SCREEN_HEIGHT 32 // Hauteur de l'afficheur OLED, en pixels

// Déclaration pour un afficheur SSD1306 connecté en I2C (broches SDA, SCL)
#define OLED_RESET -1 // Broche de réinitialisation (ou -1 si partageant la broche de réinitialisation Arduino)
#define SCREEN_ADDRESS 0x3C ///< Voir la datasheet pour l'adresse; 0x3D pour 128x64, 0x3C pour 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // Initialisation de l'afficheur SSD1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec d'allocation SSD1306"));
    for (;;); // Boucle infinie si l'initialisation échoue
  }

  // Dessin du smiley
  display.clearDisplay();
  display.drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, SSD1306_WHITE); // Tête
  display.drawCircle(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 2 - 3, 2, SSD1306_WHITE); // Oeil gauche
  display.drawCircle(SCREEN_WIDTH / 2 + 3, SCREEN_HEIGHT / 2 - 3, 2, SSD1306_WHITE); // Oeil droit
  display.drawTriangle(SCREEN_WIDTH / 2 - 4, SCREEN_HEIGHT / 2 + 3, SCREEN_WIDTH / 2 + 4, SCREEN_HEIGHT / 2 + 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 7, SSD1306_WHITE); // Bouche
  display.display(); // Affichage du smiley

}

void loop() {
  // Rien à faire dans la boucle principale
}
