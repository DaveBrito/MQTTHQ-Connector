#include <WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Parâmetros do servidor MQTT
#define MQTT_CLIENT_ID "micropython-weather-demo"
#define MQTT_BROKER    "public.mqtthq.com"
#define MQTT_USER      ""
#define MQTT_PASSWORD  ""
#define MQTT_TOPIC     "mqttHQ-client-testt"

// Definições dos pinos do LCD
#define SDA_PIN        21
#define SCL_PIN        22
#define DHT_PIN        15

// Objetos de comunicação WI-FI no dispositivo ESP32.
WiFiClient espClient;   // Comunica com o WI-FI
PubSubClient client(espClient);   // Comunica com o MQTT usando o espClient acima.

LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C e tamanho do LCD
DHT dht(DHT_PIN, DHT22);    // cria objeto sensor DHT22

// callback executa quando uma mensagem é recebida no tópico das configurações iniciais.
void callback(char* topic, byte* payload, unsigned int length) {
  lcd.clear();  //limpa tela do LCD
  lcd.setCursor(0, 0);
  lcd.print("Mensagem recebida:");
  lcd.setCursor(0, 1);
  
  // Converter o payload em uma string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Analisa a string JSON para obter os valores de temperatura e umidade
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);
  if (error) {
    Serial.print("deserializeJson() falhou: ");
    Serial.println(error.c_str());
    return;
  }

  // Extrair os valores de temperatura e umidade do documento JSON
  float temperature = doc["temp"];
  float humidity = doc["humidity"];

  // Exibir no LCD
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C, UR: ");
  lcd.print(humidity);
  lcd.print("%");
}

void setup() {
  //Taxa de baud para comunicação serial.
  Serial.begin(115200);

  // Inicialização do LCD
  lcd.init();
  lcd.backlight();
   // Exibe "Conectando wi-fi ...." enquanto se conecta ao Wi-Fi
  lcd.setCursor(0, 0);
  lcd.print("Conectando");
  lcd.setCursor(0, 1);
  lcd.print("wi-fi ....");

  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  // Exibe "Conectando MQTT ...." enquanto se conecta ao MQTT
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando");
  lcd.setCursor(0, 1);
  lcd.print("MQTT ....");

  client.setServer(MQTT_BROKER, 1883); // Configura o servidor MQTT e a port
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectado ao MQTT");
  lcd.clear();
  // Medir temperatura e umidade
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Exibir no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("UR: ");
  lcd.print(humidity);
  lcd.print("%");

  // Formatar a mensagem como JSON
  StaticJsonDocument<200> doc;
  doc["temp"] = temperature;
  doc["humidity"] = humidity;
  char buffer[256];
  serializeJson(doc, buffer);

  // Enviar para o servidor MQTT
  client.publish(MQTT_TOPIC, buffer);

  delay(9000); // Aguarda 9 segundos antes de enviar o próximo dado
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Conectado");
      client.subscribe(MQTT_TOPIC);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Falha na conexao");
      delay(5000);
    }
  }
}
