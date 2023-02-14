from http.server import HTTPServer, BaseHTTPRequestHandler
import socketserver
import os

# Imposta la porta su cui ascoltare
PORT = 8000

# Imposta la cartella di lavoro corrente
WORKING_DIRECTORY = os.getcwd()

class OTARequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Ottieni il percorso richiesto dal client
        path = self.path

        # Se il client richiede il file di codice
        if path == "/code":
            # Apre il file di codice e lo legge
            with open("code.ino", "r") as file:
                code = file.read()
            
            # Invia la risposta al client
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(bytes(code, "utf-8"))
        else:
            # Altrimenti, invia una risposta di errore
            self.send_error(404)

    def do_POST(self):
        # Ottieni il percorso richiesto dal client
        path = self.path

        # Se il client sta cercando di caricare il codice
        if path == "/upload":
            # Ottiene il contenuto del file dal client
            content_length = int(self.headers["Content-Length"])
            post_data = self.rfile.read(content_length)
            
            # Scrive il contenuto del file su disco
            with open("code.ino", "w") as file:
                file.write(post_data.decode("utf-8"))
            
            # Invia una risposta di successo al client
            self.send_response(200)
        else:
            # Altrimenti, invia una risposta di errore
            self.send_error(404)

# Crea il server
httpd = socketserver.TCPServer(("", PORT), OTARequestHandler)

# Avvia il server
print("OTA server in ascolto sulla porta", PORT)
httpd.serve_forever()
