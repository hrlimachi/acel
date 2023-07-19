const int buttonPin = 2;  // Pin del botón
const int debounceDelay = 50;  // Tiempo de debounce en milisegundos

int buttonState = HIGH;  // Estado actual del botón
int lastButtonState = HIGH;  // Estado anterior del botón
unsigned long lastDebounceTime = 0;  // Último tiempo de debounce

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(2,OUTPUT);
  // Otras configuraciones...
}

void loop() {
  int reading = digitalRead(buttonPin); 

  // Verificar si el estado del botón ha cambiado
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Actualizar el último tiempo de debounce
  }

  // Verificar si ha pasado suficiente tiempo desde el último debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Actualizar el estado del botón
    if (reading != buttonState) {
      buttonState = reading;

      // Realizar acciones según el estado del botón
      if (buttonState == LOW) {
        // El botón ha sido presionado
        digitalWrite(2,HIGH);
        
      } else {
        // El botón ha sido liberado
        digitalWrite(2,LOW);
      }
    }
  }

  lastButtonState = reading;
  // Otras acciones...
}
