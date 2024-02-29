// Définition des broches pour la LED et le bouton
const int ledPin = 12; // Broche pour la LED
const int buttonPin = 25; // Broche pour le bouton

// Variables pour gérer l'état du bouton
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Variables pour compter les appuis sur le bouton
int buttonPressCount = 0;
unsigned long buttonPressTime = 0;
unsigned long longPressTime = 3000; // Durée d'appui pour un appui prolongé

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Éteindre la LED par défaut
  pinMode(buttonPin, INPUT_PULLUP); // Utilisation de la résistance interne de pull-up
  Serial.begin(9600);
}

void loop() {
  // Lecture de l'état du bouton avec débouncing
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        buttonPressCount++;
        buttonPressTime = millis();
        Serial.print("Nombre d'appuis sur le bouton : ");
        Serial.println(buttonPressCount);
      } else {
        if ((millis() - buttonPressTime) > longPressTime) {
          buttonPressCount = 0; // Réinitialiser le compteur d'appuis pour un appui prolongé
        }
      }
    }
  }
  lastButtonState = reading;

  // Exécution des actions en fonction du nombre d'appuis sur le bouton
  switch (buttonPressCount) {
    case 1:
      digitalWrite(ledPin, HIGH); // Allumer la LED
      break;
    case 2:
      digitalWrite(ledPin, HIGH); // La LED reste allumée
      break;
    case 3:
      // La LED clignote indéfiniment
      while (true) {
        blinkLed();
        if (digitalRead(buttonPin) == LOW) {
          buttonPressCount = 0;
          digitalWrite(ledPin, LOW);
          break;
        }
      }
      break;
    default:
      // Appui prolongé : éteindre la LED
      digitalWrite(ledPin, LOW);
      break;
  }
}

// Fonction pour faire clignoter la LED
void blinkLed() {
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}

