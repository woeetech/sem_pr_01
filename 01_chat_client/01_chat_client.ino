#include <SPI.h>
#include <Ethernet.h>

//made-up MAC address
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCD, 0xDE, 0x03
};

//if DHCP fails:
IPAddress ip(192, 168, 1, 101);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255,0);

IPAddress server(192,168,1,100);

EthernetClient client;

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
  

  Serial.print("Chat client adress: ");
  Serial.println(Ethernet.localIP());

  Serial.println("trying to connect to server...");
  if (client.connect(server, 23)) {
    Serial.println("connected");
  } 
  else {
    Serial.println("connection failed");
  }
  client.print("Hello server!");
}


void loop() {
  Ethernet.maintain();
}
