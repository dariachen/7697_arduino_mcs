#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

// Assign AP ssid / password here
#define _SSID "daria"
#define _KEY  "0918410123"

float f = 56.45;
// Assign Device ID, Device Key, MCS Lite server IP and port.
MCSLiteDevice mcs_lite("H1gEkw-x-", "ab5ba502ce43ec8fb5a92a85406d7faa6fcaed0873c9500f67be8f2a2bd5f01c", "192.168.1.129", 3000);


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

  // Add Data Channel to the MCSLiteDevice
  mcs_lite.addChannel(control_boolean);
  mcs_lite.addChannel(display_boolean);


  mcs_lite.addChannel(control_integer);
  mcs_lite.addChannel(display_integer);
  mcs_lite.addChannel(control_float);
  mcs_lite.addChannel(display_float);
  mcs_lite.addChannel(control_hex);
  mcs_lite.addChannel(display_hex);
  mcs_lite.addChannel(control_string);
  mcs_lite.addChannel(display_string);
  mcs_lite.addChannel(control_gpio);
  mcs_lite.addChannel(display_gpio);
  mcs_lite.addChannel(control_pwm);
  mcs_lite.addChannel(display_pwm);


  // setup MCS Lite connection
  while(!mcs_lite.connected())
  {
    Serial.println("mcs_lite.connect()...");
    mcs_lite.connect();
  }
  Serial.println("mcs_lite connected !!");

  // read LED value from MCS server
  while(!control_boolean.valid())
  {
    Serial.println("read control_boolean value from MCS Lite...");
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
  mcs_lite.process(1000);
  
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
    else
    {
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
    Serial.print("control_pwm updated, new value = ");
    Serial.println(control_pwm.value());
    Serial.print("control_pwm updated, new period = ");
    Serial.println(control_pwm.period());
    if(!display_pwm.set(control_pwm.value(), control_pwm.period()))
    {
      Serial.print("Failed to update remote");
      Serial.println(display_pwm.value());
    }
  }  
  
  
  // check if need to re-connect
  while(!mcs_lite.connected())
  {
    Serial.println("re-connect to mcs_lite...");
    mcs_lite.connect();
    if(mcs_lite.connected())
      Serial.println("mcs_lite connected !!");
  }
}
