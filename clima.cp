#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <IRremote.h>


const char *ssid = "sua-rede-wifi";
const char *password = "sua-senha-wifi";


const char *apiKey = "sua-chave-api-openweathermap";


const int IR_RECEIVER_PIN = 2; // Pino do receptor infravermelho
const unsigned long IR_CODE = 0xFF6897; // Substitua pelo código do seu controle

// Defina o endereço I2C da tela OLED
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  connectWiFi();

  display.begin(SSD1306_I2C, SCREEN_ADDRESS);
  display.display();
  delay(1000);
  display.clearDisplay();

  IrReceiver.begin(IR_RECEIVER_PIN, false);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData == IR_CODE) {
      updateWeatherData();
      displayWeatherData();
    }
    IrReceiver.resume(); 
  }
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando à rede Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado à rede Wi-Fi");
}

void updateWeatherData() {
  
  String url = "http://api.openweathermap.org/data/2.5/weather?q=Cidade,País&appid=" + String(apiKey);
 
}

void displayWeatherData() {
 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Cidade: ");
  display.println("Nome da Cidade");
  display.print("Temperatura: ");
  display.println("Temperatura Atual");
  display.print("Clima: ");
  display.println("Condição do Tempo");
  display.print("Humidade: ");
  display.println("Porcentagem de Humidade");
  display.display();
}
