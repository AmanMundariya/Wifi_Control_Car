//Code By Smart Tech Tuition
//Wifi Control Car 

#include <ESP8266WiFi.h>

WiFiClient client;

WiFiServer server(80);
const char* ssid     = ""; // Your WiFi ssid
const char* password = ""; // Your WiFi Password

String  data =""; 
// Define all Pins Here//


int rightMotorForward = 16;   /* GPIO15(D0) -> IN1  */

int rightMotorBackward = 5;  /* GPIO13(D1) -> IN2  */

int leftMotorForward = 4;  /* GPIO2(D2) -> IN3   */

int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */

int Horn = 2;       /* GPIO2 (D4) -> Horn */

int Light = 14;     /* GPIO14 (D5) -> Light */

void setup(){
 // Code for Print IP Address OF Your board
  
  Serial.print("Attempting to connect to SSID");
  WiFi.begin(ssid, password);
  // Attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP  network:
    // Wait 1 seconds for connection:
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP

  pinMode(leftMotorForward, OUTPUT);

  pinMode(rightMotorForward, OUTPUT);

  pinMode(leftMotorBackward, OUTPUT);

  pinMode(rightMotorBackward, OUTPUT);

  pinMode(Horn, OUTPUT);

  pinMode(Light, OUTPUT);

  server.begin();

}


void loop()

{

  client = server.available();

  if (!client) return;

  data = checkClient ();

  if (data == "up") MotorForward();

  else if (data == "down") MotorBackward();

  else if (data == "left") TurnLeft();

  else if (data == "right") TurnRight();

  else if (data == "stop") MotorStop();

  else if (data == "horn") HornON();

  else if (data == "lighton") LightON();

  else if (data == "lightof") LightOFF();
  
  } 
void MotorForward(void)

{

digitalWrite(leftMotorForward,HIGH);

digitalWrite(rightMotorForward,HIGH); 

digitalWrite(leftMotorBackward,LOW);

digitalWrite(rightMotorBackward,LOW);

}
void MotorBackward(void) 

{

digitalWrite(leftMotorBackward,HIGH);

digitalWrite(rightMotorBackward,HIGH);

digitalWrite(leftMotorForward,LOW);

digitalWrite(rightMotorForward,LOW);

}
void TurnLeft(void)

{

digitalWrite(leftMotorForward,HIGH);

digitalWrite(rightMotorForward,LOW);

digitalWrite(rightMotorBackward,LOW);

digitalWrite(leftMotorBackward,LOW);

}
void TurnRight(void)

{

digitalWrite(leftMotorForward,LOW);

digitalWrite(rightMotorForward,HIGH);

digitalWrite(rightMotorBackward,LOW);

digitalWrite(leftMotorBackward,LOW);

}

void MotorStop(void) 

 {

digitalWrite(leftMotorForward,LOW);

digitalWrite(leftMotorBackward,LOW);

digitalWrite(rightMotorForward,LOW); 

digitalWrite(rightMotorBackward,LOW);

digitalWrite(Horn,LOW);


}

void HornON(void)
{
  digitalWrite(Horn,HIGH);
}

void LightON(void)
{
  digitalWrite(Light,HIGH);
}

void LightOFF(void)
{
  digitalWrite(Light,LOW);
}


/***RECEIVE DATA FROM the APP ***/

String checkClient (void)

{

while(!client.available()) delay(1); 

String request = client.readStringUntil('\r');

request.remove(0, 5);

request.remove(request.length()-9,9);

return request;

}
