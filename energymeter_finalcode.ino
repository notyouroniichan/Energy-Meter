#include <SoftwareSerial.h>             //library for using software serial 
#include <ESP8266WiFi.h>
//const char* ssid ;
//const char* pass ;
const char* ssid = "TGS";
const char* pass = "tgs@12345";

char server[] = "console.thingsgosocial.com";


 WiFiClient client ;

#define SSerialRX        D3            //Serial Receive pin
#define SSerialTX        D2             //Serial Transmit pin
#define SSerialTxControl D5           //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
// #define unlatched1        D0            //Serial Receive pin
#define unlatched2        D4          //Serial Receive pin
//#define unlatched3        D7            //Serial Receive pin
//      #define latched1        D1             //Serial Receive pin
//      #define latched2        D6             //Serial Receive pin
//      #define latched3        D8             //Serial Receive pin
#define BUFF_MAX 20
int i;
SoftwareSerial RS485Serial( SSerialRX , SSerialTX) ; // RX TX


 //char did[] = "qyuqynjul9e14s";         //la
//  char did[] = "d1evh78u8jub4d74v";         //Green Park
// char did[] = "5c055injul1awix";         //test hid
// char did[] = "25f1todnjvqef68h";         //Z rehman
// char did[] = "d1evh78u8jub4dwqa";         // pankaj sir demo
//  char did[] = "25f1todnjvqefygk";         //chandigarh updated 25f1todnjvqedk4i
char did[] = "702ff36c6c16daad5cbb65f457644f56ca9b844f";

int reading;
uint8_t buff[12];
uint8_t whbuff[12];
uint8_t vrybuff[4];
uint8_t vybbuff[4];
uint8_t vbrbuff[4];
uint8_t vrnbuff[4];
uint8_t vynbuff[4];
uint8_t vbnbuff[4];
uint8_t irbuff[4];
uint8_t iybuff[4];
uint8_t ibbuff[4];
/*
      uint8_t kvabuff[4];
      uint8_t pfrbuff[4];
      uint8_t pfybuff[4];
      uint8_t pfbbuff[4];
      uint8_t varbuff[4];
*/


//commented sending bytes were according to veritek documentation
byte Sendwh[] = { 0x01, 0x04, 0x00, 0x09, 0x00, 0x04, 0x21, 0xCB}; //works fine for wh, check register and documentation for know how

//byte Sendvry[] = { 0x01, 0x04, 0x00, 0x35, 0x00, 0x02, 0x61, 0xC5 }; //for RY - need change in CRC checksum Bytes
byte Sendvry[] = { 0x01, 0x04, 0x00, 0x65, 0x00, 0x02, 0x61, 0xd4 };
byte Sendvyb[] = { 0x01, 0x04, 0x00, 0x4F, 0x00, 0x02, 0x40, 0x1C }; //seems for Phr_Y and works fine for yb
//byte Sendvyb[] = { 0x01, 0x04, 0x00, 0x4B, 0x00, 0x02, 0x01, 0xDD }; //for YB - need change in CRC checksum Bytes

byte Sendvbr[] = { 0x01, 0x04, 0x00, 0x65, 0x00, 0x02, 0x61, 0xd4 }; //seems for Phr_B and works fine for br
//byte Sendvbr[] = { 0x01, 0x04, 0x00, 0x61, 0x00, 0x02, 0x20, 0x15 }; //for BR - need change in CRC checksum Bytes

byte Sendvrn[] = { 0x01, 0x04, 0x00, 0x3B, 0x00, 0x02, 0x00, 0x06 }; //seems it is for I_r and works fine for rn
//byte Sendvrn[] = { 0x01, 0x04, 0x00, 0x37, 0x00, 0x02, 0xC0, 0x05 }; //for RN - need change in CRC checksum Bytes

byte Sendvyn[] = { 0x01, 0x04, 0x00, 0x51, 0x00, 0x02, 0x20, 0x1a }; //seems it is for I_y and works fine for yn
//byte Sendvyn[] = { 0x01, 0x04, 0x00, 0x4D, 0x00, 0x02, 0xE1, 0xDC }; //for YN - need change in CRC checksum Bytes

byte Sendvbn[] = { 0x01, 0x04, 0x00, 0x67, 0x00, 0x02, 0xC0, 0x14 }; //seems it is for I_b and works fine for bn
//byte Sendvbn[] = { 0x01, 0x04, 0x00, 0x63, 0x00, 0x02, 0x81, 0xD5 }; //for BN - need change in CRC checksum Bytes

//byte Sendir[] = { 0x01, 0x04, 0x00, 0x3F, 0x00, 0x02, 0x41, 0xC7 }; //seems it is for active power R and works fine for Ir
byte Sendir[] = { 0x01, 0x04, 0x00, 0x3B, 0x00, 0x02, 0x00, 0x06 }; //for IR - need change in CRC checksum Bytes

byte Sendiy[] = { 0x01, 0x04, 0x00, 0x55, 0x00, 0x02, 0x61, 0xDB }; //seems it is for active power Y and works fine for iy
//byte Sendiy[] = { 0x01, 0x04, 0x00, 0x51, 0x00, 0x02, 0x20, 0x1A }; //for IY - need change in CRC checksum Bytes

byte Sendib[] = { 0x01, 0x04, 0x00, 0x6B, 0x00, 0x02, 0x00, 0x17 }; //seems it is for active power B and works fine for ib
//byte Sendib[] = { 0x01, 0x04, 0x00, 0x67, 0x00, 0x02, 0xC0, 0x14 }; //for IB - need change in CRC checksum Bytes

/*
   byte Sendkva[] =  { 0x01, 0x04, 0x00, 0x47, 0x00, 0x02, 0xC1, 0xDE };
   byte Sendpfr[] =  { 0x01, 0x04, 0x00, 0x41, 0x00, 0x02, 0x21, 0xDF };
   byte Sendpfy[] =  { 0x01, 0x04, 0x00, 0x57, 0x00, 0x02, 0xC0, 0x1B };
   byte Sendpfb[] =  { 0x01, 0x04, 0x00, 0x6D, 0x00, 0x02, 0x16, 0xE0 };
  // byte Sendvar[] = { 0x01, 0x04, 0x00, 0x21, 0x00, 0x04, 0xA1, 0xC3};
   byte Sendvar[] = { 0x01, 0x04, 0x00, 0x45, 0x00, 0x02, 0x60, 0x1E};
   //More data packets can be added as per user's input on the application
*/
void setup()   
{
  //pinMode(latched1, OUTPUT);
  //pinMode(latched2, OUTPUT);
  //pinMode(latched3, OUTPUT);
  //pinMode(unlatched1, OUTPUT);
  //pinMode(unlatched2, OUTPUT);
  //pinMode(unlatched3, OUTPUT);

  Serial.begin(115200);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  delay(100);
  WiFi.mode(WIFI_AP_STA); 
   WiFi.begin(ssid,pass);
  Serial.print("Connecting");
  int i = 0;
  int cnt = 0;
  delay(10);
  WiFi.mode(WIFI_STA);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (cnt++ >= 45) {
      WiFi.beginSmartConfig();
      while (1) {

        delay(500);
        Serial.println("configuration Mode");
        digitalWrite(unlatched2, HIGH);
        delay(100);
        digitalWrite(unlatched2, LOW);
        delay(100);
        if (WiFi.smartConfigDone()) {
          Serial.println("SmartConfig Success");
          break;
        }
      }
    }
  }
  delay(300);

  pinMode(SSerialTxControl, OUTPUT);
  RS485Serial.begin(9600);   // set the data rate
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());


  //WiFi.mode(WIFI_AP);
  WiFi.softAP("TGS", "tgs@12345", 7);  // network name, network password, wifi channel
}//--(end setup )---


void loop()
{

  for (int i = 0; i < 11; i++) // 12 changed to 11
  {
    send485(i);
    delay(1000);
    Serial.read();
    ReadRx(i);
    memset(buff, '\0', sizeof(BUFF_MAX));
    delay(1000);

  }

  String values = "";

  values += "&tid=";
  values += did;
  values += "&wh=";
  values += String(whbuff[0]) + String(':') + String(whbuff[1]) + String(':') + String(whbuff[2]) + String(':') + String(whbuff[3]) + String(':') + String(whbuff[4]) + String(':') + String(whbuff[5]) + String(':') + String(whbuff[6]) + String(':') + String(whbuff[7]);
  values += "&vry=";
  values += String(vrybuff[0]) + String(':') + String(vrybuff[1]) + String(':') + String(vrybuff[2]) + String(':') + String(vrybuff[3]);
  values += "&vyb=";
  values += String(vybbuff[0]) + String(':') + String(vybbuff[1]) + String(':') + String(vybbuff[2]) + String(':') + String(vybbuff[3]);
  values += "&vbr=";
  values += String(vbrbuff[0]) + String(':') + String(vbrbuff[1]) + String(':') + String(vbrbuff[2]) + String(':') + String(vbrbuff[3]);
  values += "&vrn=";
  values += String(vrnbuff[0]) + String(':') + String(vrnbuff[1]) + String(':') + String(vrnbuff[2]) + String(':') + String(vrnbuff[3]);
  values += "&vyn=";
  values += String(vynbuff[0]) + String(':') + String(vynbuff[1]) + String(':') + String(vynbuff[2]) + String(':') + String(vynbuff[3]);
  values += "&vbn=";
  values += String(vbnbuff[0]) + String(':') + String(vbnbuff[1]) + String(':') + String(vbnbuff[2]) + String(':') + String(vbnbuff[3]);
  values += "&ir=";
  values += String(irbuff[0]) + String(':') + String(irbuff[1]) + String(':') + String(irbuff[2]) + String(':') + String(irbuff[3]);
  values += "&iy=";
  values += String(iybuff[0]) + String(':') + String(iybuff[1]) + String(':') + String(iybuff[2]) + String(':') + String(iybuff[3]);
  values += "&ib=";
  values += String(ibbuff[0]) + String(':') + String(ibbuff[1]) + String(':') + String(ibbuff[2]) + String(':') + String(ibbuff[3]);

  /*        values += "&kva=";
          values += String(kvabuff[0]) + String(':') + String(kvabuff[1]) + String(':') + String(kvabuff[2]) + String(':') + String(kvabuff[3]);

          values += "&pfr=";
          values += String(pfrbuff[0]) + String(':') + String(pfrbuff[1]) + String(':') + String(pfrbuff[2]) + String(':') + String(pfrbuff[3]);

          values += "&pfy=";
          values += String(pfybuff[0]) + String(':') + String(pfybuff[1]) + String(':') + String(pfybuff[2]) + String(':') + String(pfybuff[3]);

          values += "&pfb=";
          values += String(pfbbuff[0]) + String(':') + String(pfbbuff[1]) + String(':') + String(pfbbuff[2]) + String(':') + String(pfbbuff[3]);

          values += "&var=";
          values += String(varbuff[0]) + String(':') + String(varbuff[1]) + String(':') + String(varbuff[2]) + String(':') + String(varbuff[3]);
  */
  values += "&me=";
  values += "vk";

  if (!client.connect(server , 80)) { //Check WiFi connection status

    Serial.println("Error in WiFi connection");
    return;

  } else {

    Serial.println("Sending Started");

  }

  delay(1000);


  Serial.println(F("the final data to be sent is"));
  //Serial.println(values);
  delay(500);
  Serial.println(values);
  delay(1000);
  // SmartMeterpost.HttpPost(values);
  // delay(500);
  // SmartMeterpost.HttpPost(values);
  delay(5000) ;
  //Serial.flush();
  //**************************************************************************
  if (client.connect(server, 80)) {
    //  String PostData="tid=5c055injul1awix";
    client.println("POST /api/databanks/meter HTTP/1.1");
    client.println("Host: d6.thingsgosocial.com");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(values.length());
    client.println();
    client.println(values);

    long interval = 2000;
    unsigned long currentMillis = millis(), previousMillis = millis();

    while (!client.available()) {

      if ( (currentMillis - previousMillis) > interval ) {

        Serial.println("Timeout");
        // blinkLed.detach();
        // digitalWrite(2, LOW);
        client.stop();
        return;
      }
      currentMillis = millis();
    }

    while (client.connected())
    {
      if ( client.available() )
      {
        String   str = client.readString();
        Serial.print(str);
        //Serial.println("swati");
        if (str.indexOf("PC=1") >= 0)
        {
          //  delay(100);
          // digitalWrite(UnLatched , HIGH);
          // delay(200);
          //  digitalWrite(UnLatched,LOW);
          //  delay(2000);
          // digitalWrite(unlatched2, HIGH);
          // delay(200);
          // digitalWrite(unlatched2, LOW);
          //  delay(2000);
          // digitalWrite(unlatched3, HIGH);
          //  delay(200);
          //  digitalWrite(unlatched3, LOW);
          //  delay(2000);
          //digitalWrite(unlatched1 , HIGH);
          //digitalWrite(unlatched2 , HIGH);
          //digitalWrite(unlatched3 , HIGH);
          //delay(200);
          //digitalWrite(unlatched1 , LOW);
          //digitalWrite(unlatched2 , LOW);
          //digitalWrite(unlatched3 , LOW);
          //Serial.println("unlacthing relay");

        }
        else if (str.indexOf("PC=0") >= 0)
        {
          //   delay(100);
          // digitalWrite(Latched , HIGH);
          // delay(200);
          //  digitalWrite(Latched,LOW);
          //  delay(2000);
          // digitalWrite(latched2, HIGH);
          // delay(200);
          // digitalWrite(latched2, LOW);
          //  delay(2000);
          // digitalWrite(latched3, HIGH);
          //  delay(200);
          //  digitalWrite(latched3, LOW);
          //  delay(2000);
          //digitalWrite(latched1 , HIGH);
          //digitalWrite(latched2 , HIGH);
          //digitalWrite(latched3 , HIGH);
          //delay(200);
          //digitalWrite(latched1 , LOW);
          //digitalWrite(latched1 , LOW);
          //digitalWrite(latched1 , LOW);
          // Serial.println("lacthing relay low");
        }
        str = "";
      }
    }
  }
}



void send485(int s) //to send command to slave
{
  Serial.println(F("calling modbus packets"));
  digitalWrite(SSerialTxControl, RS485Transmit);


  if (s == 1)
  {
    RS485Serial.write(Sendwh, sizeof(Sendwh));
    for (int i = 0; i < 8; i++)
    {
      Serial.println(Sendwh[i]);
    }
  }

  //delay(500);
  if (s == 2)
  {
    RS485Serial.write(Sendvry, sizeof(Sendvry));

  }

  if (s == 3)
  {
    RS485Serial.write(Sendvyb, sizeof(Sendvyb));

  }
  if (s == 4)
  {
    RS485Serial.write(Sendvbr, sizeof(Sendvbr));

  }

  if (s == 5)
  {
    RS485Serial.write(Sendvrn, sizeof(Sendvrn));

  }

  if (s == 6)
  {
    RS485Serial.write(Sendvyn, sizeof(Sendvyn));

  }

  if (s == 7)
  {
    RS485Serial.write(Sendvbn, sizeof(Sendvbn));

  }

  if (s == 8)
  {
    RS485Serial.write(Sendir, sizeof(Sendir));

  }

  if (s == 9)
  {
    RS485Serial.write(Sendiy, sizeof(Sendiy));

  }

  if (s == 10)
  {
    RS485Serial.write(Sendib, sizeof(Sendib));

  }

  /*       if (s == 11)
        {
          RS485Serial.write(Sendkva, sizeof(Sendkva));

        }

         if (s == 12)
        {
          RS485Serial.write(Sendpfr, sizeof(Sendpfr));

         }
          if (s == 13)
         {
            RS485Serial.write(Sendpfy, sizeof(Sendpfy));

          }

          if (s == 14)
          {
           RS485Serial.write(Sendpfb, sizeof(Sendpfb));

           }


          if (s == 15)
           {
           RS485Serial.write(Sendvar, sizeof(Sendvar));

           }   */

  digitalWrite(SSerialTxControl, RS485Receive);

}

void ReadRx(int cp) //to receive data from slave
{
  uint8_t  buff[12] = " ";
  digitalWrite(SSerialTxControl, RS485Receive);   //not necessary as it is already converted to receive mode
  delay(1000);

  if (RS485Serial.available() > 0) // do something if data available at RS485
  {

    int cmdlength = RS485Serial.readBytes(buff, BUFF_MAX);    //reading bytes fromm serial and put it in a buffer of length BUFF_MAX    (Buff_max is changed to 12)
    delay(200);
    Serial.println(F("read begin"));
    //Serial.println(cmdlength);

  }

  if ((buff[0] == 1) && (buff[1] == 4))
  {
    Serial.println(F("valid data"));
    //Serial.flush();
  }
  else
  {
    Serial.println(F("no data"));
  }

  if (cp == 1)
  {
    delay(500);
    Serial.println("reading cp value");
    Serial.println(cp);
    //changed from buff[0] to buff[3] from starting below
    //wh buffer is 64 bit data coming from energy meter
    Serial.println("buff begin");
    Serial.println(buff[3]);
    Serial.println(buff[4]);
    Serial.println(buff[5]);
    Serial.println(buff[6]);
    Serial.println(buff[7]);
    Serial.println(buff[8]);
    Serial.println(buff[9]);
    Serial.println(buff[10]);
    Serial.println("buff ends");

    whbuff[0] = buff[3];         //save wh reading
    whbuff[1] = buff[4];
    whbuff[2] = buff[5];
    whbuff[3] = buff[6];
    whbuff[4] = buff[7];
    whbuff[5] = buff[8];
    whbuff[6] = buff[9];
    whbuff[7] = buff[10];

    for (int i = 0; i < 8; i++ )
    {
      Serial.println(whbuff[i]);
    }
    //delay(2000);
  }

  else if (cp == 2)
  {
    Serial.println(cp);
    Serial.println("buf begin");
    Serial.println(buff[3]);
    Serial.println(buff[4]);
    Serial.println(buff[5]);
    Serial.println(buff[6]);

    Serial.println("buf ends");
    vrybuff[0] = buff[3];
    vrybuff[1] = buff[4];
    vrybuff[2] = buff[5];
    vrybuff[3] = buff[6];

    // print for debugging process
    Serial.println(F("reading vry"));

    delay(200);

  }

  else if (cp == 3)
  {
    Serial.println(cp);
    vybbuff[0] = buff[3];
    vybbuff[1] = buff[4];
    vybbuff[2] = buff[5];
    vybbuff[3] = buff[6];

    Serial.println(F("reading vyb"));

    delay(200);


  }

  else if (cp == 4)
  {

    Serial.println(cp);
    vbrbuff[0] = buff[3];
    vbrbuff[1] = buff[4];
    vbrbuff[2] = buff[5];
    vbrbuff[3] = buff[6];

    Serial.println(F("reading vbr"));

    delay(200);

  }


  else if (cp == 5)
  {
    Serial.println(cp);
    vrnbuff[0] = buff[3];
    vrnbuff[1] = buff[4];
    vrnbuff[2] = buff[5];
    vrnbuff[3] = buff[6];

    // only printing for debugging
    Serial.println(F("reading vrn"));

    delay(200);

  }

  else if (cp == 6)
  {
    Serial.println(cp);
    vynbuff[0] = buff[3];
    vynbuff[1] = buff[4];
    vynbuff[2] = buff[5];
    vynbuff[3] = buff[6];

    Serial.println(F("reading vyn"));

    delay(200);


  }

  else if (cp == 7)
  {
    Serial.println(cp);
    vbnbuff[0] = buff[3];
    vbnbuff[1] = buff[4];
    vbnbuff[2] = buff[5];
    vbnbuff[3] = buff[6];

    Serial.println(F("reading vbn"));

    delay(200);

  }

  else if (cp == 8)
  {
    Serial.println(cp);
    irbuff[0] = buff[3];
    irbuff[1] = buff[4];
    irbuff[2] = buff[5];
    irbuff[3] = buff[6];

    Serial.println(F("reading ir"));

    delay(200);


  }

  else if (cp == 9)
  {
    Serial.println(cp);
    iybuff[0] = buff[3];
    iybuff[1] = buff[4];
    iybuff[2] = buff[5];
    iybuff[3] = buff[6];

    Serial.println(F("reading iy"));

    delay(200);


  }

  else if (cp == 10)
  {
    Serial.println(cp);
    ibbuff[0] = buff[3];         //save power factor reading
    ibbuff[1] = buff[4];
    ibbuff[2] = buff[5];
    ibbuff[3] = buff[6];

    Serial.println(F("reading ib"));

    delay(200);
  }
  /*        else if (cp == 11)
         {
           Serial.println(cp);
           kvabuff[0] = buff[3];
           kvabuff[1] = buff[4];
           kvabuff[2] = buff[5];
           kvabuff[3] = buff[6];

           Serial.println(F("kva stored in registers"));

           delay(200);
         }


         else if (cp == 12)
         {
           Serial.println(cp);
           pfrbuff[0] = buff[3];
           pfrbuff[1] = buff[4];
           pfrbuff[2] = buff[5];
           pfrbuff[3] = buff[6];

           Serial.println(F("pfr stored in registers"));

           delay(200);
         }

         else if (cp == 13)
         {
           Serial.println(cp);
           pfybuff[0] = buff[3];
           pfybuff[1] = buff[4];
           pfybuff[2] = buff[5];
           pfybuff[3] = buff[6];

           Serial.println(F("pfy stored in registers"));

           delay(200);
         }

         else if (cp == 14)
         {
           Serial.println(cp);
           pfbbuff[0] = buff[3];
           pfbbuff[1] = buff[4];
           pfbbuff[2] = buff[5];
           pfbbuff[3] = buff[6];

           Serial.println(F("pfb stored in registers"));
           delay(200);
         }


          else if (cp == 15)
         {
           Serial.println(cp);
           varbuff[0] = buff[3];
           varbuff[1] = buff[4];
           varbuff[2] = buff[5];
           varbuff[3] = buff[6];

           Serial.println(F("var stored in registers"));
           delay(200);
         }
  */

}
