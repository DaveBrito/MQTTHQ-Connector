# MQTTHQ-Connector

Este projeto demostra como conectar um ESP32 a uma rede WI-FI, para realizar a leitura da temperatura e umidade do sensor DHT22, através da comunicação MQTT para Publicar/Receber mensagens do Broker. 
Desenvolvimento realizado através de IDE online, Wokwi usado para Arduino e MQTTHQ para o Broker utilizado nesse projeto.


# Requisitos de Software
- [Arduino IDE](https://wokwi.com/)
- [Broker MQTT ](https://mqtthq.com/client)
- Bibliotecas: WiFi, Wire, ArduinoJson, PubSubClient, LiquidCrystal_I2C, DHT

# Instruções de Configuração:
1. Conecte o ESP32 à rede Wi-Fi.
2. Configure o Broker MQTT com as credenciais adequadas.
3. Instale as bibliotecas listadas no arquivo `libraries.txt`.
4. Abra o projeto no Wokwi e faça os ajustes necessários.
5. Carregue o código no ESP32 e inicie o monitor serial para verificar a conexão e os dados do sensor.

   
# Funcionamento
- O ESP32 conecta-se à rede Wi-Fi especificada.
- O sensor DHT22 é usado para ler a temperatura e umidade.
- As leituras são publicadas no broker MQTT e também são exibidas localmente.
- O ESP32 também pode receber mensagens do broker, que podem ser exibidas no dispositivo conectado.

# Observações:
Este código é uma demonstração e pode precisar de ajustes para funcionar em sua configuração específica.
Certifique-se de configurar corretamente as credenciais do Wi-Fi e do broker MQTT.
Teste o projeto em ambiente controlado para garantir seu funcionamento adequado antes de implantá-lo em produção.
