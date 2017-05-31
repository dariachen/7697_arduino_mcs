#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

// Assign AP ssid / password here
#define _SSID "mcs"
#define _KEY  "mcs123"

// Assign Device ID, Device Key, MCS server IP and port.
MCSDevice mcs("DGW8G2ox", "Njefq0JvAfMB3kDE");

// Associate the Data Channel ID with the Data Channel type.
MCSDisplayInteger display_integer("display_integer");
MCSDisplayHex display_hex("display_hex");
MCSDisplayString display_string("display_string");

MCSControllerInteger control_integer("control_integer");
MCSControllerHex control_hex("control_hex");
MCSControllerString control_string("control_string");

#define LED_PIN 7
int count = 0;


void setup() {
  // setup Serial output at 9600
  Serial.begin(9600);
  
  // setup LED/Button pin
  pinMode(LED_PIN, OUTPUT);
  

  // setup Wifi connection
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(_SSID);
    Serial.print(",");
    Serial.print(_KEY);
    Serial.println(")...");
    WiFi.begin(_SSID, _KEY);
  }
  Serial.println("WiFi connected !!");
  Serial.print("WiFi.status()=");
  Serial.println(WiFi.status());

  // Add Data Channel to the MCSDevice
  mcs.addChannel(display_integer);
  mcs.addChannel(display_hex);
  mcs.addChannel(display_string);
  mcs.addChannel(control_integer);
  mcs.addChannel(control_hex);
  mcs.addChannel(control_string);
  

  // setup MCS connection
  while(!mcs.connected())
  {
    Serial.println("mcs.connect()...");
    mcs.connect();
  }
  Serial.println("mcs connected !!");

  // read LED value from MCS server
 /*
  while(!control_boolean.valid())
  {
    Serial.println("read control_boolean value from MCS...");
    control_boolean.value();
  }
  Serial.print("done, control_boolean value = ");
  Serial.println(control_boolean.value());
  digitalWrite(LED_PIN, control_boolean.value() ? HIGH : LOW);

 */
}

void loop() {
  // call process() to allow background processing, add timeout to avoid high cpu usage
  Serial.print("process(");
  Serial.print(millis());
  Serial.println(")");
  mcs.process(1000);

  count = count + 1;
  int upload_data = count;
  Serial.println(String(upload_data));


  Serial.println("start to upload integer...");
  display_integer.set(upload_data);
  Serial.print("WiFi.status()=");
  Serial.println(WiFi.status());
  Serial.print("mcs.connected=");
  Serial.println(mcs.connected()); 


  Serial.println("start to upload string...");
  display_string.set(String(upload_data));
  Serial.print("WiFi.status()=");
  Serial.println(WiFi.status());
  Serial.print("mcs.connected=");
  Serial.println(mcs.connected());  


  Serial.println("start to upload hex...");
  display_hex.set(upload_data);
  Serial.print("WiFi.status()=");
  Serial.println(WiFi.status());
  Serial.print("mcs.connected=");
  Serial.println(mcs.connected()); 


  
  // updated flag will be cleared in process(), user must check it after process() call.
  // check updates for control_integer
  if(control_integer.updated())
  {
    Serial.print("control_integer updated, new value = ");
    Serial.println(control_integer.value());
    if(!display_integer.set(control_integer.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_integer.value());
    }
  }

  // check updates for control_hex
  if(control_hex.updated())
  {
    Serial.print("control_hex updated, new value = ");
    Serial.println(control_hex.value());
    if(!display_hex.set(control_hex.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_hex.value());
    }
  }

  // check updates for control_string
  if(control_string.updated())
  {
    Serial.print("control_string updated, new value = ");
    Serial.println(control_string.value());
    if(!display_string.set(control_string.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_string.value());
    }
  }


  // check if need to re-connect
  while(!mcs.connected())
  {
     Serial.print("mcs.connected=");
     Serial.println(mcs.connected());
     Serial.print("WiFi.status()=");
     Serial.println(WiFi.status());
     while(WL_CONNECTED != WiFi.status())
     {
       Serial.print("Start to reconnect to Wifi...");
       WiFi.begin(_SSID, _KEY);
       delay(3000);
       Serial.print("WiFi.status()=");
       Serial.println(WiFi.status());
     }
    if(WL_CONNECTED == WiFi.status()){
      Serial.println("WiFi connected !!");
      }
    
    Serial.println("Start to reconnect to MCS...");
    mcs.connect();
    if(mcs.connected()){
      Serial.println("mcs connected !!");
    }
  }
}
