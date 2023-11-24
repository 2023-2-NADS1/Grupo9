#define BLYNK_TEMPLATE_ID "TMPL2LOnGns6G"
#define BLYNK_TEMPLATE_NAME "datadump"
#define BLYNK_AUTH_TOKEN "YiXrm2fV-3t_O35MnPznObj__LBJq6sC"

#include <Ultrasonic.h>
#include "HX711.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#define BLYNK_PRINT Serial
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "ar";
char pass[] = "12345678";

const int echoPin = 12; // Pino digital utilizado pelo HC-SR04 Echo (recebe)
const int trigPin = 14; // Pino digital utilizado pelo HC-SR04 Trig (envia)

const int dtPin = 18;   // Pino digital do ESP32 conectado ao DT do HX711
const int sckPin = 4;   // Pino digital do ESP32 conectado ao SCK do HX711

const float profundidade = 22;
const float largura = 11;

Ultrasonic ultrasonic(trigPin, echoPin); // Inicializando os pinos do ESP32 para o sensor ultrassônico
HX711 scale;

void setup() {
  Serial.begin(115200); // Inicializa a porta serial
  scale.begin(dtPin, sckPin); // Inicializa o HX711 com os pinos corretos

  // // Configure a escala do HX711 para gramas
   scale.set_scale(152.5); 
    scale.tare();
    Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  // Mede a distância em centímetros
  float distancia = ultrasonic.read(CM);

  // Mede o peso em gramas
  float peso = scale.get_units(10); // 10 leituras para suavizar o resultado

if(peso <= 1) {
   peso = 0;
 } 

 float volume  = profundidade * largura * distancia;
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm | Peso: ");
  Serial.print(peso);
  Serial.print(" g | Volume:");
  Serial.print(volume/1000);
  Serial.println(" m³");

  Serial.println();
  Blynk.virtualWrite(V0,peso);
  Blynk.virtualWrite(V1,distancia);
  Blynk.virtualWrite(V2,volume/1000);
 
  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}

