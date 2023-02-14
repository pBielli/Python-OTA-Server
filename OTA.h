#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "nomedellawifi";
const char* password = "passworddellawifi";
const char* server = "192.168.1.100";  // IP del server OTA

class OTA {
  public:
    void connect() {
      // Connetti alla rete WiFi
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connettendo alla rete WiFi...");
      }
      
      Serial.println("Connesso alla rete WiFi!");
    }
    
    void update() {
      // Crea una connessione TCP con il server OTA
      WiFiClient client;
      if (client.connect(server, 8000)) {
        // Invia una richiesta GET per il file di codice
        client.println("GET /code HTTP/1.1");
        client.println("Host: 192.168.1.100");
        client.println("Connection: close");
        client.println();
        
        // Legge il contenuto del file di codice
        String code = "";
        while (client.connected()) {
          String line = client.readStringUntil('\n');
          if (line == "\r") {
            break;
          }
          code += line;
        }
        
        // Salva il codice su disco
        File file = SPIFFS.open("/code.ino", "w");
        file.println(code);
        file.close();
        
        // Invia una richiesta POST per indicare che il caricamento è stato completato
        client.println("POST /upload HTTP/1.1");
        client.println("Host: 192.168.1.100");
        client.println("Content-Type: text/plain");
        client.print("Content-Length: ");
        client.println(code.length());
        client.println("Connection: close");
        client.println();
        client.println(code);
        
        // Legge la risposta del server
        while (client.connected()) {
          String line = client.readStringUntil('\n');
          if (line == "\r") {
            break;
          }
        }
      }
    }
};
