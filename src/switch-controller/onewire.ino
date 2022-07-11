// function to print a device address
String OneWireAddressToString(DeviceAddress deviceAddress) {
  String address;
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) address += "0";
    address += String(deviceAddress[i], HEX);
  }

  return address;
}
