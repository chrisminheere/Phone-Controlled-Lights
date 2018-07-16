//Made By: Chris Minheere 
//16-07-2018
//Phone Controlled Lights


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "***********************";
char ssid[] = "*********";
char pass[] = "*********";

void setup()
{
  pinMode(D2, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V1)
{
WidgetLED led1(V3);
Blynk.setProperty(V3, "color","#ff9933");
  
digitalWrite(D2, LOW);
led1.on();
delay(500);   
digitalWrite(D2, HIGH);
led1.off();
delay(500);

digitalWrite(D2, LOW);
led1.on();
delay(500);   
digitalWrite(D2, HIGH);
led1.off();
delay(500);

digitalWrite(D2, LOW);
led1.on();
delay(500);   
digitalWrite(D2, HIGH);
led1.off();
delay(500);

digitalWrite(D2, LOW);
led1.on();
delay(500);   
digitalWrite(D2, HIGH);
led1.off();
delay(500);

}

BLYNK_WRITE(V2)
{
WidgetLED led2(V4);
Blynk.setProperty(V4, "color","#ff9933");
  
digitalWrite(D7, LOW);
led2.on();
delay(500);   
digitalWrite(D7, HIGH);
led2.off();
delay(500);

digitalWrite(D7, LOW);
led2.on();
delay(500);   
digitalWrite(D7, HIGH);
led2.off();
delay(500);

digitalWrite(D7, LOW);
led2.on();
delay(500);   
digitalWrite(D7, HIGH);
led2.off();
delay(500);

digitalWrite(D7, LOW);
led2.on();
delay(500);   
digitalWrite(D7, HIGH);
led2.off();
delay(500);
}

void loop()
{
  Blynk.run();

}
