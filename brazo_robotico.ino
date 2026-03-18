
![Diagrama de conexiones](diagrama_conexiones.png)

## 💻 Código

```cpp
/*
 * BRAZO ROBÓTICO CONTROLADO POR JOYSTICK
 * Controla 2 servos con un joystick analógico
 * 
 * Conexiones:
 * - Joystick VRx → A0
 * - Joystick VRy → A1
 * - Servo base → Pin 9
 * - Servo brazo → Pin 10
 * - LED → Pin 13
 */

#include <Servo.h>

// Crear objetos para los servos
Servo servoBase;
Servo servoBrazo;

// Pines
const int pinJoystickX = A0;
const int pinJoystickY = A1;
const int pinServoBase = 9;
const int pinServoBrazo = 10;
const int pinLED = 13;

// Variables para almacenar posiciones
int posBase = 90;      // Posición inicial
int posBrazo = 90;
int lecturaX, lecturaY;

void setup() {
  // Inicializar servos
  servoBase.attach(pinServoBase);
  servoBrazo.attach(pinServoBrazo);
  
  // Configurar pines
  pinMode(pinLED, OUTPUT);
  
  // Posición inicial
  servoBase.write(posBase);
  servoBrazo.write(posBrazo);
  
  // LED indica sistema listo
  digitalWrite(pinLED, HIGH);
  delay(1000);
  digitalWrite(pinLED, LOW);
  
  Serial.begin(9600); // Para debug opcional
}

void loop() {
  // Leer joystick
  lecturaX = analogRead(pinJoystickX);
  lecturaY = analogRead(pinJoystickY);
  
  // Mapear valores (0-1023 a 0-180 grados)
  // Invertimos X para control intuitivo
  int nuevoAnguloBase = map(lecturaX, 0, 1023, 180, 0);
  int nuevoAnguloBrazo = map(lecturaY, 0, 1023, 0, 180);
  
  // Aplicar suavizado (movimiento gradual)
  if (abs(nuevoAnguloBase - posBase) > 2) {
    if (nuevoAnguloBase > posBase) posBase++;
    else if (nuevoAnguloBase < posBase) posBase--;
    servoBase.write(posBase);
  }
  
  if (abs(nuevoAnguloBrazo - posBrazo) > 2) {
    if (nuevoAnguloBrazo > posBrazo) posBrazo++;
    else if (nuevoAnguloBrazo < posBrazo) posBrazo--;
    servoBrazo.write(posBrazo);
  }
  
  // LED parpadea durante movimiento
  digitalWrite(pinLED, HIGH);
  delay(5);
  digitalWrite(pinLED, LOW);
  
  // Pequeña pausa para estabilidad
  delay(10);
  
  // Debug opcional (descomentar para ver valores)
  /*
  Serial.print("X: ");
  Serial.print(lecturaX);
  Serial.print(" → Base: ");
  Serial.print(posBase);
  Serial.print(" | Y: ");
  Serial.print(lecturaY);
  Serial.print(" → Brazo: ");
  Serial.println(posBrazo);
  */
}
