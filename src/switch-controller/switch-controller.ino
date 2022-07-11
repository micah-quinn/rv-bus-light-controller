// RV-Bus switch controller
#include <Arduino.h>
#include <ETH.h>
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>

#include "one_wire.h"
#include "mcp23xx7.h"

// Ethernet setup
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

static bool eth_connected = false;
WiFiClient client;

void WiFiEvent(WiFiEvent_t event);

// MQTT setup
const char MQTTserver[] = "10.0.0.66";
int        MQTTport = 1883;

static bool mqtt_connected = false;
MqttClient mqttClient(client);

// Button state
int pressed[NUMBER_OF_MCP23017][NUMBER_OF_PINS];
int oldPressed[NUMBER_OF_MCP23017][NUMBER_OF_PINS];

// Temperature read
const long tempReadInterval = 60000;
unsigned long tempPreviousReadTime = 0;

// MQTT
unsigned long previousMillis;
const unsigned long interval = 3000;

void setRGB(int R, int G, int B)
{

  mcp23017[3].pinMode(7, OUTPUT);
  mcp23017[3].pinMode(6, OUTPUT);
  mcp23017[3].pinMode(5, OUTPUT);

  // 7=R, 6=G, 5=B
  mcp23017[3].digitalWrite(7, R);
  mcp23017[3].digitalWrite(6, G);
  mcp23017[3].digitalWrite(5, B);
}

bool sendMQTTMessage(String topic, const String &message)
{
  // Check connection; connect if necessary
  if (eth_connected) {
    if (!mqtt_connected) {
      // Connect
      if (mqttClient.connect(MQTTserver, MQTTport)) {
        mqtt_connected = true;
      }
      else {
        mqtt_connected = false;
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
      }
    }

    // Send the message
    if (mqtt_connected){
      mqttClient.beginMessage(topic);
      mqttClient.print(message);
      mqttClient.endMessage();      
      return true;
    }
  }

  return false;
}

void setup()
{

  bool setupSuccess = true;

  Serial.print("RV-Bus Switch Controller Starting...\n");

  Serial.begin(115200);

  Serial.println("Initializing MCP23017 array...\n");

  // Initialize the MCP23017 chips (mass GPIO)
  for (int i = 0; i < NUMBER_OF_MCP23017; i++)
  {
    Serial.print("Initializing MCP23017 ");
    Serial.println(0x20 + i, DEC);
    if (!mcp23017[i].begin_I2C(0x20 + i)) {
      Serial.print("ERROR: Could not initialize MCP23017 at addr: ");
      Serial.println(0x20 + i, DEC);
      setupSuccess = false;
    }
    else {
      for (int pin = 0; pin < NUMBER_OF_PINS; pin++) {
        if (i == 3 && pin >= 5 && pin <= 7) {
        }
        else {
          mcp23017[i].pinMode(pin, INPUT_PULLUP);
        }
      }
    }
    Serial.print("MCP23017 initialized at addr: ");
    Serial.println(0x20 + i, DEC);
  }

  setRGB(HIGH, LOW, HIGH);  // Purple

  delay(1000);

  // Start network
  WiFi.onEvent(WiFiEvent);
  ETH.begin();

  // Find temperature sensors
  Serial.println("Initializing temperature sensors...");
  tempsensors.begin();
  numberOfTempSensors = tempsensors.getDeviceCount();
  Serial.print("   Found ");
  Serial.print(numberOfTempSensors, DEC);
  Serial.println(" temperature sensors.");

  delay(1000);

  // Loop through each temp sensor, print out address
  for (int i = 0; i < numberOfTempSensors; i++) {
    if (tempsensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("   ");
      Serial.print(i, DEC);
      Serial.print(" Addr: ");
      Serial.print(OneWireAddressToString(tempDeviceAddress));
      Serial.println();
    } else {
      Serial.print("WARNING: Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

  if (numberOfTempSensors < 1)
  {
    setupSuccess = false;
  }
  tempPreviousReadTime = millis();

  delay(1000);

  if (setupSuccess) {
    setRGB(LOW, HIGH, LOW);  // Green
  }
  else {
    setRGB(HIGH, LOW, LOW);  // Red
  }

}

void loop()
{

  if (millis() - tempPreviousReadTime > tempReadInterval) {
    tempsensors.requestTemperatures();

    // Loop through each device, print out temperature data
    for (int i = 0; i < numberOfTempSensors; i++) {
      // Search the wire for address
      if (tempsensors.getAddress(tempDeviceAddress, i)) {

        // Output the device ID
        Serial.print("Temperature for device: ");
        Serial.println(i, DEC);

        // Print the data
        float tempC = tempsensors.getTempC(tempDeviceAddress);
        Serial.print("Temp C: ");
        Serial.print(tempC);
        Serial.print(" Temp F: ");
        Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit

        DynamicJsonDocument tempMessage(1024);
        tempMessage["sensor"] = OneWireAddressToString(tempDeviceAddress);
        tempMessage["fahrenheit"] = DallasTemperature::toFahrenheit(tempC);
        String mqttMessage;
        serializeJson(tempMessage, mqttMessage);

        sendMQTTMessage("temperature", mqttMessage);
      }
    }
    tempPreviousReadTime = millis();
  }

  // Read switches
  for (int i = 0; i < NUMBER_OF_MCP23017; i++)
  {
    for (int pin = 0; pin < NUMBER_OF_PINS; pin++) {
      // The RGB LED on the PCB
      if (i == 3 && pin >= 5 && pin <= 7) {
        switch (pin)
        {
          case 5:
            pressed[i][pin] = 'B';
            break;
          case 6:
            pressed[i][pin] = 'G';
            break;
          case 7:
            pressed[i][pin] = 'R';
            break;
        }
      }
      else {
        pressed[i][pin] = mcp23017[i].digitalRead(pin);
      }
    }
  }

  // pressed state changed
  if (memcmp(pressed, oldPressed, sizeof(pressed)) != 0)
  {
    // Build message
    DynamicJsonDocument switchMessage(2048);
    for (int i = 0; i < NUMBER_OF_MCP23017; i++)
    {
      for (int pin = 0; pin < NUMBER_OF_PINS; pin++) {
        switchMessage["mcp"][i][pin] = pressed[i][pin];
      }
    }

    String mqttMessage;
    serializeJson(switchMessage, mqttMessage);
    sendMQTTMessage("switches", mqttMessage);

    for (int i = 0; i < NUMBER_OF_MCP23017; i++)
    {
      Serial.print("MCP");
      Serial.print(20 + i, DEC);
      Serial.println(":");
      for (int pin = 0; pin < NUMBER_OF_PINS; pin++) {
        Serial.print(pressed[i][pin]);
      }
      Serial.println("");
      for (int pin = 0; pin < NUMBER_OF_PINS; pin++) {
        Serial.print(oldPressed[i][pin]);
      }
      Serial.println("");
    }


    // Flash LED and update oldPressed
    setRGB(LOW, LOW, HIGH);
    memcpy(oldPressed, pressed, sizeof(pressed));


  }
  else {
    setRGB(LOW, HIGH, LOW); // Green
  }

  // Read MQTT messages
  if (mqtt_connected) {
    mqttClient.poll();
  }


}
