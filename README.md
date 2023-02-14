# OTA Web Server per ESP8266

Questo progetto consiste in un server OTA Python e un client ESP8266 che consente di selezionare, modificare e caricare il codice su dispositivi ESP8266 tramite una app web.

## Server OTA Python

Il server OTA Python fornisce un'interfaccia web per selezionare, modificare e caricare il codice su dispositivi ESP8266. Il server fornisce due endpoint:

- `GET /code`: restituisce il codice attualmente caricato sul dispositivo ESP8266
- `POST /upload`: riceve il nuovo codice caricato dal dispositivo ESP8266

### Dipendenze

Il server richiede l'installazione di Python 3 e le seguenti librerie Python:

- Flask
- Flask-RESTful

### Utilizzo

Per avviare il server OTA Python, eseguire il file `server.py`:

```bash
python3 server.py
