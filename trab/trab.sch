EESchema Schematic File Version 4
LIBS:trab-cache
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
L Isolator:4N25 U?
U 1 1 5BB940A7
P 1600 1800
F 0 "U?" H 1600 2125 50  0000 C CNN
F 1 "4N25" H 1600 2034 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 1400 1600 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 1600 1800 50  0001 L CNN
	1    1600 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BB942AA
P 2050 1250
F 0 "R?" H 2120 1296 50  0000 L CNN
F 1 "10k" H 2120 1205 50  0000 L CNN
F 2 "" V 1980 1250 50  0001 C CNN
F 3 "~" H 2050 1250 50  0001 C CNN
	1    2050 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BB9433C
P 1000 1700
F 0 "R?" V 1207 1700 50  0000 C CNN
F 1 "220" V 1116 1700 50  0000 C CNN
F 2 "" V 930 1700 50  0001 C CNN
F 3 "~" H 1000 1700 50  0001 C CNN
	1    1000 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BB945F3
P 2000 2000
F 0 "#PWR?" H 2000 1750 50  0001 C CNN
F 1 "GND" H 2005 1827 50  0000 C CNN
F 2 "" H 2000 2000 50  0001 C CNN
F 3 "" H 2000 2000 50  0001 C CNN
	1    2000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1700 1300 1700
Wire Wire Line
	1900 1800 2050 1800
Wire Wire Line
	2050 1400 2050 1800
Connection ~ 2050 1800
Wire Wire Line
	1900 1900 2000 1900
Wire Wire Line
	2000 1900 2000 2000
Wire Wire Line
	850  1700 650  1700
Wire Wire Line
	1300 1900 800  1900
Wire Wire Line
	2050 1100 2050 950 
Text Label 650  1700 0    50   ~ 0
pwm
Text Label 2050 950  0    50   ~ 0
+5V
Text Label 800  1900 0    50   ~ 0
external_gnd
$Comp
L Device:R R?
U 1 1 5BB94CB0
P 3300 1800
F 0 "R?" V 3093 1800 50  0000 C CNN
F 1 "470" V 3184 1800 50  0000 C CNN
F 2 "" V 3230 1800 50  0001 C CNN
F 3 "~" H 3300 1800 50  0001 C CNN
	1    3300 1800
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:TIP122 Q?
U 1 1 5BB95020
P 7450 1550
F 0 "Q?" H 7656 1596 50  0000 L CNN
F 1 "TIP122" H 7656 1505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7650 1475 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/TI/TIP120.pdf" H 7450 1550 50  0001 L CNN
	1    7450 1550
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:TIP122 Q?
U 1 1 5BB950A7
P 7450 2850
F 0 "Q?" H 7656 2896 50  0000 L CNN
F 1 "TIP122" H 7656 2805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7650 2775 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/TI/TIP120.pdf" H 7450 2850 50  0001 L CNN
	1    7450 2850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BB9588A
P 6500 3100
F 0 "#PWR?" H 6500 2850 50  0001 C CNN
F 1 "GND" H 6505 2927 50  0000 C CNN
F 2 "" H 6500 3100 50  0001 C CNN
F 3 "" H 6500 3100 50  0001 C CNN
	1    6500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1400 5750 1350
Wire Wire Line
	7350 1400 7350 1350
Wire Wire Line
	5750 1050 6550 1050
Connection ~ 7350 1350
Wire Wire Line
	7350 1350 7350 1050
Wire Wire Line
	7350 1750 7350 1950
$Comp
L Device:R R?
U 1 1 5BB9AD84
P 7750 3050
F 0 "R?" H 7820 3096 50  0000 L CNN
F 1 "47000" H 7820 3005 50  0000 L CNN
F 2 "" V 7680 3050 50  0001 C CNN
F 3 "~" H 7750 3050 50  0001 C CNN
	1    7750 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3350 7750 3200
Wire Wire Line
	7750 2900 7750 2850
Wire Wire Line
	7750 2850 7650 2850
Wire Wire Line
	7750 1550 7650 1550
Wire Wire Line
	6550 1050 6550 900 
Connection ~ 6550 1050
Wire Wire Line
	6550 1050 7350 1050
Text Label 6550 900  0    50   ~ 0
+27V
$Comp
L Diode:1N4148 D?
U 1 1 5BB9C43F
P 6200 1600
F 0 "D?" H 6200 1816 50  0000 C CNN
F 1 "1N4148" H 6200 1725 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6200 1425 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6200 1600 50  0001 C CNN
	1    6200 1600
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BB9E4FF
P 6850 1600
F 0 "D?" H 6850 1816 50  0000 C CNN
F 1 "1N4148" H 6850 1725 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6850 1425 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6850 1600 50  0001 C CNN
	1    6850 1600
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BB9E9D0
P 6200 2800
F 0 "D?" H 6200 3016 50  0000 C CNN
F 1 "1N4148" H 6200 2925 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6200 2625 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6200 2800 50  0001 C CNN
	1    6200 2800
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BB9EEA9
P 6800 2800
F 0 "D?" H 6800 3016 50  0000 C CNN
F 1 "1N4148" H 6800 2925 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6800 2625 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6800 2800 50  0001 C CNN
	1    6800 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 2650 6200 2450
Wire Wire Line
	6200 2450 5750 2450
Connection ~ 5750 2450
Wire Wire Line
	5750 2450 5750 2550
Wire Wire Line
	5750 2950 5750 3100
Wire Wire Line
	5750 3100 6200 3100
Wire Wire Line
	6500 3100 6800 3100
Wire Wire Line
	7350 3100 7350 3050
Connection ~ 6500 3100
Wire Wire Line
	6200 2950 6200 3100
Connection ~ 6200 3100
Wire Wire Line
	6200 3100 6500 3100
Wire Wire Line
	6800 2950 6800 3100
Connection ~ 6800 3100
Wire Wire Line
	6800 3100 7350 3100
Wire Wire Line
	6800 2650 6800 2450
Wire Wire Line
	6800 2450 7350 2450
Connection ~ 7350 2450
Wire Wire Line
	7350 2450 7350 2650
Wire Wire Line
	6200 1450 6200 1350
Wire Wire Line
	6200 1350 5750 1350
Connection ~ 5750 1350
Wire Wire Line
	5750 1350 5750 1050
Wire Wire Line
	6200 1750 6200 1950
Wire Wire Line
	6200 1950 5750 1950
Connection ~ 5750 1950
Wire Wire Line
	5750 1950 5750 2200
Wire Wire Line
	6850 1450 6850 1350
Wire Wire Line
	6850 1350 7350 1350
Wire Wire Line
	6850 1750 6850 1950
Wire Wire Line
	6850 1950 7350 1950
Connection ~ 7350 1950
Wire Wire Line
	7350 1950 7350 2200
Wire Wire Line
	5750 2200 6050 2200
Connection ~ 5750 2200
Wire Wire Line
	5750 2200 5750 2450
Wire Wire Line
	7350 2200 7000 2200
Connection ~ 7350 2200
Wire Wire Line
	7350 2200 7350 2450
Text Label 6050 2200 0    50   ~ 0
SAIDA+
Text Label 7000 2200 0    50   ~ 0
SAIDA-
$Comp
L Transistor_BJT:TIP122 Q?
U 1 1 5BB94F89
P 5650 2750
F 0 "Q?" H 5857 2796 50  0000 L CNN
F 1 "TIP122" H 5857 2705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5850 2675 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/TI/TIP120.pdf" H 5650 2750 50  0001 L CNN
	1    5650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1800 5750 1750
Wire Wire Line
	5750 1800 5750 1950
Connection ~ 5750 1800
$Comp
L Transistor_BJT:TIP122 Q?
U 1 1 5BB94F00
P 5650 1600
F 0 "Q?" H 5857 1646 50  0000 L CNN
F 1 "TIP122" H 5857 1555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5850 1525 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/TI/TIP120.pdf" H 5650 1600 50  0001 L CNN
	1    5650 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BBAA450
P 5200 2750
F 0 "R?" V 4993 2750 50  0000 C CNN
F 1 "47k" V 5084 2750 50  0000 C CNN
F 2 "" V 5130 2750 50  0001 C CNN
F 3 "~" H 5200 2750 50  0001 C CNN
	1    5200 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 3350 5000 3350
Wire Wire Line
	5000 3350 5000 2750
$Comp
L Transistor_BJT:BC337 Q?
U 1 1 5BBACEED
P 4450 2950
F 0 "Q?" H 4641 2996 50  0000 L CNN
F 1 "BC337" H 4641 2905 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4650 2875 50  0001 L CIN
F 3 "http://www.nxp.com/documents/data_sheet/BC817_BC817W_BC337.pdf" H 4450 2950 50  0001 L CNN
	1    4450 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2750 5000 2750
Wire Wire Line
	4550 3150 4550 3250
$Comp
L power:GND #PWR?
U 1 1 5BBAEC9E
P 4550 3250
F 0 "#PWR?" H 4550 3000 50  0001 C CNN
F 1 "GND" H 4555 3077 50  0000 C CNN
F 2 "" H 4550 3250 50  0001 C CNN
F 3 "" H 4550 3250 50  0001 C CNN
	1    4550 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BBAEE89
P 4550 2450
F 0 "R?" V 4343 2450 50  0000 C CNN
F 1 "2k2" V 4434 2450 50  0000 C CNN
F 2 "" V 4480 2450 50  0001 C CNN
F 3 "~" H 4550 2450 50  0001 C CNN
	1    4550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2750 4550 2600
Connection ~ 4550 2750
Text Label 4550 2200 0    50   ~ 0
+27V
Wire Wire Line
	4550 2300 4550 2200
$Comp
L Device:R R?
U 1 1 5BBBCA51
P 4900 1600
F 0 "R?" V 4693 1600 50  0000 C CNN
F 1 "47k" V 4784 1600 50  0000 C CNN
F 2 "" V 4830 1600 50  0001 C CNN
F 3 "~" H 4900 1600 50  0001 C CNN
	1    4900 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 550  7750 550 
Wire Wire Line
	7750 550  7750 1550
Connection ~ 5000 2750
$Comp
L Transistor_BJT:BC337 Q?
U 1 1 5BBC1473
P 3750 1800
F 0 "Q?" H 3941 1846 50  0000 L CNN
F 1 "BC337" H 3941 1755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3950 1725 50  0001 L CIN
F 3 "http://www.nxp.com/documents/data_sheet/BC817_BC817W_BC337.pdf" H 3750 1800 50  0001 L CNN
	1    3750 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2000 3850 2100
$Comp
L power:GND #PWR?
U 1 1 5BBC147B
P 3850 2100
F 0 "#PWR?" H 3850 1850 50  0001 C CNN
F 1 "GND" H 3855 1927 50  0000 C CNN
F 2 "" H 3850 2100 50  0001 C CNN
F 3 "" H 3850 2100 50  0001 C CNN
	1    3850 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5BBC1481
P 3850 1350
F 0 "R?" V 3643 1350 50  0000 C CNN
F 1 "2k2" V 3734 1350 50  0000 C CNN
F 2 "" V 3780 1350 50  0001 C CNN
F 3 "~" H 3850 1350 50  0001 C CNN
	1    3850 1350
	1    0    0    -1  
$EndComp
Text Label 3850 1100 0    50   ~ 0
+27V
Wire Wire Line
	3850 1200 3850 1100
Wire Wire Line
	3850 1600 3850 1500
$Comp
L 74xx:74HC14 U?
U 1 1 5BBCC109
P 3000 2950
F 0 "U?" H 3000 3267 50  0000 C CNN
F 1 "74HC14" H 3000 3176 50  0000 C CNN
F 2 "" H 3000 2950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3000 2950 50  0001 C CNN
	1    3000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2750 5050 2750
Wire Wire Line
	5350 2750 5450 2750
Connection ~ 3850 1600
Wire Wire Line
	3850 1600 4400 1600
Wire Wire Line
	4400 550  4400 1600
Wire Wire Line
	5050 1600 5450 1600
Wire Wire Line
	4750 1600 4400 1600
Connection ~ 4400 1600
Wire Wire Line
	3450 1800 3550 1800
$Comp
L Device:R R?
U 1 1 5BBF32AF
P 3600 2950
F 0 "R?" V 3393 2950 50  0000 C CNN
F 1 "470" V 3484 2950 50  0000 C CNN
F 2 "" V 3530 2950 50  0001 C CNN
F 3 "~" H 3600 2950 50  0001 C CNN
	1    3600 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	3750 2950 4250 2950
Wire Wire Line
	3300 2950 3450 2950
Wire Wire Line
	2700 2950 2700 1800
Connection ~ 2700 1800
Wire Wire Line
	2700 1800 3150 1800
Wire Wire Line
	2050 1800 2700 1800
$Comp
L trab:LS7366R U?
U 1 1 5BBFFD64
P 2800 5600
F 0 "U?" H 3775 6715 50  0000 C CNN
F 1 "LS7366R" H 3775 6624 50  0000 C CNN
F 2 "" H 3800 6600 50  0001 C CNN
F 3 "" H 3800 6600 50  0001 C CNN
	1    2800 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y?
U 1 1 5BC00BEE
P 2150 4700
F 0 "Y?" V 2104 4831 50  0000 L CNN
F 1 "30MHz" V 2195 4831 50  0000 L CNN
F 2 "" H 2150 4700 50  0001 C CNN
F 3 "~" H 2150 4700 50  0001 C CNN
	1    2150 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5BC026B2
P 2650 4700
F 0 "R?" V 2443 4700 50  0000 C CNN
F 1 "1M" V 2534 4700 50  0000 C CNN
F 2 "" V 2580 4700 50  0001 C CNN
F 3 "~" H 2650 4700 50  0001 C CNN
	1    2650 4700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 4550 2150 4500
Wire Wire Line
	2150 4500 2650 4500
Wire Wire Line
	2650 4500 2650 4550
Wire Wire Line
	2650 4850 2650 4900
Wire Wire Line
	2650 4900 2150 4900
Wire Wire Line
	2150 4900 2150 4850
$Comp
L Device:C C?
U 1 1 5BC13B83
P 1700 4500
F 0 "C?" V 1448 4500 50  0000 C CNN
F 1 "C" V 1539 4500 50  0000 C CNN
F 2 "" H 1738 4350 50  0001 C CNN
F 3 "~" H 1700 4500 50  0001 C CNN
	1    1700 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 4500 1850 4500
Connection ~ 2150 4500
$Comp
L Device:C C?
U 1 1 5BC196FF
P 1700 4900
F 0 "C?" V 1448 4900 50  0000 C CNN
F 1 "C" V 1539 4900 50  0000 C CNN
F 2 "" H 1738 4750 50  0001 C CNN
F 3 "~" H 1700 4900 50  0001 C CNN
	1    1700 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 4900 2150 4900
Connection ~ 2150 4900
Wire Wire Line
	1550 4500 1400 4500
Wire Wire Line
	1400 4500 1400 4900
Wire Wire Line
	1400 4900 1550 4900
$Comp
L power:GND #PWR?
U 1 1 5BC1DAA7
P 1400 5000
F 0 "#PWR?" H 1400 4750 50  0001 C CNN
F 1 "GND" H 1405 4827 50  0000 C CNN
F 2 "" H 1400 5000 50  0001 C CNN
F 3 "" H 1400 5000 50  0001 C CNN
	1    1400 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 5000 1400 4900
Connection ~ 1400 4900
Wire Wire Line
	2650 4900 3350 4900
Connection ~ 2650 4900
Wire Wire Line
	3350 4750 3200 4750
Wire Wire Line
	3200 4750 3200 4500
Wire Wire Line
	3200 4500 2650 4500
Connection ~ 2650 4500
$EndSCHEMATC
