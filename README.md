# OTA Web Server in Python per Ubuntu e Client ESP8266

Questo progetto consiste in un server OTA (over-the-air) in Python per Ubuntu e un client ESP8266 in C, che permettono di selezionare, modificare e caricare il codice su dispositivi ESP8266 tramite una app web.

## Requisiti

- Ubuntu 18.04 o successivo
- Python 3.6 o successivo
- Flask
- PySerial
- ESP8266 board e il firmware [Arduino Core for ESP8266](https://github.com/esp8266/Arduino)
- [Arduino IDE](https://www.arduino.cc/en/software) (per caricare il firmware sulla scheda ESP8266)

## Installazione

1. Clona il repository su Ubuntu:

git clone https://github.com/tuore/ota-web-server.git


2. Installa Flask e PySerial:

pip3 install Flask PySerial


3. Carica il firmware [Arduino Core for ESP8266](https://github.com/esp8266/Arduino) sulla scheda ESP8266 tramite l'IDE di Arduino.

4. Modifica il file `ota_client.ino` nella cartella `esp8266_client` con il tuo SSID e password WiFi, quindi carica il codice sulla scheda ESP8266 tramite l'IDE di Arduino.

## Utilizzo

1. Avvia il server OTA Python:

python3 server.py

2. Apri il browser web e vai all'indirizzo [http://localhost:8000](http://localhost:8000) per accedere all'app web.

3. Seleziona il dispositivo ESP8266 dalla lista, quindi modifica il codice sorgente e fai clic sul pulsante "Carica" per caricare il nuovo codice sulla scheda ESP8266.

4. Il client ESP8266 si connette al server OTA e scarica il nuovo codice. Se il caricamento è stato completato con successo, la scheda ESP8266 si riavvia con il nuovo codice.

## Struttura del progetto

- `esp8266_client`: contiene il codice sorgente del client ESP8266.
- `ota_server`: contiene il codice sorgente del server OTA Python.
- `templates`: contiene il template HTML dell'app web.
- `static`: contiene i file statici (CSS e JavaScript) dell'app web.

## Contributi

Questo progetto è open-source e si accettano contributi! Se vuoi contribuire, fai una fork del repository e invia una pull request con le tue modifiche.

## Licenza

Questo progetto è rilasciato sotto la licenza MIT. Vedi il file LICENSE per maggiori dettagli.

Spero che questa wiki ti sia utile!
