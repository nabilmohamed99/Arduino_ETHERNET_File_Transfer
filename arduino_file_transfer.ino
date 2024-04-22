
#include <SdFat.h>
SdFat sd;

#include <SPI.h>
#include <Ethernet.h>

// SD chip select pin
const uint8_t chipSelect = 12; //Connect SD Card to pins 50, 51, 52 and 53 

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10,0xCA,0x90 };

IPAddress server(192,168,1,140); //SERVER IP ADDRESS

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,251); //ARDUINO IP ADDRESS

// Initialize the Ethernet client library
// with the IP address and port of the server
EthernetClient client;
int localport =19126;
// print stream

//------------------------------------------------------------------------------
// store error strings in flash memory
//------------------------------------------------------------------------------
void ftransfer() {

  char rbuffer[2048]; //Chunk can be increased to bigger sizes, be careful about memory!!
  char c;
  int n;
  // open test file
  SdFile rdfile("DATA.CSV", O_READ); // <--- Name of file to be transfered

  //Obtain file size
  uint32_t fsize;
  // Serial.println("On va commencer");
  fsize = rdfile.fileSize() - rdfile.curPosition();
  Ethernet.init(53);
  Serial.println(fsize);
  if (!rdfile.isOpen()) Serial.println("File could not be opened, check configuration...");
  // Serial.println("connexion avec le serveur");
  // if (Ethernet.begin(mac, ip) == 0) {
    // Serial.println("Failed to configure Ethernet using DHCP");

    Ethernet.begin(mac, ip);
  // }
  delay(1000);
  // Serial.println("Connecting to server for transfer...");
//  Serial.println(Ethernet.localIP());
  if (client.connect(server, localport)) {
    Serial.println("Connected");

  while ((n = rdfile.fgets(rbuffer, sizeof(rbuffer))) > 0) {
      client.write(reinterpret_cast<uint8_t*>(rbuffer), n); // Send raw bytes without decoding
  }
    
    client.stop();
  }
  else {
    // No response from server reply
    Serial.println("No server available");
  }

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void setup(void) {

  //Allow communications for SD Card ant Ethernet Shield
 pinMode(48, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(42, OUTPUT);


  digitalWrite(48, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(42, HIGH);



                    
  
  Serial.begin(9600);
  while (!Serial) {}  


  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(chipSelect, SPI_FULL_SPEED)){

   sd.initErrorHalt();
   Serial.println("Erreur dans l'initialisation du sd");

  }else{
       Serial.println("bon");

  }
  
  ftransfer();
  // Serial.println("finit");
  
}

void loop(void) {}
