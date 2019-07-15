
#ifndef NETATMO_VARIABLES_EXTERNES_H_
#define NETATMO_VARIABLES_EXTERNES_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <UTFT.h>
#include <UTFT_Geometry.h>

// Variable de Debug
extern bool _Debug;

// Déclaration de l'écran LCD
extern UTFT myGLCD ( SSD1963_800, 38, 39, 40, 41 ); // (byte model, int RS, int WR, int CS, int RST, int SER)
extern UTFT_Geometry geo ( &myGLCD );
extern int Ysize;	//	 Pour stocker le nombre de pixel de l'écran sur les Y (hauteur)
extern int Xsize;	//	 Pour stocker le nombre de pixel de l'écran sur les X (largeur)

// Déclaration des polices utilisées
extern uint8_t SmallFont[];				// 8x12 font
extern uint8_t BigFont[];				// 16x16 font
//extern uint8_t Grotesk16x32[];
extern uint8_t Grotesk32x64[];
extern uint8_t Grotesk24x48[];
//extern uint8_t Ubuntu[];				// 24x32 font
extern uint8_t hallfetica_normal[];		// 16x16 font
extern uint8_t arial_normal[];			// 16x16 font
//extern uint8_t arial_bold[];			// 16x16 font
//extern uint8_t arial_italic[];			// 16x16 font
//extern uint8_t franklingothic_normal[];	// 16x16 font
//extern uint8_t TinyFont[];				// 8x8 font

// ========================================== LES TEMPÉRATURES ========================================
// Température Extérieure
extern float _Temp_Ext;
extern float _Temp_Ext_Precedente;
extern String _Temp_Ext_Tendance;
extern String _Temp_Ext_Text;

// Température interieure (SALON)
extern float _Temp_Int;
extern float _Temp_Int_Precedente;
extern String _Temp_Int_Tendance;
extern String _Temp_Int_Text;

// Température interieure (CHAMBRE)
extern float _Temp_Chambre;
extern float _Temp_Chambre_Precedente;
extern String _Temp_Chambre_Tendance;
extern String _Temp_Chambre_Text;
// ****************************************************************************************************


// ============================================= L'HUMIDITÉ ===========================================
extern int _Humidite_Ext;
extern int _Humidite_Ext_Precedente;
extern String _Humidite_Ext_Text;

extern int _Humidite_Int;
extern int _Humidite_Int_Precedente;
extern String _Humidite_Int_Text;

extern int _Humidite_Chambre;
extern int _Humidite_Chambre_Precedente;
extern String _Humidite_Chambre_Text;
// ****************************************************************************************************

// ============================================= LA PLUIE =============================================
// extern float _Pluie_Heure;
// extern float _Pluie_Heure_Precedente;
// extern String _Pluie_Heure_Text;
//
// extern float _Pluie_Jour;
// extern float _Pluie_Jour_Precedente;
// extern String _Pluie_Jour_Text;
// ****************************************************************************************************

// ============================================== LE CO2 ==============================================
extern int _CO2_Int;
extern int _CO2_Int_Pecedent;
extern String _CO2_Int_Text;

extern int _CO2_Chambre;
extern int _CO2_Chambre_Precedent;
extern String _CO2_Chambre_Text;
// ****************************************************************************************************

// =========================================== LES PRESSIONS =========================================
extern int _Pression;
extern int _Pression_Precedente;
extern String _Pression_Text;
extern String _Pression_Tendance;
// ****************************************************************************************************

// =========================== HISTORIQUE DES PRESSIONS ET DES TEMPÉRATURES ===========================
extern float _HistoriqueTemperatures [2][49];
extern int _HistoriquePressions [48];
// ****************************************************************************************************


// ==============================   VALEURS POUR LES PRÉVISIONS MÉTÉO   ===============================
extern float _TempMin_Jour;
extern float _TempMax_Jour;
extern float _TempMin_Demain;
extern float _TempMax_Demain;
extern float _TempMin_Apres_Demain;
extern float _TempMax_Apres_Demain;

extern int _Meteo_Du_Jour;
extern int _Meteo_Demain;
extern int _Meteo_Apres_Demain;

extern int _Nuage_Jour;
extern int _Nuage_Demain;
extern int _Nuage_Apres_Demain;

extern float _Pluie_Du_Jour;
extern float _Pluie_Demain;
extern float _Pluie_Apres_Demain;

extern time_t _Temps_Meteo;
// ****************************************************************************************************




// ****************************************************************************************************
// ********** Variables de la gestion WIFI
extern String _wifi_SSID;
extern String _wifi_PASS;
extern String _hote_php;
// ****************************************************************************************************


// ****************************************************************************************************
// Autres variables définies ailleurs et utilisées dans d'autres modules
// Pour le module de récupération des données et leur extraction via la communication série
extern char c1;
extern char c2;

extern String request;
extern String _buffer;			// _buf dans le projet d'origine
extern int _buffer_length;		// _buf_length dans le projet d'origine
extern int _cursor;

extern time_t _CurrentTime;
extern time_t _PreviousTime;
extern bool heureEte;			// Si true alors l'heure d'été est en place, sinon, c'est l'heure d'hiver


extern int _CountDown;
extern int _PreviousCountDown;

extern unsigned long MILLIS_INTERNET;
extern unsigned long MILLIS_TIME;
extern unsigned long MILLIS_WEATHERMAP;

#endif /* NETATMO_VARIABLES_EXTERNES_H_ */
