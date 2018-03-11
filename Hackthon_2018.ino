

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include "DHT.h"
#define DHTTYPE DHT11 
const int DHTPin = 12;
DHT dht(DHTPin, DHTTYPE);

int count = 0;


int x,y,z;
int a;

SimpleTimer timer;
char auth[] = " cea5df0c389a424bb3f57028953c4636";               // Token for Blynk Server

#define BLYNK_PRINT Serial


float t;
float h;



 
void setup() {
  
 pinMode(D2,INPUT);
  pinMode(D3,INPUT);
   pinMode(D4,INPUT);
  Serial.begin(9600);
dht.begin();

  
  timer.setInterval(2000, sendUptime);//Serial connection
  WiFi.begin("B'HUB", "bL@@m0123");   //WiFi connection
  Blynk.begin(auth, "B'HUB", "bL@@m0123");
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}



void sendUptime()
{
  float h = dht.readHumidity();
 float t = dht.readTemperature();

  
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2,a);
  if(x==0 && y==1 && z==1)
    Blynk.notify("Its raining at (5,5)!");

  if(x==1 && y==0 && z==0)
    Blynk.notify("Garbage out at(5,5)");
  
  
}





 
void loop() {
  Blynk.run();
  timer.run();
  x = digitalRead(D2);
  y = digitalRead(D3);
  z = digitalRead(D4);
  
  
 //Serial.println(x);
 
 //Serial.println(y);
 
 //Serial.println(z);
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 

    
 if(x==0 && y==0 && z==0 && count==0)
 {
    JSONencoder["Ping"] = "F";
    a = 100;
    count = count+1;}
  if(x==0 && y==0 && z==1)
  {
  JSONencoder["Ping"] = "H";
  a = 50;}
   if(x==0 && y==1 && z==0)
   {
  JSONencoder["Ping"] = "L";
  a = 0;
  count = 0;}

   if(x==0 && y==1 && z==1)
  JSONencoder["Ping"] = "M";

   if(x==1 && y==0 && z==0)
  JSONencoder["Ping"] = "T";

 // if(x==0 && y==0 && z==0 && count==1)
  //JSONencoder["Ping"] = "V";

  //else
  //JSONencoder["Ping"] = "C";
  
 
 
    
    
    
 
    
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://10.15.1.4:8090/postjson");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(3000);  //Send a request every 30 seconds
 
}
