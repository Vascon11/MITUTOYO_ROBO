# Projeto: Robô Sumo
Este repositório tem como objetivo fornecer uma base simples e reutilizável para quem deseja montar um robô sumô utilizando o ESP32 e controlar tudo via controle Bluetooth usando a biblioteca Bluepad32.
Se você está começando um projeto ou quer um código rápido para protótipos, este material serve como ponto de partida.

![https://github.com/Vascon11/MITUTOYO_ROBO/blob/main/imagens/imagens%20finalizada.jpeg?raw=true](https://raw.githubusercontent.com/Vascon11/MITUTOYO_ROBO/refs/heads/main/imagens/imagens%20finalizada.jpeg)

## Arquitetura do Robô
O robô utiliza o clássico driver de motor L298N, capaz de controlar dois motores DC simultaneamente. Além de fornecer controle de direção, esse módulo também disponibiliza uma saída regulada de 5V, que utilizamos para alimentar o VIN do ESP32 e funcionou perfeitamente.
Optamos por usar dois motores e um ponto de apoio traseiro (rampa/rodízio), o que permite ao robô mover-se para frente, para trás e realizar curvas sem complexidade adicional.
A alimentação vem de uma bateria de 12V / 2A, ligada através de uma chave para ligar/desligar todo o sistema.

Observação:
Os motores usados são indicados para cerca de 5–6V, então quando alimentados com 10–11V, a vida útil tende a diminuir. Para uma competição rápida, isso não deve ser um problema, mas se preferir, você pode adicionar um resistor ou regulador DC-DC step-down para manter os 6V seguros.

## Um detalhe importante sobre o ESP32
Durante os testes, percebemos uma característica interessante:
Quando ligamos o ESP32 diretamente nos pinos de controle da ponte H, ele não conseguia ativar duas portas ao mesmo tempo.
Depois de investigação e vários testes, identificamos que a corrente retornava para o pino do ESP32, causando proteção interna e impedindo o acionamento.
A solução foi simples: colocar diodos nos sinais de direção.
No Arduino o problema não ocorreu, mas no ESP32 os diodos resolveram completamente.

![ttps://github.com/Vascon11/MITUTOYO_ROBO/blob/main/imagens/imagem%20circuito%20robo.jpeg?raw=true](https://github.com/Vascon11/MITUTOYO_ROBO/blob/main/imagens/imagem%20circuito%20robo.jpeg?raw=true)

## Bibliotecas e Configuração do Ambiente
Para compilar o código no Arduino IDE:
Adicionar URLs do gerenciador de placas
Vá em:
Arquivo → Preferências → URLs do Gerenciador de Placas Adicionais
Adicione estas URLs:
* https://arduino.esp8266.com/stable/package_esp8266com_index.json
* https://espressif.github.io/arduino-esp32/package_esp32_index.json
* https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
* https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

## Instalar bibliotecas
Depois:
Ferramentas → Gerenciador de Bibliotecas

Instale:
Bluepad32 for NINA-W10 boards
esp32_bluepad32
ESP32 by Espressif (versão recomendada: 1.0.3)
