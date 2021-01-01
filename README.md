# Energy-Meter
Extracting data from Energy Meter using ESP8266 and RS485
# Introduction : 
We are using VIPS 80P Energymeter to extract datas like Volatage, Current, Power Consumption and other parameters, by using ESP8266 as microcontroller. RS485 is used for Modbus RTU Protocol.
# Working :
Energymeter, when plugged in with the AC power supply, switches on and microcontroller as well. ESP8266 takes few seconds to connect to WiFi and then starts sending message to energymeter via RS485 to extract data. This process repeats itself automatically from time to time and the data hence extracted can be seen on the *Serial Monitor* as well as the _Console_
