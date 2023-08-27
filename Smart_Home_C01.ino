#include <ESP8266WiFi.h>

int port = 4200;  //Port number
WiFiServer server(port);

//Server connect to WiFi Network
//Enter your wifi SSID

const char *ssid = "Dialog 4G 406";
//Enter your wifi Password
const char *password = "53F900c5";

String string = "";
char tst;

//==============================
//                    Power on setup
//==============================
void setup()
{
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi


  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}
//===================================
//                    Loop
//===================================

void loop()
{

  WiFiClient client = server.available();

  if (client) {
    if (client.connected())
    {
    }

    while (client.connected()) {
      while (client.available() > 0) {
        // read data from the connected client
        char a = client.read();
        tst = a;
        String b = String(a);
        string = string + b;
        //Serial.write(a);
        delay(10); //wait to read data
      }
      //Send Data to connected client(No need this for now)
      while (Serial.available() > 0)
      {
        client.write(Serial.read());
      }

    }
    client.stop();
    controlDevice(tst);
    string = "";
  }

}

void controlDevice(char s) {

  // s = "acon";

  Serial.print("Respons --> ");
  Serial.println(s);

  switch (s)
  {
    case 'A':
      digitalWrite(16, HIGH);
      break;
    case 'B':
      digitalWrite(16, LOW);
      break;

    case 'C':
      digitalWrite(5, HIGH);
      break;
    case 'D':
      digitalWrite(5, LOW);
      break;

    case 'E':
      digitalWrite(4, HIGH);
      break;
    case 'F':
      digitalWrite(4, LOW);
      break;
      
    case 'G':
      digitalWrite(14, HIGH);
      //Serial.println("ONNN");
      break;
    case 'H':
      digitalWrite(14, LOW);
      //Serial.println("OFFF");
      break;

    case 'I':
      digitalWrite(2, HIGH);
      break;
    case 'J':
      digitalWrite(2, LOW);
      break;

   


    default:
      break;
  }

}
