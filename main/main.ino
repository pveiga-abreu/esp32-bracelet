#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int greenLed = 12;
int redLed = 13;
int vibratingMotor = 2;

char feeling = 'x';

void setup() {
  // Configurando comunicacao serial
  Serial.begin(115200);
  
  // Configurando bluetooth
  SerialBT.begin("ESP32_Paulo_Victor");
  Serial.println("O dispositivo foi iniciado!");
  
  // Configurando os pinos como saída
  pinMode(vibratingMotor, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void negativeFeeling() {
  digitalWrite(redLed, HIGH);
  digitalWrite(vibratingMotor, HIGH);
  
  delay(400);
  
  digitalWrite(vibratingMotor, LOW);
  digitalWrite(redLed, LOW);
}

void positiveFeeling() {
  digitalWrite(greenLed, HIGH);
  delay(50);
  digitalWrite(vibratingMotor, HIGH);
  delay(50);
  digitalWrite(vibratingMotor, LOW);
  delay(50);
  digitalWrite(vibratingMotor, HIGH);
  delay(50);
  digitalWrite(vibratingMotor, LOW);
  delay(50);
  digitalWrite(vibratingMotor, HIGH);
  delay(50);
  digitalWrite(vibratingMotor, LOW);
  delay(100);
  digitalWrite(greenLed, LOW);
}

void loop() {
  if (SerialBT.available()) {
    feeling = SerialBT.read();
  }

  if (feeling == 'p') {
    positiveFeeling();
    Serial.println("Positive");
    feeling = 'x';
  }
  if (feeling == 'n') {
    negativeFeeling();
    Serial.println("Negative");
    feeling = 'x';
  }
}
