#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177);

int photocellPin = 0;  
int photocellReading;

char server[] = "www.iot.ajarin.id"; 
EthernetClient client;

void setup() {
 
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
    
}

void loop() {
  photocellReading = analogRead(photocellPin); 
  
  if (client.connect(server, 80)) {
    client.print("GET /index.php/datalogger/?");
    client.print("nilai=");
    client.print(photocellReading);
    client.println(" HTTP/1.1"); 
    client.println("Host: www.iot.ajarin.id");
    client.println("Connection: close");
    client.println();
    client.println();
    client.stop();
  }

  else {
    Serial.println("--> connection failed\n");
  }
  
  delay(10000);
}
