//Made By: Chris Minheere
//13-12-2018
//Phone Controlled Lights for hand cart
//
//Sketch uses 271076 bytes (25%) of program storage space. Maximum is 1044464 bytes.
//Global variables use 30872 bytes (37%) of dynamic memory, leaving 51048 bytes for local variables. Maximum is 81920 bytes.


#define BLYNK_PRINT Serial    //Remove by end product. lets it run more smoothly.
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "your blynk auth ky";   //Authentication ky for the Blynk app 
const char* KNOWN_SSID[] = {"your wifi network 1", "your wifi network 2", "your wifi network 3"}; //Put all Your WiFi Network Names
const char* KNOWN_PASSWORD[] = {"password 1", "password 2", "password 3"}; //Put the WiFi Passwords in same order. For Open networks leave the password blank inside the double quotes.
const int KNOWN_SSID_COUNT = sizeof(KNOWN_SSID) / sizeof(KNOWN_SSID[0]); // number of known networks

void setup() {
  pinMode(D2, OUTPUT);  //set pin to output                                                             //////////////////////////////////////////
  pinMode(D7, OUTPUT);  //set pin to output                                                             // "Wifi SSID 1", "Wifi SSID 2"         //
  pinMode(D8, OUTPUT);  //set pin to output                                                             // "Wifi PASSWORD 1", "Wifi PASSWORD 2" //
                                                                                                        //////////////////////////////////////////
  boolean wifiFound = false;                                                                            
  int i, n;

  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); 
  delay(100);
  Serial.println("Setup done");

  // WiFi.scanNetworks will return the number of networks found
  Serial.println(F("Scan start"));
  int nbVisibleNetworks = WiFi.scanNetworks();
  Serial.println(F("Scan Completed"));
  if (nbVisibleNetworks == 0) {
    Serial.println(F("No networks found. Reset to try again"));
    while (true); // no need to go further, hang in there, will auto launch the Soft WDT reset
  }

  // if you arrive here at least some networks are visible
  Serial.print(nbVisibleNetworks);
  Serial.println(" network(s) found");

  // check if we recognize one by comparing the visible networks
  // one by one with our list of known networks
  for (i = 0; i < nbVisibleNetworks; ++i) {
    Serial.println(WiFi.SSID(i)); // Print current SSID
    for (n = 0; n < KNOWN_SSID_COUNT; n++) { // walk through the list of known SSID and check for a match
      if (strcmp(KNOWN_SSID[n], WiFi.SSID(i).c_str())) {
        Serial.print(F("\tNot matching "));
        Serial.println(KNOWN_SSID[n]);
      } else { // we got a match
        wifiFound = true;
        break; // n is the network index we found
      }
    } // end for each known wifi SSID
    if (wifiFound) break; // break from the "for each visible network" loop
  }

  if (!wifiFound) {
    Serial.println(F("No Known Network identified. Reset to try again"));
    while (true);
  }

  const char* ssid = (KNOWN_SSID[n]);
  const char* pass = (KNOWN_PASSWORD[n]);
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk Connected"); //Connected and Authenticated with Blynk Server
}


//-----Right blinker-----//
BLYNK_WRITE(V1) {
  WidgetLED led1(V3);
  Blynk.setProperty(V3, "color", "#ff9933");

  for (int i = 0; i <= 4; i++) {
    digitalWrite(D2, LOW);
    led1.on();
    delay(500);
    digitalWrite(D2, HIGH);
    led1.off();
    delay(500);
  }
}

//-----Left blinker-----//
BLYNK_WRITE(V2)
{
  WidgetLED led2(V4);
  Blynk.setProperty(V4, "color", "#ff9933");

  for (int i = 0; i <= 4; i++) {
    digitalWrite(D7, LOW);
    led2.on();
    delay(500);
    digitalWrite(D7, HIGH);
    led2.off();
    delay(500);

  }
}

//----Fun mode----//
BLYNK_WRITE(V5) {
  for (int i = 0; i <= 3; i++) {
    digitalWrite(D2, LOW);
    delay(500);
    digitalWrite(D8, LOW);
    delay(500);
    digitalWrite(D7, LOW);
    delay(500);
    digitalWrite(D2, HIGH);
    delay(500);
    digitalWrite(D8, HIGH);
    delay(500);
    digitalWrite(D7, HIGH);
    delay(500);
  }
}

//-----hazards lights-----//
BLYNK_WRITE(V6) {
  WidgetLED led1(V3);
  WidgetLED led2(V4);
  Blynk.setProperty(V3, "color", "#ff9933");
  Blynk.setProperty(V4, "color", "#ff9933");

  for (int i = 0; i <= 5; i++) {
    digitalWrite(D2, LOW);
    digitalWrite(D7, LOW);
    led1.on();
    led2.on();
    delay(500);
    digitalWrite(D2, HIGH);
    digitalWrite(D7, HIGH);
    led1.off();
    led2.off();
    delay(500);
  }
}

//------Strobe function------//
BLYNK_WRITE(V7) {
  for (int i = 0; i <= 50; i++) {
    digitalWrite(D2, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    delay(20);
    digitalWrite(D2, HIGH);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    delay(20);
  }
}


//------Blynk Start-----//
void loop()
{
  Blynk.run();
}
