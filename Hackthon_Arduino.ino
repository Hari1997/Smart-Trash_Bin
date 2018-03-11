#include <dht.h>

#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                                    //Initiliazing

dht DHT;
#define DHT11_PIN 9

//long gyrox,gyroy,gyroz;
//float rotx,roty,rotz;
long ax,ay,az;
float fx,fy,fz;

const int trigPin = 7;
const int echoPin = 6;
// defines variables
long duration;
int distance;
int k;

int output_value ;
//int a0,a1,a2;
String data;


void setupMPU()
{
Wire.beginTransmission(0b1101000); 
Wire.write(0x6B);
Wire.write(0b00000000);
Wire.endTransmission();



Wire.beginTransmission(0b1101000);                                 //MPU-6050 setup
Wire.write(0x1B);
Wire.write(0b00000000);
Wire.endTransmission();


Wire.beginTransmission(0b1101000); 
Wire.write(0x1C);
Wire.write(0b00000000);
Wire.endTransmission();

}

void processdata()
{
fx = ax/16384.0;
fy = ay/16384.0;
fz = az/16384.0;
}

void accel()
{

Wire.beginTransmission(0b1101000); 
Wire.write(0x3B);

Wire.endTransmission();
Wire.requestFrom(0b1101000,6);
while(Wire.available() < 6);
ax = Wire.read()<<8|Wire.read();
ay = Wire.read()<<8|Wire.read();
az = Wire.read()<<8|Wire.read();
processdata();
}





int ping()
{
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

delay(1000);
return distance;
}

void setup() {

  lcd.begin(16, 2);
  //lcd.setCursor(0, 1); 
  //lcd.print("hello, world!");
  //delay(3000);
  //lcd.clear();


 Wire.begin();
setupMPU(); 

pinMode(A0,OUTPUT);  
pinMode(A1,OUTPUT);  
pinMode(A2,OUTPUT);  
pinMode(A3,INPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
  k = ping();
 accel();
  output_value= analogRead(A3);

  
int chk = DHT.read11(DHT11_PIN);
//Serial.println(" Humidity " );

//Serial.println(DHT.humidity, 1);

//Serial.println(" Temparature ");

//Serial.println(DHT.temperature, 1);

//delay(2000);



/*  Serial.println(rotx);
  Serial.println(roty);
  Serial.println(rotz);
  Serial.println();
  delay(4000);*/

  output_value = map(output_value,550,0,0,100);
  //Serial.println(k);


 //Serial.print(output_value);

  // Serial.println("%");

  if(k<10)
  {
  analogWrite(A0,0);
  analogWrite(A1,0);
  analogWrite(A2,0);
  data = "100% Full";
  }
   if(k>10 && k<20)
  {analogWrite(A0,0);
  analogWrite(A1,0);
  analogWrite(A2,255);
  data = "50% Full";
  }                      //Ping Sensor
   if(k>20)
 { analogWrite(A0,0);
  analogWrite(A1,255);
  analogWrite(A2,0);
  data = "0% Full";
  }

  if(output_value>20)
  { analogWrite(A0,0);
  analogWrite(A1,255);                    //Moisture Sensor
  analogWrite(A2,255);
  data = "Alert! Raining";
  }

  if(fy>0)
  { analogWrite(A0,255);
  analogWrite(A1,0);                    //Gyro
  analogWrite(A2,0);
  data = "Place me Straight";
  }
  else{
    data= ("Swatch Bharath!");
  }

  //a0 = analogRead(A0);
  //a1 = analogRead(A1);
  //a2 = analogRead(A2);
  //Serial.print("fz=");
//Serial.println(fz);
//Serial.print("fx=");
//Serial.println(fx);
//Serial.print("fy=");
//Serial.println(fy);

  //Serial.println(a0);
  //Serial.println(a1);
  //Serial.println(a2);


  lcd.setCursor(0, 0); 
  lcd.print(data);
  delay(2000);
  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Humidity ->");
  lcd.setCursor(0, 1); 
  lcd.print(DHT.humidity);
  delay(2000);                                          //LCD display
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temp in oC ->");
  lcd.setCursor(0, 1); 
  lcd.print(DHT.temperature);
  delay(2000);
  lcd.clear();
  
  

}
