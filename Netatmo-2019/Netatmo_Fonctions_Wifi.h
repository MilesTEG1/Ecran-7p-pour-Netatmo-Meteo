// ***********************************************************************************
// Netatmo_Fonctions_Wifi.h
// ***********************************************************************************

#ifndef _NETATMO_FONCTIONS_WIFI_h
#define _NETATMO_FONCTIONS_WIFI_h


#if defined ( ARDUINO ) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "TimeLib.h"
// #include "Netatmo_Variables_Externes.h"

void WifiConnect_Netatmo ( void );
void WifiConnect_WeatherMap ( void );

void Decodage_Donnees_Tps_Reel ( void );
void Decodage_Pression_Hist ( void );
void Decodage_Temp_Hist ( void );

void Decodage_Previsions_Meteo ( void );

String Lecture_Buffer_Pourcent ( void );
String Lecture_Buffer ( void );


int ReadSerial3 ( void );
void ReadSerial3forData ( void );

void GetTimeFromBuffer ( void );

void debug_buffer ();

#endif	/* _NETATMO_FONCTIONS_WIFI_h */



