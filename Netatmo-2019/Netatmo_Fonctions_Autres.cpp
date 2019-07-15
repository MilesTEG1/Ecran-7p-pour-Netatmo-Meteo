// ***********************************************************************************
// *****************  Netatmo - Afficheurs LCD - Connexion Internet  *****************
// ******
// ****** Fonctions Diverses pour gérer le debugage
// ****** ou pour afficher dans le moniteur série les valeurs récuppérées
// ******
// ------ Date de création : 20 Mai 2019
// ------ Date de dernière révision : 09 juillet 2019
// ------ Auteur : MilesTEG
// ------
// ***********************************************************************************
// ***********************************************************************************

// Les include pour le bon déroulement de la compilation
#include "TimeLib.h"
#include "Netatmo_Variables_Externes.h"
#include "Netatmo_Fonctions_Wifi.h"
#include "Netatmo_Fonctions_Affichage.h"
#include "Netatmo_Defines.h"
#include "Netatmo_Fonctions_Autres.h"


void debug_buffer() {
    if ( _cursor >= _buffer.length() ) {
        Serial.print ( F ( "buffer read error: " ) );
        Serial.print ( _cursor );
        Serial.print ( F ( " > " ) );
        Serial.println ( _buffer.length() );
    }
}

void debug_historique_temp_MaxMin ( int ii, int jj, String val_str, float val_flt ) {
    // ----- DEBUG
    if ( ii == 0 && jj == 0 ) Serial.println ( F ( "--DEBUG Historique Temp. MaxMin--" ) );
    Serial.print ( "->" );
    Serial.print ( ii );
    Serial.print ( " <--> " );
    Serial.print ( val_str );
    Serial.print ( " <--> " );
    Serial.print ( val_flt );
    Serial.print ( " <--> " );
    Serial.println ( val_flt, 1 );
    if ( ii == 47 && jj == 47 ) Serial.println ( F ( "--FIN DEBUG--" ) );
    // ----- FIN DEBUG
}

// -------------------------------------------------------------------

time_t Conversion_String_v_TimeT ( String _TimeString ) {
    time_t _ComputeTime = 1400000000;
    _ComputeTime = _ComputeTime + ( _TimeString.substring ( 2, 6 ) ).toInt() * 10000;
    _ComputeTime = _ComputeTime + ( _TimeString.substring ( 6, 10 ) ).toInt();
    return _ComputeTime;
}

// -------------------------------------------------------------------

void debug_Afficher_Donnees_Sur_Serial ( void ) {
    // Pour DEBUG
    Serial.println ( F ( "--DEBUG--" ) );
    Serial.println ( F ( "----- Temp. Ext" ) );
    Serial.print ( F ( "Variable float brute : " ) );
    Serial.println ( _Temp_Ext );
    Serial.print ( F ( "Variable float arrondie : " ) );
    Serial.println ( _Temp_Ext, 1 );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Ext_Text );
    Serial.println ( F ( "----- Temp. Ext Tendance" ) );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Ext_Tendance );
    Serial.println ( F ( "----- humidité Ext." ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _Humidite_Ext );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Humidite_Ext_Text );
    Serial.println ( F ( "----- Temp. Int. Salon" ) );
    Serial.print ( F ( "Variable float brute : " ) );
    Serial.println ( _Temp_Int );
    Serial.print ( F ( "Variable float arrondie : " ) );
    Serial.println ( _Temp_Int, 1 );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Int_Text );
    Serial.println ( F ( "----- Temp. int. Tendance" ) );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Int_Tendance );
    Serial.println ( "----- humidité Int." ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _Humidite_Int );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Humidite_Int_Text );
    Serial.println ( F ( "----- Pression" ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _Pression );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Pression_Text );
    Serial.println ( F ( "----- Pression Tendance" ) );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Pression_Tendance );
    Serial.println ( F ( "----- CO2 Salon" ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _CO2_Int );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _CO2_Int_Text );
    Serial.println ( F ( "----- Temp. Chambre" ) );
    Serial.print ( F ( "Variable float brute : " ) );
    Serial.println ( _Temp_Chambre );
    Serial.print ( F ( "Variable float arrondie : " ) );
    Serial.println ( _Temp_Chambre, 1 );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Chambre_Text );
    Serial.println ( F ( "----- Temp. chambre Tendance" ) );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Temp_Chambre_Tendance );
    Serial.println ( F ( "----- humidité Chambre" ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _Humidite_Chambre );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _Humidite_Chambre_Text );
    Serial.println ( F ( "----- CO2 Chambre" ) );
    Serial.print ( F ( "Variable int : " ) );
    Serial.println ( _CO2_Chambre );
    Serial.print ( F ( "Variable texte : " ) );
    Serial.println ( _CO2_Chambre_Text );
    Serial.println ( F ( "--FIN DEBUG--" ) );
    // FIN DEBUG
}


void debug_Afficher_Meteo_Sur_Serial ( int ii ) {
    // ii=1 -> Valeurs d'aujourd'hui uniquement
    // ii=2 -> Valeurs d'aujourd'hui & demain
    // ii=3 -> Valeurs d'aujourd'hui & demain & après-demain

    Serial.println ( F ( "======== Données OpenWeathermap =========" ) );

    Serial.print ( F ( "Temps : " ) );
    Serial.print ( day ( _Temps_Meteo ) );
    Serial.print ( F ( "-" ) );
    Serial.print ( month ( _Temps_Meteo ) );
    Serial.print ( F ( "-" ) );
    Serial.print ( year ( _Temps_Meteo ) );
    Serial.print ( F ( "  " ) );
    Serial.print ( hour ( _Temps_Meteo ) );
    Serial.print ( F ( ":" ) );
    Serial.println ( minute ( _Temps_Meteo ) );

    Serial.print ( F ( "Aujourd'hui - Temp. Min. : " ) );
    Serial.println ( _TempMin_Jour );
    Serial.print ( F ( "Aujourd'hui - Temp. Max. : " ) );
    Serial.println ( _TempMax_Jour );
    Serial.print ( F ( "Aujourd'hui - Prévisions Météo : " ) );
    Serial.println ( _Meteo_Du_Jour );
    Serial.print ( F ( "Aujourd'hui - Nuages : " ) );
    Serial.println ( _Nuage_Jour );
    Serial.print ( F ( "Aujourd'hui - Pluie : " ) );
    Serial.println ( _Pluie_Du_Jour );

    if ( ii == 2 || ii == 3 ) {
        Serial.print ( F ( "Tomorrow Temp Min : " ) );
        Serial.println ( _TempMin_Demain );
        Serial.print ( F ( "Tomorrow Temp Max : " ) );
        Serial.println ( _TempMax_Demain );
        Serial.print ( F ( "Tomorrow Weather : " ) );
        Serial.println ( _Meteo_Demain );
        Serial.print ( F ( "Tomorrow Cloud : " ) );
        Serial.println ( _Nuage_Demain );
        Serial.print ( F ( "Tomorrow Rain : " ) );
        Serial.println ( _Pluie_Demain );
    }
    if ( ii == 3 ) {
        Serial.print ( F ( "Day After Tomorrow Temp Min : " ) );
        Serial.println ( _TempMin_Apres_Demain );
        Serial.print ( F ( "Day After Tomorrow Temp Max : " ) );
        Serial.println ( _TempMax_Apres_Demain );
        Serial.print ( F ( "Day After Tomorrow Weather : " ) );
        Serial.println ( _Meteo_Apres_Demain );
        Serial.print ( F ( "Day After Tomorrow Cloud : " ) );
        Serial.println ( _Nuage_Apres_Demain );
        Serial.print ( F ( "Day After Tomorrow Rain : " ) );
        Serial.println ( _Pluie_Apres_Demain );
    }

    Serial.println ( F ( "---------------------------" ) );
}


void debug_Afficher_Donnees_Sur_TFT ( void ) {
    TFT.setTextSize ( 1 );
    TFT.setCursor ( 0, 0 );
    TFT.setTextColor ( WHITE ); //(white)
    TFT.fillScreen ( BLACK ); // efface ecran


    TFT.println ( F ( "--------------" ) );

    TFT.print ( F ( "Temperature Exterieure : " ) );
    TFT.println ( _Temp_Ext );

    TFT.print ( F ( "Tendance Temperature Exterieure : " ) );
    TFT.println ( _Temp_Ext_Tendance );

    TFT.print ( F ( "Humidite Exterieure " ) );
    TFT.println ( _Humidite_Ext );

    TFT.println ( F ( "" ) );

    //TFT.print ("Pluie de l\'heure : ");
    //TFT.println (_Pluie_Heure);

    //TFT.print ( F ( "Pluie du Jour : ") );
    //TFT.println ( _Pluie_Jour );

    TFT.println ( F ( "" ) );

    TFT.print ( F ( "Pression : " ) );
    TFT.println ( _Pression );

    TFT.print ( F ( "Pressure trend : " ) );
    TFT.println ( _Pression_Tendance );

    TFT.println ( F ( "" ) );

    TFT.print ( F ( "Temperature Salon : " ) );
    TFT.println ( _Temp_Int );

    TFT.print ( F ( "Tendance Temperature Salon : " ) );
    TFT.println ( _Temp_Int_Tendance );

    TFT.print ( F ( "Humidite Salon : " ) );
    TFT.println ( _Humidite_Int );

    TFT.print ( F ( "CO2 Salon : " ) );
    TFT.println ( _CO2_Int );

    TFT.println ( F ( "" ) );

    TFT.print ( F ( "Temperature Chambre : " ) );
    TFT.println ( _Temp_Chambre );

    TFT.print ( F ( "Tendance Temperature Chambre : " ) );
    TFT.println ( _Temp_Chambre_Tendance );

    TFT.print ( F ( "Humidité Chambre : " ) );
    TFT.println ( _Humidite_Chambre );

    TFT.print ( F ( "CO2 Chambre : " ) );
    TFT.println ( _CO2_Chambre );

    TFT.println ( F ( "--------------" ) );
}