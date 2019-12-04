EESchema Schematic File Version 4
LIBS:1-wire-sens-cache
EELAYER 26 0
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
L power:GND #PWR0101
U 1 1 5D9E5672
P 3550 5450
F 0 "#PWR0101" H 3550 5200 50  0001 C CNN
F 1 "GND" H 3555 5277 50  0000 C CNN
F 2 "" H 3550 5450 50  0001 C CNN
F 3 "" H 3550 5450 50  0001 C CNN
	1    3550 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D9E568C
P 3550 4650
F 0 "#PWR0102" H 3550 4400 50  0001 C CNN
F 1 "GND" H 3555 4477 50  0000 C CNN
F 2 "" H 3550 4650 50  0001 C CNN
F 3 "" H 3550 4650 50  0001 C CNN
	1    3550 4650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5D9E569F
P 3550 4300
F 0 "#PWR0103" H 3550 4150 50  0001 C CNN
F 1 "+5V" H 3565 4473 50  0000 C CNN
F 2 "" H 3550 4300 50  0001 C CNN
F 3 "" H 3550 4300 50  0001 C CNN
	1    3550 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5D9E56B2
P 3550 5050
F 0 "#PWR0104" H 3550 4900 50  0001 C CNN
F 1 "+5V" H 3565 5223 50  0000 C CNN
F 2 "" H 3550 5050 50  0001 C CNN
F 3 "" H 3550 5050 50  0001 C CNN
	1    3550 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D9E59CF
P 2900 4450
F 0 "R1" V 2693 4450 50  0000 C CNN
F 1 "4k7" V 2784 4450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2830 4450 50  0001 C CNN
F 3 "~" H 2900 4450 50  0001 C CNN
	1    2900 4450
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5D9E5C00
P 2450 4450
F 0 "#PWR0105" H 2450 4300 50  0001 C CNN
F 1 "+5V" H 2465 4623 50  0000 C CNN
F 2 "" H 2450 4450 50  0001 C CNN
F 3 "" H 2450 4450 50  0001 C CNN
	1    2450 4450
	1    0    0    -1  
$EndComp
Text GLabel 5650 3700 0    50   Input ~ 0
Data1
Text GLabel 5650 3800 0    50   Input ~ 0
Data2
Text GLabel 5650 3900 0    50   Input ~ 0
Data3
Text GLabel 3100 2100 0    50   Input ~ 0
Data1
Text GLabel 3100 2200 0    50   Input ~ 0
Data2
Text GLabel 3100 2300 0    50   Input ~ 0
Data3
Text GLabel 4250 2200 2    50   Input ~ 0
sens
Text GLabel 3250 4600 3    50   Input ~ 0
sens
Text GLabel 3200 5350 3    50   Input ~ 0
sens
Wire Wire Line
	3050 4450 3150 4450
Wire Wire Line
	3800 4350 3550 4350
Wire Wire Line
	3550 4350 3550 4300
Wire Wire Line
	3550 4650 3550 4550
Wire Wire Line
	3550 4550 3800 4550
Wire Wire Line
	3250 4600 3250 4450
Connection ~ 3250 4450
Wire Wire Line
	3250 4450 3800 4450
Wire Wire Line
	2750 4450 2450 4450
Wire Wire Line
	3800 5100 3550 5100
Wire Wire Line
	3550 5100 3550 5050
Wire Wire Line
	3800 5200 3200 5200
Wire Wire Line
	3200 5350 3200 5200
Wire Wire Line
	3550 5450 3550 5300
Wire Wire Line
	3550 5300 3800 5300
Text GLabel 8400 3700 2    50   Input ~ 0
Data1a
Text GLabel 8400 3800 2    50   Input ~ 0
Data2a
Text GLabel 8400 3900 2    50   Input ~ 0
Data3a
Text GLabel 6400 1450 0    50   Input ~ 0
Data1
Text GLabel 6400 1550 0    50   Input ~ 0
Data2
Text GLabel 6400 1650 0    50   Input ~ 0
Data3
Text GLabel 7950 1450 2    50   Input ~ 0
Data1a
Text GLabel 7950 1550 2    50   Input ~ 0
Data2a
Text GLabel 7950 1650 2    50   Input ~ 0
Data3a
$Comp
L DUALRJ45:DUALRJ45 U1
U 1 1 5DC21074
P 7050 3950
F 0 "U1" H 7050 4978 50  0000 C CNN
F 1 "DUALRJ45" H 7050 4887 50  0000 C CNN
F 2 "RJ45_dual:RJ45_dual" H 7050 3950 50  0001 C CNN
F 3 "DOCUMENTATION" H 7050 3950 50  0001 C CNN
	1    7050 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5DC22CF8
P 7150 4800
F 0 "#PWR0107" H 7150 4550 50  0001 C CNN
F 1 "GND" H 7155 4627 50  0000 C CNN
F 2 "" H 7150 4800 50  0001 C CNN
F 3 "" H 7150 4800 50  0001 C CNN
	1    7150 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5DC22D45
P 7050 4800
F 0 "#PWR0108" H 7050 4550 50  0001 C CNN
F 1 "GND" H 7055 4627 50  0000 C CNN
F 2 "" H 7050 4800 50  0001 C CNN
F 3 "" H 7050 4800 50  0001 C CNN
	1    7050 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5DC22D66
P 6950 4800
F 0 "#PWR0109" H 6950 4550 50  0001 C CNN
F 1 "GND" H 6955 4627 50  0000 C CNN
F 2 "" H 6950 4800 50  0001 C CNN
F 3 "" H 6950 4800 50  0001 C CNN
	1    6950 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5DC22DB3
P 5700 3300
F 0 "#PWR0110" H 5700 3050 50  0001 C CNN
F 1 "GND" H 5705 3127 50  0000 C CNN
F 2 "" H 5700 3300 50  0001 C CNN
F 3 "" H 5700 3300 50  0001 C CNN
	1    5700 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5DC22DD4
P 8400 3150
F 0 "#PWR0111" H 8400 2900 50  0001 C CNN
F 1 "GND" H 8405 2977 50  0000 C CNN
F 2 "" H 8400 3150 50  0001 C CNN
F 3 "" H 8400 3150 50  0001 C CNN
	1    8400 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5DC22DF5
P 5950 4700
F 0 "#PWR0112" H 5950 4550 50  0001 C CNN
F 1 "+5V" H 5965 4873 50  0000 C CNN
F 2 "" H 5950 4700 50  0001 C CNN
F 3 "" H 5950 4700 50  0001 C CNN
	1    5950 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 5DC22E16
P 8250 4700
F 0 "#PWR0113" H 8250 4550 50  0001 C CNN
F 1 "+5V" H 8265 4873 50  0000 C CNN
F 2 "" H 8250 4700 50  0001 C CNN
F 3 "" H 8250 4700 50  0001 C CNN
	1    8250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3600 6150 3300
Wire Wire Line
	6150 3300 5700 3300
Wire Wire Line
	7950 3150 8400 3150
Wire Wire Line
	7950 4300 7950 4700
Wire Wire Line
	7950 4700 8250 4700
Wire Wire Line
	6150 4300 6150 4700
Wire Wire Line
	6150 4700 5950 4700
Wire Wire Line
	7950 3150 7950 3600
Wire Wire Line
	6150 3700 5650 3700
Wire Wire Line
	6150 3800 5650 3800
Wire Wire Line
	6150 3900 5650 3900
Wire Wire Line
	7950 3800 8400 3800
Wire Wire Line
	7950 3700 8400 3700
Wire Wire Line
	7950 3900 8400 3900
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5DC33416
P 4000 4450
F 0 "J2" H 4080 4492 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 4080 4401 50  0000 L CNN
F 2 "Connector_Phoenix_MC:PhoenixContact_MCV_1,5_3-G-3.81_1x03_P3.81mm_Vertical" H 4000 4450 50  0001 C CNN
F 3 "~" H 4000 4450 50  0001 C CNN
	1    4000 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J4
U 1 1 5DC334A3
P 7100 1550
F 0 "J4" H 7150 1867 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 7150 1776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 7100 1550 50  0001 C CNN
F 3 "~" H 7100 1550 50  0001 C CNN
	1    7100 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 5DC33789
P 7650 2050
F 0 "J6" V 7523 2230 50  0000 L CNN
F 1 "Conn_01x03" V 7614 2230 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7650 2050 50  0001 C CNN
F 3 "~" H 7650 2050 50  0001 C CNN
	1    7650 2050
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5DC3384A
P 6750 2250
F 0 "J5" V 6623 2430 50  0000 L CNN
F 1 "Conn_01x03" V 6714 2430 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6750 2250 50  0001 C CNN
F 3 "~" H 6750 2250 50  0001 C CNN
	1    6750 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 1450 7750 1450
Wire Wire Line
	7400 1550 7650 1550
Wire Wire Line
	7400 1650 7550 1650
Wire Wire Line
	7750 1850 7750 1450
Connection ~ 7750 1450
Wire Wire Line
	7750 1450 7950 1450
Connection ~ 7650 1550
Wire Wire Line
	7650 1550 7950 1550
Wire Wire Line
	7550 1850 7550 1650
Connection ~ 7550 1650
Wire Wire Line
	7550 1650 7950 1650
Wire Wire Line
	6900 1450 6850 1450
Wire Wire Line
	6400 1550 6750 1550
Wire Wire Line
	6900 1650 6650 1650
Connection ~ 6850 1450
Wire Wire Line
	6850 1450 6400 1450
Wire Wire Line
	6750 2050 6750 1550
Connection ~ 6750 1550
Wire Wire Line
	6750 1550 6900 1550
Connection ~ 6650 1650
Wire Wire Line
	6650 1650 6400 1650
Wire Wire Line
	6850 1450 6850 2050
Wire Wire Line
	6650 1650 6650 2050
Wire Wire Line
	7650 1550 7650 1850
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J1
U 1 1 5DC468F3
P 3500 2200
F 0 "J1" H 3550 2517 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3550 2426 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3500 2200 50  0001 C CNN
F 3 "~" H 3500 2200 50  0001 C CNN
	1    3500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2100 3950 2100
Wire Wire Line
	3950 2100 3950 2200
Wire Wire Line
	3950 2300 3800 2300
Wire Wire Line
	3800 2200 3950 2200
Connection ~ 3950 2200
Wire Wire Line
	3950 2200 3950 2300
Wire Wire Line
	3950 2200 4250 2200
Wire Wire Line
	3100 2100 3300 2100
Wire Wire Line
	3100 2200 3300 2200
Wire Wire Line
	3100 2300 3300 2300
$Comp
L Connector:Screw_Terminal_01x03 J3
U 1 1 5DC4B9A2
P 4000 5200
F 0 "J3" H 4080 5242 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 4080 5151 50  0000 L CNN
F 2 "Connector_Phoenix_MC:PhoenixContact_MCV_1,5_3-G-3.81_1x03_P3.81mm_Vertical" H 4000 5200 50  0001 C CNN
F 3 "~" H 4000 5200 50  0001 C CNN
	1    4000 5200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5DC4BED7
P 9450 1900
F 0 "H1" H 9550 1946 50  0000 L CNN
F 1 "MountingHole" H 9550 1855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO14580_Pad" H 9450 1900 50  0001 C CNN
F 3 "~" H 9450 1900 50  0001 C CNN
	1    9450 1900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5DC4BF4F
P 9500 2150
F 0 "H2" H 9600 2196 50  0000 L CNN
F 1 "MountingHole" H 9600 2105 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO14580_Pad" H 9500 2150 50  0001 C CNN
F 3 "~" H 9500 2150 50  0001 C CNN
	1    9500 2150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5DC4BF77
P 9550 2450
F 0 "H3" H 9650 2496 50  0000 L CNN
F 1 "MountingHole" H 9650 2405 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO14580_Pad" H 9550 2450 50  0001 C CNN
F 3 "~" H 9550 2450 50  0001 C CNN
	1    9550 2450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5DC4BFA9
P 9600 2750
F 0 "H4" H 9700 2796 50  0000 L CNN
F 1 "MountingHole" H 9700 2705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_ISO14580_Pad" H 9600 2750 50  0001 C CNN
F 3 "~" H 9600 2750 50  0001 C CNN
	1    9600 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D1
U 1 1 5DC4C20E
P 3300 3200
F 0 "D1" H 3300 3416 50  0000 C CNN
F 1 "D_Schottky" H 3300 3325 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 3300 3200 50  0001 C CNN
F 3 "~" H 3300 3200 50  0001 C CNN
	1    3300 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5DC4C2B4
P 3600 3200
F 0 "#PWR0114" H 3600 2950 50  0001 C CNN
F 1 "GND" H 3605 3027 50  0000 C CNN
F 2 "" H 3600 3200 50  0001 C CNN
F 3 "" H 3600 3200 50  0001 C CNN
	1    3600 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0115
U 1 1 5DC4C2DB
P 2850 3200
F 0 "#PWR0115" H 2850 3050 50  0001 C CNN
F 1 "+5V" H 2865 3373 50  0000 C CNN
F 2 "" H 2850 3200 50  0001 C CNN
F 3 "" H 2850 3200 50  0001 C CNN
	1    2850 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3200 3600 3200
Wire Wire Line
	2850 3200 3150 3200
Wire Wire Line
	3200 5200 3150 5200
Wire Wire Line
	3150 5200 3150 4450
Connection ~ 3200 5200
Connection ~ 3150 4450
Wire Wire Line
	3150 4450 3250 4450
$EndSCHEMATC
