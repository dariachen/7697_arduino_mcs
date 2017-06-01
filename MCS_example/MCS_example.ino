#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

// Assign AP ssid / password here
#define _SSID "mcs"
#define _KEY  "1234"

// Assign Device ID, Device Key, MCS server IP and port.
MCSDevice mcs("DGW8G2ox", "Njefq0JvAfMB3kDE");

// Associate the Data Channel ID with the Data Channel type.
MCSControllerOnOff control_boolean("control_boolean");
MCSDisplayOnOff    display_boolean("display_boolean");

MCSControllerInteger control_integer("control_integer");
MCSDisplayInteger display_integer("display_integer");

MCSControllerFloat control_float("control_float");
MCSDisplayFloat display_float("display_float");

MCSControllerHex control_hex("control_hex");
MCSDisplayHex display_hex("display_hex");

MCSControllerString control_string("control_string");
MCSDisplayString display_string("display_string");

MCSControllerGPIO control_gpio("control_gpio");
MCSDisplayGPIO display_gpio("display_gpio");

MCSControllerPWM control_pwm("control_pwm");
MCSDisplayPWM display_pwm("display_pwm");

MCSControllerGPS control_gps("control_gps");
MCSDisplayGPS display_gps("display_gps");

MCSControllerCategory control_category("control_category");
MCSDisplayCategory display_category("display_category");

MCSControllerAnalog control_analog("control_analog");


#define LED_PIN 7

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

  // Add Data Channel to the MCSDevice
  mcs.addChannel(control_boolean);
  mcs.addChannel(display_boolean);


  mcs.addChannel(control_integer);
  mcs.addChannel(display_integer);
  mcs.addChannel(control_float);
  mcs.addChannel(display_float);
  mcs.addChannel(control_hex);
  mcs.addChannel(display_hex);
  mcs.addChannel(control_string);
  mcs.addChannel(display_string);
  mcs.addChannel(control_gpio);
  mcs.addChannel(display_gpio);
  mcs.addChannel(control_pwm);
  mcs.addChannel(display_pwm);
  mcs.addChannel(control_category);
  mcs.addChannel(display_category);
  mcs.addChannel(control_gps);
  mcs.addChannel(display_gps);
  mcs.addChannel(control_analog);
  

  // setup MCS connection
  while(!mcs.connected())
  {
    Serial.println("mcs.connect()...");
    mcs.connect();
  }
  Serial.println("mcs connected !!");

  // read LED value from MCS server
  while(!control_boolean.valid())
  {
    Serial.println("read control_boolean value from MCS...");
    control_boolean.value();
  }
  Serial.print("done, control_boolean value = ");
  Serial.println(control_boolean.value());
  digitalWrite(LED_PIN, control_boolean.value() ? HIGH : LOW);
}

void loop() {
  // call process() to allow background processing, add timeout to avoid high cpu usage
  Serial.print("process(");
  Serial.print(millis());
  Serial.println(")");
  mcs.process(1000);
  
  // updated flag will be cleared in process(), user must check it after process() call.

  // check updates for control_boolean
  if(control_boolean.updated())
  {
    Serial.print("control_boolean updated, new value = ");
    Serial.println(control_boolean.value());
    digitalWrite(LED_PIN, control_boolean.value() ? HIGH : LOW);
    if(!display_boolean.set(control_boolean.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_boolean.value());
    }
  }


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

  // check updates for control_float
  if(control_float.updated())
  {
    Serial.print("control_float updated, new value = ");
    Serial.println(control_float.value());
    if(!display_float.set(control_float.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_float.value());
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

  // check updates for control_gpio
  if(control_gpio.updated())
  {
    Serial.print("control_gpio updated, new value = ");
    Serial.println(control_gpio.value());
    if(!display_gpio.set(control_gpio.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_gpio.value());
    }
  }

  // check updates for control_pwm
  if(control_pwm.updated())
  {
    Serial.print("control_pwm updated, new duty cycle = ");
    Serial.println(control_pwm.dutyCycle());
    Serial.print("control_pwm updated, new period = ");
    Serial.println(control_pwm.period());
    if(!display_pwm.set(control_pwm.dutyCycle(), control_pwm.period()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_pwm.value());
    }
  }  

  // check updates for control_category
  if(control_category.updated())
  {
    Serial.print("control_category updated, new value = ");
    Serial.println(control_category.value());
    if(!display_category.set(control_category.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_category.value());
    }
  }  

  // check updates for control_analog
  if(control_analog.updated())
  {
    Serial.print("control_analog updated, new value = ");
    Serial.println(control_analog.value());
    if(!display_integer.set(control_analog.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_integer.value());
    }
  }  

    
  // check updates for control_gps
  if(control_gps.updated())
  {
    Serial.print("control_gps updated, new value = ");
    String gps = String(control_gps.latitude()) + "," + String(control_gps.longitude()) + "," + String(control_gps.altitude());
    Serial.println(gps);
    if(!display_string.set(gps))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_string.value());
    }
    if(!display_gps.set(control_gps.latitude(), control_gps.longitude(), control_gps.altitude()))
    {
      Serial.print("Failed to update remote");
    }
  }  
  

  // check if need to re-connect
  while(!mcs.connected())
  {
    Serial.println("re-connect to mcs...");
    mcs.connect();
    if(mcs.connected())
      Serial.println("mcs connected !!");
  }
}
