#define RED_PIN   D0     // Pin para el color rojo
#define GREEN_PIN D1     // Pin para el color verde
#define BLUE_PIN  D2     // Pin para el color azul
#define BUTTON_PIN_FORWARD D5    // Pin para el botón de avanzar colores
#define BUTTON_PIN_BACKWARD D6   // Pin para el botón de retroceder colores

int currentColor = -1;  // Variable para realizar un seguimiento del color actual
int buttonStateForward = HIGH; // Variable para realizar un seguimiento del estado del botón de avanzar colores
int buttonStateBackward = HIGH; // Variable para realizar un seguimiento del estado del botón de retroceder colores
unsigned long lastDebounceTime = 0; // Último tiempo en que se detectó un cambio de estado en los botones
unsigned long debounceDelay = 50;    // Retardo de rebote

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN_FORWARD, INPUT_PULLUP); // Pin del botón de avanzar colores con resistencia pull-up interna
  pinMode(BUTTON_PIN_BACKWARD, INPUT_PULLUP); // Pin del botón de retroceder colores con resistencia pull-up interna
  setColor(0, 0, 0); // Inicializa el LED RGB con el color rojo
}

void loop() {
  int newButtonStateForward = digitalRead(BUTTON_PIN_FORWARD);
  int newButtonStateBackward = digitalRead(BUTTON_PIN_BACKWARD);

  if (newButtonStateForward != buttonStateForward) {
    lastDebounceTime = millis(); // Actualiza el tiempo de último rebote

    // Cambiar al siguiente color cuando dejas de presionar el botón de avanzar colores
    if (newButtonStateForward == HIGH) {
      currentColor++;
      if (currentColor > 10) {
        currentColor = 0;
      }
    }
  }

  if (newButtonStateBackward != buttonStateBackward) {
    lastDebounceTime = millis(); // Actualiza el tiempo de último rebote

    // Cambiar al color anterior cuando dejas de presionar el botón de retroceder colores
    if (newButtonStateBackward == HIGH) {
      currentColor--;
      if (currentColor < 0) {
        currentColor = 10;
      }
    }
  }

  // Cambiar el color del LED RGB según el valor de currentColor
  if (currentColor == 0) {
    setColor(255, 0, 0); // Rojo
  } else if (currentColor == 1) {
    setColor(255, 35, 0); // Naranja
  } else if (currentColor == 2) {
    setColor(255, 100, 0); // Amarillo
  } else if (currentColor == 3) {
    setColor(191, 255, 0); // Verde limón
  } else if (currentColor == 4) {
    setColor(0, 255, 0); // Verde
  } else if (currentColor == 5) {
    setColor(0, 255, 166); // Aguamarina
  } else if (currentColor == 6) {
    setColor(0, 255, 255); // Cian
  } else if (currentColor == 7) {
    setColor(67,124,255); // Azul índigo
  } else if (currentColor == 8) {
    setColor(148, 0, 211); // Violeta
  } else if (currentColor == 9) {
    setColor(255, 0, 255); // Magenta
  } else if (currentColor == 10) {
    setColor(255, 255, 255); // Blanco
  }

  buttonStateForward = newButtonStateForward;
  buttonStateBackward = newButtonStateBackward;
}

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}