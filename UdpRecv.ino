
#include <SPI.h>       
#include <Ethernet.h>
#include <EthernetUdp.h>         


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

IPAddress ip_a(192, 168, 1, 123);

unsigned int localPort = 8888;      // local port to listen on
unsigned int answPort = 6000; 
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
char  ReplyBuffer[] = "ok";       // a string to send back

char com[14] = "Fuck the World";

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;



bool isPermutation(char* str1, char* str2, int size)
{

    for (int i = 0; i < size; ++i)
    {
        if (str1[i] != str2[i])
            return false;
    }

    return true;
}


void debug(){
   Serial.print("Received packet of size ");
   Serial.println(packetSize);
   Serial.print("From ");
  
   IPAddress remote = Udp.remoteIP();
  
   for (int i = 0; i < 4; i++) {
     Serial.print(remote[i], DEC);
     if (i < 3) {
       Serial.print(".");
     }
   }
  
   Serial.print(", port ");
   Serial.println(Udp.remotePort());
}



void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  Serial.begin(9600);
  Serial.println("Ready to recv UDP ");
}





void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  
  if (packetSize) {

 String command = "";
 




    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    for(int i = 0 ; i < packetSize; i++){
      command+=packetBuffer[i];
    }

    Serial.print ("String - ");
    Serial.println(command);
    

  
    if (command == "Fuck the World")Serial.println("Bingo plus jackpot");

    // send a reply to the IP address and port that sent us the packet we received
    Udp.beginPacket(/*Udp.remoteIP()*/ip_a, /*Udp.remotePort()*/answPort);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);
}
 
