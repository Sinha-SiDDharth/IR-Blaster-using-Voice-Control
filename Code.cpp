#include <WiFi.h>
#include <WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char* ssid = "okay then have a great time";
const char* password = "siddharthSinhaheheok";

const uint16_t irSendPin = 2;
IRsend irsend(irSendPin);

uint16_t powerToggleSignal[36] = {
  417, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 278,
  167, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 778,
  167, 278, 167, 65535
};

uint16_t channelUpSignal[36] = {
  417, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 278,
  167, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 611, 167, 278,
  167, 278, 167, 65535
};

uint16_t channelDownSignal[36] = {
  417, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 278,
  167, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 611, 167, 278,
  167, 444, 167, 65535
};

uint16_t volumeUpSignal[36] = {
  417, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 278,
  167, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 444, 167, 278,
  167, 278, 167, 65535
};


uint16_t volumeDownSignal[36] = {
  417, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 278, 167, 278,
  167, 278, 167, 278, 167, 611, 167, 444,
  167, 611, 167, 278, 167, 444, 167, 278,
  167, 444, 167, 65535
};

WebServer server(80);

void sendIR(uint16_t* signal, size_t length) {
  Serial.println("Sending IR signal...");
  irsend.sendRaw(signal, length, 38); //38KHz
  Serial.println("Signal sent");
  server.send(200, "text/plain", "Signal sent");
}

// This is for connecting to WiFi
void setup() {
  Serial.begin(115200);
  irsend.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

// These will be activated when I run the HTTP Shortcut
  server.on("/power", []() { sendIR(powerToggleSignal, 36); });
  server.on("/chup", []() { sendIR(channelUpSignal, 36); });
  server.on("/chdown", []() { sendIR(channelDownSignal, 36); });
  server.on("/volup", []() { sendIR(volumeUpSignal, 36); });
  server.on("/voldown", []() { sendIR(volumeDownSignal, 36); });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
