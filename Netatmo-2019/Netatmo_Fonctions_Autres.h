// ***********************************************************************************
// Netatmo_Fonctions_Wifi.h
// ***********************************************************************************

#ifndef _NETATMO_FONCTIONS_AUTRES_h
#define _NETATMO_FONCTIONS_AUTRES_h


#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif


#include "TimeLib.h"
#include "Netatmo_Variables_Externes.h"


void debug_buffer();
void debug_historique_temp_MaxMin ( int ii, int jj, String val_str, float val_flt );

time_t Conversion_String_v_TimeT ( String _TimeString );

void debug_Afficher_Donnees_Sur_Serial ( void );
void debug_Afficher_Meteo_Sur_Serial ( int ii );
void debug_Afficher_Donnees_Sur_TFT (void);


#endif /* _NETATMO_FONCTIONS_AUTRES_h */