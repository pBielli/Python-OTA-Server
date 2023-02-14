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
# OTA Web Server per ESP8266

Questo progetto consiste in un server OTA Python e un client ESP8266 che consente di selezionare, modificare e caricare il codice su dispositivi ESP8266 tramite una app web.

## Server OTA Python

Il server OTA Python fornisce un'interfaccia web per selezionare, modificare e caricare il codice su dispositivi ESP8266. Il server fornisce due endpoint:

- `GET /code`: restituisce il codice attualmente caricato sul dispositivo ESP8266
- `POST /upload`: riceve il nuovo codice caricato dal dispositivo ESP8266

```python
from flask import Flask, request
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

class Code(Resource):
    def get(self):
        with open('code.ino', 'r') as file:
            code = file.read()
        return {'code': code}

class Upload(Resource):
    def post(self):
        code = request.form['code']
        with open('code.ino', 'w') as file:
            file.write(code)
        return {'message': 'Code uploaded successfully'}

api.add_resource(Code, '/code')
api.add_resource(Upload, '/upload')

if __name__ == '__main__':
    app.run(port=8000, debug=True)
```

### Dipendenze

Il server richiede l'installazione di Python 3 e le seguenti librerie Python:

- Flask
- Flask-RESTful

### Utilizzo

Per avviare il server OTA Python, eseguire il file `server.py`:

```bash
python3 server.py
```

Il server verrà avviato sulla porta 8000.

## Client ESP8266

Il client ESP8266 si connette al server OTA Python e scarica il codice attualmente caricato sul server. Il client salva il codice sul disco utilizzando la libreria SPIFFS e invia una richiesta POST per indicare che il caricamento è stato completato.

```c
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "NOME RETE WIFI";
const char* password = "PASSWORD RETE WIFI";
const char* server = "INDIRIZZO IP DEL SERVER OTA";
const int port = 8000;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  WiFiClient client;
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
    client.println("GET /code HTTP/1.1");
    client.println("Host: " + String(server));
    client.println();
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }
    String code = client.readStringUntil('\0');
    if (code.length() > 0) {
      Serial.println("Code downloaded from server:");
      Serial.println(code);
      File file = SPIFFS.open("/code.ino", "w");
      file.print(code);
      file.close();
      client.println("POST /upload HTTP/1.1");
      client.println("Host: " + String
