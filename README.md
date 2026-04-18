# ESP32 WebControl

Servidor web embarcado no ESP32 para controle de GPIO via navegador. Permite ligar/desligar um LED por rotas HTTP e serve como base para aplicações IoT mais completas.

## Visão geral

O projeto cria um servidor HTTP no ESP32 (porta 80). Ao acessar o IP do dispositivo na mesma rede Wi-Fi, o usuário visualiza uma página simples com ações para controlar um pino digital.

## Funcionalidades

* Conexão Wi-Fi (modo station)
* Servidor HTTP local (`WebServer`)
* Rotas:

  * `/` — página principal
  * `/on` — liga o LED
  * `/off` — desliga o LED
* Respostas HTML simples
* Controle de GPIO remoto

## Arquitetura (alto nível)

* Camada de rede: `WiFi.h` (DHCP, conexão)
* Camada HTTP: `WebServer.h` (roteamento e respostas)
* Aplicação: handlers de rota manipulando estado do GPIO

Fluxo:

1. Boot → conecta ao Wi-Fi
2. Inicia servidor HTTP
3. Define rotas e handlers
4. Loop atende requisições (`server.handleClient()`)

## Hardware

* ESP32 (ex: DevKit V1)
* LED
* Resistor 220Ω–330Ω
* Jumpers / protoboard

### Ligações

* LED anodo → GPIO 13 (padrão do exemplo) via resistor
* LED catodo → GND

> Ajuste o pino no código se necessário.

## Software / Requisitos

* Arduino IDE (ou PlatformIO)
* Core ESP32 instalado (Boards Manager)
* Bibliotecas:

  * `WiFi.h` (core ESP32)
  * `WebServer.h` (core ESP32)

## Configuração

No código, defina suas credenciais:

```cpp
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
```

Opcional:

```cpp
#define ledPin 13 // altere conforme seu hardware
```

## Execução

1. Compile e faça upload para o ESP32
2. Abra o Serial Monitor (115200 baud)
3. Aguarde a conexão e copie o IP exibido (ex: `192.168.0.105`)
4. No navegador (mesma rede), acesse:

   * `http://<IP>/`
   * `http://<IP>/on`
   * `http://<IP>/off`

## Endpoints

* `GET /` → HTML com links de controle
* `GET /on` → seta GPIO HIGH
* `GET /off` → seta GPIO LOW

## Estrutura de código (referência)

* `setup()`:

  * inicializa Serial
  * configura `pinMode`
  * conecta ao Wi-Fi
  * registra rotas (`server.on`)
  * `server.begin()`
* `loop()`:

  * `server.handleClient()`

## Troubleshooting

* **Não conecta ao Wi-Fi**: verifique SSID/senha, frequência 2.4 GHz, distância do roteador
* **IP não acessível**: dispositivo cliente deve estar na mesma rede; teste ping
* **LED não responde**: confirme pino correto, resistor, GND comum
* **Upload falha**: verifique driver USB (CH340/CP210x) e porta correta
* **Página não atualiza**: force refresh ou teste rotas diretas `/on` e `/off`

## Limitações

* HTTP síncrono (bloqueante)
* Sem autenticação
* HTML mínimo (sem CSS/JS estruturado)
