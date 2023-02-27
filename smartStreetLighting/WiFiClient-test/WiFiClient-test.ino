/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <WiFi.h>

#ifndef STASSID
#define STASSID "Skiba"
#define STAPSK "1223334444"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.88.247";
const uint16_t port = 4242;

WiFiClient client;

WiFiMulti multi;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  multi.addAP(ssid, password);

  if (multi.run() != WL_CONNECTED) {
    Serial.println("Unable to connect to network, rebooting in 10 seconds...");
    delay(10000);
    rp2040.reboot();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  


}

void loop() {

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  
  if (client.connected()) {
    Serial.println("sending data to server");
    client.println("Klient skickar skit");
  }

/*
  Serial.println("Trying to read data");
  //if (client.available() != 0) {
    //Serial.println("Data found");
    while (client.available()) {
      char ch = static_cast<char>(client.read());
      Serial.print(ch);
    }
  //}
*/
Serial.println("Läs data fan");
  String req = client.readStringUntil('\n');
  Serial.println(req + " test");
  delay(3000);

    /*
    // wait for data to be available
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        delay(60000);
        return;
      }
    }

    // Read all the lines of the reply from server and print them to Serial
    Serial.println(" --- receiving from remote server");
    // not testing 'client.connected()' since we do not need to send data here
    while (client.available()) {
      char ch = static_cast<char>(client.read());
      Serial.print(ch);
    }
    */

  }
  /*
  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  if (wait) {
    delay(10000);  // execute once every 5 minutes, don't flood remote service
  }
  wait = true;
}*/
