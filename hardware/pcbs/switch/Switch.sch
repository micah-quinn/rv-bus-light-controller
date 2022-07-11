EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor_Touch:TP233_Touch_Pad TP1
U 1 1 62D51A0C
P 2450 1500
F 0 "TP1" H 2778 1117 50  0000 L CNN
F 1 "TP233_Touch_Pad" H 2778 1026 50  0000 L CNN
F 2 "Capacitor_THT:TTP23_Touch_Pad" H 2450 1550 50  0001 C CNN
F 3 "" H 2450 1550 50  0001 C CNN
	1    2450 1500
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Touch:TP233_Touch_Pad TP3
U 1 1 62D5255E
P 4950 1550
F 0 "TP3" H 5278 1167 50  0000 L CNN
F 1 "TP233_Touch_Pad" H 5278 1076 50  0000 L CNN
F 2 "Capacitor_THT:TTP23_Touch_Pad" H 4950 1600 50  0001 C CNN
F 3 "" H 4950 1600 50  0001 C CNN
	1    4950 1550
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Touch:TP233_Touch_Pad TP2
U 1 1 62D52B75
P 2550 3400
F 0 "TP2" H 2878 3017 50  0000 L CNN
F 1 "TP233_Touch_Pad" H 2878 2926 50  0000 L CNN
F 2 "Capacitor_THT:TTP23_Touch_Pad" H 2550 3450 50  0001 C CNN
F 3 "" H 2550 3450 50  0001 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Touch:TP233_Touch_Pad TP4
U 1 1 62D5373B
P 4950 3400
F 0 "TP4" H 5278 3017 50  0000 L CNN
F 1 "TP233_Touch_Pad" H 5278 2926 50  0000 L CNN
F 2 "Capacitor_THT:TTP23_Touch_Pad" H 4950 3450 50  0001 C CNN
F 3 "" H 4950 3450 50  0001 C CNN
	1    4950 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J1
U 1 1 62D53FD1
P 3600 850
F 0 "J1" V 3611 1380 50  0000 L CNN
F 1 "RJ45" V 3702 1380 50  0000 L CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 3600 875 50  0001 C CNN
F 3 "~" V 3600 875 50  0001 C CNN
	1    3600 850 
	0    1    1    0   
$EndComp
Text GLabel 3300 1250 3    50   Input ~ 0
VCC
Text GLabel 3400 1250 3    50   Input ~ 0
GND
Text GLabel 2500 1650 2    50   Input ~ 0
VCC
Text GLabel 2200 1650 0    50   Input ~ 0
GND
Text GLabel 4700 1700 0    50   Input ~ 0
GND
Text GLabel 5000 1700 2    50   Input ~ 0
VCC
Text GLabel 5000 3550 2    50   Input ~ 0
VCC
Text GLabel 4700 3550 0    50   Input ~ 0
GND
Text GLabel 2300 3550 0    50   Input ~ 0
GND
Text GLabel 2600 3550 2    50   Input ~ 0
VCC
Wire Wire Line
	3500 1250 3500 1600
Wire Wire Line
	2850 1600 2850 1250
Wire Wire Line
	2850 1250 2350 1250
Wire Wire Line
	2350 1250 2350 1650
Wire Wire Line
	2850 1600 3500 1600
Wire Wire Line
	3600 1250 3600 3150
Wire Wire Line
	3600 3150 2450 3150
Wire Wire Line
	2450 3150 2450 3550
Wire Wire Line
	3700 1250 3700 3250
Wire Wire Line
	3700 3250 4850 3250
Wire Wire Line
	4850 3250 4850 3550
Wire Wire Line
	3800 1250 3800 1350
Wire Wire Line
	3800 1350 4850 1350
Wire Wire Line
	4850 1350 4850 1700
$Comp
L Sensor_Temperature:DS18B20 U1
U 1 1 62D5E1D0
P 5800 900
F 0 "U1" H 5570 946 50  0000 R CNN
F 1 "DS18B20" H 5570 855 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4800 650 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 5650 1150 50  0001 C CNN
	1    5800 900 
	1    0    0    -1  
$EndComp
Text GLabel 5800 600  2    50   Input ~ 0
VCC
Text GLabel 5800 1200 2    50   Input ~ 0
GND
Wire Wire Line
	6100 900  6250 900 
Wire Wire Line
	6250 900  6250 1300
Wire Wire Line
	6250 1300 4000 1300
Wire Wire Line
	4000 1300 4000 1250
$Comp
L Device:LED_RCGB D1
U 1 1 62D6891B
P 6300 2900
F 0 "D1" H 6300 2433 50  0000 C CNN
F 1 "LED_RCGB" H 6300 2524 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm-4_RGB_Wide_Pins" H 6300 2850 50  0001 C CNN
F 3 "~" H 6300 2850 50  0001 C CNN
	1    6300 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 1250 3900 3100
Wire Wire Line
	3900 3100 6100 3100
Text GLabel 6500 2900 2    50   Input ~ 0
GND
$EndSCHEMATC
