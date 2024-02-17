#define BLYNK_TEMPLATE_ID "TMPL3jdkUUmj8"
#define BLYNK_TEMPLATE_NAME "Posture Detector"
#define BLYNK_AUTH_TOKEN "35llFGkR7MyXIHYr0ZvcxOtjmTvIn5On"
//the details of channel created on the blynk IOT Website


#define BLYNK_PRINT Serial
#include<WiFi.h>
#include<WiFiClient.h>
#include<BlynkSimpleEsp32.h>

// #include<DHT.h>

#include "Wire.h"            
#include "MPU6050.h" 

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Mustafa Y36"; //wifi
char pass[] = "MUSTAFA IS THE KING"; //pass

// BlynkTimer timer;

MPU6050 mpu;
int buzz = 13 ; //ESP 32 (13 from 8)
int add=0,good=0,bad=0;



int16_t ax, ay, az;
int16_t gx, gy, gz;  
struct MyData {
  int X;
  int Y;
  int Z;
};
MyData data;
void setup()
{
  Serial.begin(115200); //ESP 32 (115200 to 9600)
  Wire.begin();
  mpu.initialize();
  pinMode(buzz,OUTPUT);

  Blynk.begin(auth,ssid,pass);
}
void loop()
{
  Blynk.run();
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  data.Z = map(az, -17000, 17000, 0, 255);  // Z axis data
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Blynk.virtualWrite(V0,data.X);

  Serial.print("  ");
  Serial.print("Axis Y = ");
  Blynk.virtualWrite(V1,data.Y);
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z = ");
  Serial.println(data.Z); 
  Blynk.virtualWrite(V2,data.Z);

  
//  if((data.X<120 || data.X>130) && (data.Y<5 || data.Y>8) && (data.Z<88 || data.Z>93))
//if((data.X<120 || data.X>135) && (data.Y<5 || data.Y>10) && (data.Z<88 || data.Z>100))
//if((data.X<115 || data.X>130) && (data.Z<88 || data.Z>93))
if((data.Y<5 || data.Y>8) && (data.Z<100 || data.Z>125))
  {
     Serial.println("Bad Posture");
     digitalWrite(buzz,HIGH);
     bad++;
     delay(100);
     digitalWrite(buzz,LOW);
     delay(100);        
    }
    else
    {
      good++;
    }
    add = good + bad;
    if(add >=20)
    {
      float ans = (good/(good+bad))*100;
      Serial.print("ANS : ");
      Serial.print(ans);
      Blynk.virtualWrite(V0,ans);
      good=0;
      bad=0;
      ans=0;
    }
  delay(500);
}
