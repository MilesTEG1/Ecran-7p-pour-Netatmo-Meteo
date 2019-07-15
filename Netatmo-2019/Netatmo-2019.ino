// ***********************************************************************************
// *****************  Netatmo - Afficheurs LCD - Connexion Internet  *****************
// ***********************************************************************************
// ------ Date de création : 15 Avril 2019
// ------ Date de dernière révision : 11 mai 2019
// ------ Auteur : MilesTEG
// ***********************************************************************************
// ** Pour ce projet, je me suis grandement inspiré du projet "Netatmo DualScreen Station"
// ** de Barzok : --> https://www.instructables.com/id/Netatmo-DualScreen-Station/
// ** mais aussi du projet Station méteo sur TFT 7 "
// ** de hameau : https://forum.arduino.cc/index.php?topic=559421.new#new
// ** Un très grand merci à ce dernier qui m'a beaucoup aidé et fourni des ressources
// **
// ***********************************************************************************
// Explications des objectifs de ce script et de ceux inclus pour son fonctionnement :
// L'idée est d'utiliser deux scripts PHP (netatmo2019.php et openweathermap2019.php)
// qui récupèrent via les API de Netatmo et de OpenWeatherMap les données de la sonde
// météo et des prévisions sur 5 jours.
//   J'ai du mettre à jour les scripts fourni par Barzok car l'API Netatmo à changé,
//   celle de OpenWeatherMap presque pas.
// Le script exéctué par l'Arduino va donc se connecter à interet via la shield ESP8266
// et lancer les deux scripts qui sont hébergés sur mon NAS. (Il faudra peut-être adapter
// ce point a votre utilisation, par exemple faire tourner un serveur sur votre ordinateur
// ou une autre solution.)
// Ces deux scripts formatent les données d'une certaine manière.
// netatmo2019.php retourne 4 lignes ;
// openweathermap2019.php retourne une seule ligne.
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// On inclue les différents fichiers pour le projet
// D'abord les bibliothèques
#include "TimeLib.h"
#include <UTFT.h>
#include <UTFT_Geometry.h>


// Puis les fichiers headers des modules contenant les diverses fonctions
// #include "Netatmo_Fonctions_Temps.h"
#include "Netatmo_Fonctions_Wifi.h"
#include "Netatmo_Fonctions_Affichage.h"
#include "Netatmo_Fonctions_Autres.h"
#include "Netatmo_Defines.h"

// Déclaration de l'écran LCD
UTFT myGLCD ( SSD1963_800, 38, 39, 40, 41 );    // (byte model, int RS, int WR, int CS, int RST, int SER)
UTFT_Geometry geo_myGLCD ( &myGLCD );   // Pour tracer des triangles


// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// *-*-*-*  Les variables utilisées dans tous les modules
// *-*-*-*  (Internet - Affichage - Temps)
// Les données actuelles et précédentes sont utilisées pour raffraichir l'affichage seulement si nécessaire
// Les valeurs sont en Text lorsqu'elles sont récupérées du flux internet

// ======== LES TEMPÉRATURES
// Température Extérieure
float _Temp_Ext = -99.9;
float _Temp_Ext_Precedente = -99.9;     // La valeur précédente pour la comparaison
String _Temp_Ext_Tendance  = "up";
String _Temp_Ext_Text;      // La variable text récupérée du flux Internet

// Température interieure (SALON)
float _Temp_Int = -99.9;
float _Temp_Int_Precedente = -99.9;     // La valeur précédente pour la comparaison
String _Temp_Int_Tendance  = "down";
String _Temp_Int_Text;      // La variable text récupérée du flux Internet

// Température interieure (CHAMBRE)
float _Temp_Chambre = -99.9;
float _Temp_Chambre_Precedente = -99.9;     // La valeur précédente pour la comparaison
String _Temp_Chambre_Tendance  = "down";
String _Temp_Chambre_Text;      // La variable text récupérée du flux Internet

// ======== L'HUMIDITÉ
int _Humidite_Ext = 00;
int _Humidite_Ext_Precedente = 00;
String _Humidite_Ext_Text;      // La variable text récupérée du flux Internet

int _Humidite_Int = 00;
int _Humidite_Int_Precedente = 00;
String _Humidite_Int_Text;      // La variable text récupérée du flux Internet

int _Humidite_Chambre = 00;
int _Humidite_Chambre_Precedente = 00;
String _Humidite_Chambre_Text;  // La variable text récupérée du flux Internet


// ======== LA PLUIE
// float _Pluie_Heure = 999;
// float _Pluie_Heure_Precedente = 999;
// String _Pluie_Heure_Text;            // La variable text récupérée du flux Internet

// float _Pluie_Jour = 999;
// float _Pluie_Jour_Precedente = 999;
// String _Pluie_Jour_Text;             // La variable text récupérée du flux Internet

// ======== LE CO2
int _CO2_Int = 9999;
int _CO2_Int_Precedent = 9999;
String _CO2_Int_Text;       // La variable text récupérée du flux Internet

int _CO2_Chambre = 9999;
int _CO2_Chambre_Precedent = 9999;
String _CO2_Chambre_Text;   // La variable text récupérée du flux Internet

// ======== LES PRESSIONS
int _Pression = 9999;
int _Pression_Precedente = 9999;
String _Pression_Text;      // La variable text récupérée du flux Internet
String _Pression_Tendance = "up";

// ======== HISTORIQUE DES PRESSIONS ET DES TEMPÉRATURES
int _HistoriquePressions [48];  // Pour stocker l'historique des valeurs de pression lues avec l'API Netatmo
float _HistoriqueTemperatures [2][49];  // Pour stocker l'historique des températures mini et maxi, ainsi que la plus petite et la plus grande des valeurs

// ======== VALEURS POUR LES PRÉVISIONS MÉTÉO
float _TempMin_Jour;
float _TempMax_Jour;
float _TempMin_Demain;
float _TempMax_Demain;
float _TempMin_Apres_Demain;
float _TempMax_Apres_Demain;

int _Meteo_Du_Jour;
int _Meteo_Demain;
int _Meteo_Apres_Demain;

int _Nuage_Jour;
int _Nuage_Demain;
int _Nuage_Apres_Demain;

float _Pluie_Du_Jour;
float _Pluie_Demain;
float _Pluie_Apres_Demain;

time_t _Temps_Meteo = 0;

// ********** Variables de la gestion WIFI
String _wifi_SSID = "";     // Mettre ici le SSID du réseau Wi-Fi
String _wifi_PASS = "";     // Mettre ici le Mot de passe Wi-Fi
String _hote_php  = "";     // Mettre ici l'Adresse du serveur où se trouve les scripts PHP
// Il faut juste le nom d'hote, de domaine, ou
// l'adresse IP.
// Ne pas mettre toute l'adresse du fichier PHP...

// ********** Autres variables définies ailleurs et utilisées dans d'autres modules
// Pour le module de récupération des données et leur extraction via la communication série
char c1;    // Pour lire et récupérer les données de la liaison série avec l'ESP8266
char c2;    // Pour lire et récupérer les données de la liaison série avec l'ESP8266
unsigned long MILLIS_INTERNET   = 99999999;
unsigned long MILLIS_TIME       = 99999999;
unsigned long MILLIS_WEATHERMAP = 99999999;
int _Decompte = -1;
int _Decompte_Precedent = -1;
time_t _CurrentTime;
time_t _PreviousTime = 0;
bool heureEte        = true;    // Si true alors l'heure d'été est en place, sinon, c'est l'heure d'hiver

bool _PremiereBoucle = true;
String _buffer       = "";      // C'est LA VARIABLE du programme qui va stocker les données récupérées des scripts PHP !!
int _cursor        = 0;         // Pour stocker l'index du curseur où on se trouve dans le _buffer
int _buffer_length = 0;     // Pour la longueur du _buffer



// Vérifier si ces variables ont besoin d'être déclarées dans la partie générale
String request;



// Variable de Debug
bool _Debug = true;

// ***************************************

void setup () {
    // === INITIALISATOIN ===

    Serial.begin ( 115200 );
    Serial3.begin ( 115200 );   // baudrate par défaut de l'ESP8266

    Serial.println ( F ( "===== DÉBUT DU SETUP =====" ) );

    // On s'occupe de l'écran LCD
    Serial.println ( F ( "Allumage de l'écran LCD..." ) );
    myGLCD.InitLCD ();
    pinMode ( 8, OUTPUT );      //  backlight
    digitalWrite ( 8, HIGH );   //  ON

    // Vérification des dimensions de l'écran, sinon ça va tracer n'importe quoi...
    Serial.println ( F ( "Vérification des dimensions de l'écran LCD..." ) );

    Ysize = myGLCD.getDisplayYSize ();
    Xsize = myGLCD.getDisplayXSize ();
    if ( !Xsize == 800 && !Ysize == 480 ) {
        Serial.println ( F ( "Les dimensions de l'écran connecté ne sont pas correctes...\n Le tracé à l'écran de la grille et des valeurs ne va pas fonctionner correctement. Le rendu ne sera pas celui atrendu..." ) );
    }
    else {
        Serial.println ( F ( "L'écran détecté est aux bonnes dimensions :" ) );
        Serial.print ( F ( "Taille de l'écran :  Xsize=" ) );
        Serial.print ( Xsize );
        Serial.print ( F ( "      Ysize=" ) );
        Serial.println ( Ysize );
    }

    // On affiche un écran arc-en-ciel
    myGLCD.clrScr ();
    Texte_Bonjour ();
    delay ( 1000 );

    Serial.println ( F ( "Initialisation de l'écran LCD..." ) );
    Initialisation_Affichage_LCD ();    // On trace les différentes zones d'affichage pour les données, avec les titres


    Serial.println ( F ( "===== FIN DU SETUP, LA BOUCLE LOOP COMMENCE =====" ) );
} // setup

void loop () {
    // ------ TOUTES LES 5 MINUTES ------
    // ------ CONNECTION À INTERNET ET RÉCUPÉRATION DES DONNÉES NETATMO ------
    if ( millis () - MILLIS_INTERNET > 300000 ) {
        _cursor = 0;    // flush buffer

        // Pour DEBUG sans accès wifi, on commente la ligne suivante
        WifiConnect_Netatmo ();     // connects and gets data from internet

        // DEBUG Buffer
        Serial.println ( F (  "===== DEBUG BUFFER =====" ) );
        Serial.println ( F (  "On affiche le _buffer pour vérifier" ) );
        Serial.println ( F ( "~~~~ BUFFER Netatmo ~~~~~" ) );
        Serial.println ( _buffer );
        Serial.println ( F ( "~~~~ EOBUFF Netatmo ~~~~~" ) );
        // FIN DEBUG


        if ( _buffer_length  > 700 ) {
            Serial.println ( F ( " ===== On récupère la date etc... dans le buffer =====" ) );
            GetTimeFromBuffer ();

            // C'est parti pour décoder les données du buffer
            Decodage_Donnees_Tps_Reel ();
            Decodage_Pression_Hist ();
            Decodage_Temp_Hist ();

            // Pour DEBUG
            debug_Afficher_Donnees_Sur_Serial ();
            // debug_Afficher_Donnees_Sur_TFT();

            if ( _PremiereBoucle ) {
                // TFT.fillScreen ( BLACK ); // Efface ecran
                _PremiereBoucle = false;
            }

            // Fonctions d'affichage des données A FAIRE !!!!
            // _DisplayTemp();
            // _DisplayHumidity();
            // _DisplayCO2 ();
            // _DisplayRain ();
            // _DisplayPressure ();

            // _DisplayPressureHistory ();
            // _DisplayTemperatureHistory ();
        }

        MILLIS_INTERNET = millis ();
    }

    // ------ TOUTES LES 1 SECONDE ------
    // ------ AFFICHAGE DU TEMPS ------
    if ( millis () - MILLIS_TIME > 1000 ) {     // Toutes les secondes
        Serial.println ( F ( " ===== On affiche le temps à l'écran =====" ) );

        // Fonctions d'affichage du temps A FAIRE !!!!!
        // _DisplayTime ();
        Affiche_Decompte_Actualisation ();

        MILLIS_TIME = millis ();
    }


    // ------ TOUTES LES 1 HEURE ------
    // ------ AFFICHAGE DES PRÉVISIONS MÉTÉO ------
    if ( millis () - MILLIS_WEATHERMAP > 3600000 ) {    // Toutes les 1 heure
        // Pour DEBUG sans accès wifi, on commente la ligne suivante
        WifiConnect_WeatherMap ();

        // DEBUG Buffer
        Serial.println ( F ( "===== DEBUG BUFFER =====" ) );
        Serial.println ( F ( "On affiche le _buffer pour vérifier" ) );
        Serial.println ( F ( "~~~~ BUFFER Openweahtermap ~~~~~" ) );
        Serial.println ( _buffer );
        Serial.println ( F ( "~~~~ EOBUFF Openweahtermap ~~~~~" ) );
        // FIN DEBUG

        if ( _buffer_length  > 700 ) {
            Serial.println ( F ( " ===== On récupère les prévisions météo une fois par heure =====" ) );

            // Fonction de décodage des données Openweathermap
            Decodage_Previsions_Meteo ();

            // Fonctions d'affichage des prévisions météo A FAIRE !!!!!
            // _DisplayWeather2 (X1, _TodayWeather, _TodayTempMin, _TodayTempMax, _TodayCloud, _TodayRain);
            // _DisplayWeather2 (X2, _TomorrowWeather, _TomorrowTempMin, _TomorrowTempMax, _TomorrowCloud, _TomorrowRain);
            // _DisplayWeather2 (X3, _DayAfterWeather, _DayAfterTempMin, _DayAfterTempMax, _DayAfterCloud, _DayAfterRain);
        }
        MILLIS_WEATHERMAP = millis ();
    }
} // loop



