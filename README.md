## Descrição do Projeto:

O projeto demonstra a conexão de um ESP32 à rede Wi-Fi para coletar dados de temperatura e umidade do sensor DHT22.
Os dados coletados são publicados no MQTTHQ, um broker MQTT público, permitindo monitoramento remoto.
O projeto foi desenvolvido na IDE online Wokwi e utiliza o MQTTHQ como broker.
## Requisitos de Software:

Hardware: ESP32

### Software:
- IDE Arduino (Wokwi recomendado)
- Broker MQTT (MQTTHQ recomendado)
- Bibliotecas: WiFi, Wire, ArduinoJson, PubSubClient, LiquidCrystal_I2C, DHT

## Instruções de Configuração:

- Conectar o ESP32 à rede Wi-Fi
- As credenciais da rede Wi-Fi (SSID e senha) estão configuradas no código.
- **É fundamental a biblioteca WI-FI para conectar com o Broker, sem ele, não é possível entrar em contato.**

 ### Configurar o Broker MQTT:
 - Criar uma conta no MQTTHQ e obter as credenciais.
- Configure as credenciais do broker no código (port, mqtt_broker, mqtt_topic e mqtt_client_id).
```c
#define MQTT_CLIENT_ID "micropython-weather-demo" // Id aleatório gerado 
#define MQTT_BROKER    "public.mqtthq.com"
#define MQTT_USER      ""
#define MQTT_PASSWORD  ""
#define MQTT_TOPIC     "mqttHQ-client-testt" // Exemplo de topic
```

## Instalar as bibliotecas:
- As bibliotecas listadas no arquivo `libraries.txt` devem ser instaladas na IDE Arduino.
 ### Abrir o projeto no Wokwi:
- Carregar o código do projeto no Wokwi.
- Carregar o código no ESP32:
- Compilar e carregar o código no ESP32 usando a IDE Arduino.

## Observações Importantes:

A rede Wi-Fi é essencial para a comunicação MQTT entre o ESP32 e o broker.
O código contém comentários detalhados para auxiliar na compreensão e adaptação.
A configuração da rede Wi-Fi e do broker MQTT deve ser feita corretamente.
Teste o projeto em um ambiente controlado antes de implementá-lo em produção.

## Funcionamento Detalhado:

### Leitura de dados do sensor DHT22:
- O sensor DHT22 é utilizado para coletar dados de temperatura e umidade.
- A biblioteca DHT é utilizada para ler os valores do sensor e converte para JSON e exibe-as no Display/Broker.
### Envio de mensagens para o broker:
- A biblioteca PubSubClient é utilizada para se conectar ao broker MQTT.
- Os dados de temperatura e umidade são formatados em JSON e publicados no tópico especificado no código.
### Conversão e exibição de dados:
- A mensagem JSON recebida do broker é convertida em string para ser exibida no display LCD.
- A biblioteca ArduinoJson é utilizada para interpretar a string JSON e extrair os valores de temperatura e umidade.
### Envio de dados interpretados:
- Os valores interpretados de temperatura e umidade são enviados novamente para o broker MQTT.
## Visualização dos dados:
- Os dados de temperatura e umidade são exibidos no display LCD.
- Os dados também são publicados no broker MQTT e podem ser visualizados na interface do broker.
##  Testes e Verificação:
### Conexão correta:
- Se a conexão com a rede Wi-Fi e o broker MQTT estiver correta, os valores de temperatura e umidade devem ser exibidos no display LCD e no MQTTHQ.
### Verificação de dados:
- Compare os valores exibidos no display LCD com os valores no MQTTHQ para garantir a consistência dos dados.
### Resultado Esperado:
- Mesmas informações exibidas no display, deve ser exibidas no Broker.
<img src="https://github.com/DaveBrito/MQTTHQ-Connector/raw/main/mqtthq.png" width="90%" height="90%">

## Observações Adicionais:
Este código é um exemplo e pode precisar de ajustes para se adequar à sua configuração específica.
Certifique-se de que as credenciais da rede Wi-Fi e do broker MQTT estejam corretas.
Teste o projeto em um ambiente controlado para garantir seu funcionamento adequado antes de implementá-lo em produção.
