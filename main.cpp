#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <avr/pgmspace.h>

uint8_t ledRed = D7;
// uint8_t firstButton = D7;

const char* ssid = "WIFI-HAFIDH";
const char* password = "Hafidh1708";

// bool lastButtonState = LOW;
// bool ButtonStatus = false;
bool statusRedLed = LOW;


ESP8266WebServer server(80);

const char htmlTemplate[] PROGMEM = R"====(
  <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1 style="font-size:100px">Mengendalikan Led</h1>
    <p style="font-size:80px">status led : %%LED_STATUS%%</p>
    <a href="%%BUTTON_LINK%%">
    <button type="button" style="font-size:150px">%%BUTTON_TEXT%%</button>
    </a>
</body>
</html>
)====";


void tersambung();
void ledMenyala();
void ledMati();
void tidak_ditemukan();
String kirimHTML(uint8_t statusRedLed);

void setup() {
  pinMode(ledRed, OUTPUT);
  // pinMode(firstButton, INPUT);
  Serial.begin(115200);
  


  Serial.print("mengubungi...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("mencoba menghubungi ulang...");
    delay(1000);
  }

  Serial.println("tersambung");
  Serial.print("IP Number : "); Serial.println(WiFi.localIP());

  server.on("/", tersambung);
  server.on("/ledMenyala", ledMenyala);
  server.on("/ledMati", ledMati);
  server.onNotFound(tidak_ditemukan);
  server.begin();
  Serial.println("memulai HTTP server");
}

void tersambung() {
  statusRedLed = LOW;
  server.send(200, "text/html", kirimHTML(statusRedLed));
}

void ledMenyala() {
  statusRedLed = HIGH;
  server.send(200, "text/html", kirimHTML(statusRedLed));
}

void ledMati() {
  statusRedLed = LOW;
  server.send(200, "text/html", kirimHTML(statusRedLed));
}

void tidak_ditemukan() {
  server.send(404, "text/plain", "halaman tidak ditemukan");
}



String kirimHTML(uint8_t statusRedLed) {
  // char buffer[1024];
  // strcpy_P(buffer, htmlTemplate);

  // String konten = buffer;

  if(statusRedLed) {
    konten.replace("%%LED_STATUS%%", "ON");
    konten.replace("%%BUTTON_LINK%%", "OFF");
    konten.replace("%%BUTTON_TEXT%%", "OFF");
  } else {
    konten.replace("%%LED_STATUS%%", "OFF");
    konten.replace("%%BUTTON_LINK%%", "ON");
    konten.replace("%%BUTTON_TEXT%%", "ON");
  }
}


void loop() {
  server.handleClient();
                                    
  if(statusRedLed) {
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(ledRed, LOW);

  // digitalWrite(ledRed, HIGH);
  // delay(1000);
  // digitalWrite(ledRed, LOW);
  // delay(1000);

  }







}


