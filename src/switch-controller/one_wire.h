// One-wire setup
#include <DS2431.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS2413_FAMILY_ID    0x3A
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF

const int ONE_WIRE_PIN = 4;
OneWire oneWire(ONE_WIRE_PIN);
DS2431 ds2413(oneWire);
DallasTemperature tempsensors(&oneWire);
DeviceAddress tempDeviceAddress;
int DS2413devices = 0;
int numberOfTempSensors;

String OneWireAddressToString(DeviceAddress deviceAddress);
