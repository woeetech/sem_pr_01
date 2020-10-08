#include <SPI.h>
#include <Ethernet.h>

//made-up MAC address
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCD, 0xDE, 0x02
};

//if DHCP fails:
IPAddress ip(192, 168, 1, 100);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255,0);


EthernetServer server(23);

bool alreadyConnected = false;

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  //SETUP
  Serial.println("Trying to obtain IP from DHCP...");
  if (Ethernet.begin(mac) == 0) {
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield not found!");
      while(true) {
        delay(1); //basically do nothing, we're done, end of story...
      }  
    }  
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable not connected!"); //never got this message, even with cable unplugged
    }
    Serial.println("Failed to obtain IP from DHCP, setting default values.");
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
  }
  

  Serial.print("Chat server adress: ");
  Serial.println(Ethernet.localIP());
  server.begin();
}

void loop() {
 
 /*EthernetClient client = server.available();
 if (client) {
  if (!alreadyConnected) {
    client.flush();
    Serial.println("New client connected!");
    client.println("Hello World, I am Arduino.!");
    alreadyConnected = true;
  }
  
  if (client.available() > 0) {
    char incoChar = client.read();
    Serial.write(incoChar);
  }
 }

 char serialInput = Serial.read();
 if (serialInput == '/') client.flush();            //attempt to disconnect the client, but no luck here.
 serialInput == -1 ? : server.print(serialInput);   //arduino can respond back now.
*/

EthernetClient client = server.available();
if (client) {
    Serial.print("Remote client IP adress: ");
    Serial.println(client.remoteIP());
    client.stop();
  }
  Ethernet.maintain();
}
