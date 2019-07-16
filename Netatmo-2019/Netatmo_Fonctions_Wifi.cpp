// ***********************************************************************************
// *****************  Netatmo - Afficheurs LCD - Connexion Internet  *****************
// ******
// ****** Fonctions de connexion au WIFI avec récupétation des données
// ****** avec les fonctions de décodage des données récupérées
// ******
// ------ Date de création : 15 Avril 2019
// ------ Date de dernière révision : 11 mai 2019
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


void WifiConnect_Netatmo ( void ) {
    Serial.println ( F ( "============ START WIFI Netatmo PROCEDURE ==============" ) );

    // Echo off
    Serial.println ( F ( "Echo off..." ) );		// Ici on désactive le retour dans le Serial des commandes AT envoyées à l'ESP
    Serial3.println ( "ATE0" );
    ReadSerial3 ();

    // on va se connecter à un réseau existant, donc on passe en mode station
    Serial.println ( F ( "Init to Wifi Client..." ) );
    Serial3.println ( "AT+CWMODE_CUR=1" );
    ReadSerial3 ();

    // on se connecte au réseau
    Serial.println ( F ( "Connects to WiFi network..." ) );
    Serial3.println ( "AT+CWJAP_DEF=\"" + _wifi_SSID + "\",\"" + _wifi_PASS + "\"" );
    if ( ReadSerial3 () == 1 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    //      Serial3.println("AT+CIPSTA_CUR?");

    // Mode "connexions unique"
    Serial.println ( F ( "Set to only one connection..." ) );
    Serial3.println ( "AT+CIPMUX=0" );
    if ( ReadSerial3 () == 1 ) { // On a un 'OK' de l'ESP
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    // on se connecte à notre serveur en TCP + keepalive = 1000
    Serial.println ( F ( "TCP connection to website..." ) );
    Serial3.println ( "AT+CIPSTART=\"TCP\",\"" + _hote_php + "\",80,1000" );

    if ( ReadSerial3 () == 1 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    // On contruit la requète GET puis on on l'envoie avec SEND pour récupérer les infos
    request  = "GET /netatmo2019.php HTTP/1.1\r\n";
    request += "Host:" + _hote_php + "\r\n";
    request += "User-Agent: Arduino\r\n";
    request += "Accept: text/html\r\n";
    request += "Connection: close\r\n";
    // on donne la taille de la requète qu'on va envoyer, en ajoutant 2 car
    // println ajouter 2 caractères à la fin "\r" et "\n"
    Serial3.println ( "AT+CIPSEND=" + String ( request.length() + 2 ) );
    delay ( 100 );
    Serial3.println ( request );

    ReadSerial3forData ();

    Serial.println ( _buffer_length );
    if ( _buffer_length > 700 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }
}
// ----------------------------------------

// ----------------------------------------
void WifiConnect_WeatherMap ( void ) {
    Serial.println ( F ( "============ START WIFI WeatherMap PROCEDURE ==============" ) );

    // Echo off
    Serial.println ( F ( "Echo off..." ) );
    Serial3.println ( "ATE0" );
    ReadSerial3 ();

    // on va se connecter à un réseau existant, donc on passe en mode station
    Serial.println ( F ( "Init to Wifi Client..." ) );
    Serial3.println ( "AT+CWMODE_CUR=1" );
    ReadSerial3 ();

    // on se connecte au réseau
    Serial.println ( F ( "Connects to WiFi network..." ) );
    Serial3.println ( "AT+CWJAP_DEF=\"" + _wifi_SSID + "\",\"" + _wifi_PASS + "\"" );
    if ( ReadSerial3 () == 1 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    //      Serial3.println("AT+CIPSTA_CUR?");

    // mode "connexions unique"
    Serial.println ( F ( "Set to only one connection..." ) );
    Serial3.println ( "AT+CIPMUX=0" );
    if ( ReadSerial3 () == 1 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    // on se connecte à notre serveur en TCP + keepalive = 1000
    Serial.println ( F ( "TCP connection to website..." ) );
    Serial3.println ( "AT+CIPSTART=\"TCP\",\"" + _hote_php + "\",80,1000" );

    if ( ReadSerial3 () == 1 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }

    // build GET request and SEND request info
    request  = "GET /openweathermap2019.php HTTP/1.1\r\n";
    request += "Host:" + _hote_php + "\r\n";
    request += "User-Agent: Arduino\r\n";
    request += "Accept: text/html\r\n";
    request += "Connection: close\r\n";
    // on donne la taille de la requète qu'on va envoyer, en ajoutant 2 car
    // println ajouter 2 caractères à la fin "\r" et "\n"
    Serial3.println ( "AT+CIPSEND=" + String ( request.length() + 2 ) );
    delay ( 100 );
    Serial3.println ( request );

    ReadSerial3forData ();

    Serial.println ( _buffer_length );
    if ( _buffer_length > 700 ) {
        Serial.println ( F ( "Connexion internet OK -> Green" ) );
        Affiche_Statut_Internet ( GREEN );
    }
    else {
        Serial.println ( F ( "Connexion internet KO -> Red" ) );
        Affiche_Statut_Internet ( RED );
    }
}
// ----------------------------------------

// ---------- Fonctions de décodage des données
void Decodage_Donnees_Tps_Reel ( void ) {
    String _buffer_Temp = "";	// Une variable buffer juste pour la fonction
    _cursor = 0; // Remise à zéro du curseur de déplacement dans le buffer

    // Example de ce qu'on va avoir
    // #EXT#14.6#up#77#SALON#35#20.8#stable#58#998.7#up#831#CHAMBRE#20.5#stable#54#848#
    // Le fichier "Sortie Serial du buffer" vous donnera une idée de ce qu'il y a dedans
    // Dans le buffer, les données sont mises dans l'ordre suivant :
    // MODULE EXTERIEUR
    //		->	Température / Tendance Température / Humidité
    // MODULE INTERIEUR PRINCIPAL - SALON
    //		->	Bruit / Température / Tendance Température / Humidité /
    //			Pression / Tendance Pression / CO2
    // MODULE INTERIEUR SECONDAIRE - CHAMBRE
    //		->	Température / Tendance Température / Humidité / CO2
    // Il faut avoir regardé le contenu du fichier PHP pour modifier l'ordre en fonction des modules à disposition

    _buffer_Temp = Lecture_Buffer();	// On enlève le début du buffer, lié à la réponse à la commande AT (Header)
    _buffer_Temp = Lecture_Buffer();	// On enlève le #EXT

    // Température extérieure
    _buffer_Temp = Lecture_Buffer();
    _Temp_Ext = _buffer_Temp.toFloat();		// Il faut utiliser xxx.print(float, 1) pour afficher le nombre avec une décimale
    _Temp_Ext_Text = String ( _Temp_Ext, 1 );
    _Temp_Ext_Text = _Temp_Ext_Text + "°C";

    // Tendance de température extérieure
    _buffer_Temp = Lecture_Buffer();
    _Temp_Ext_Tendance = _buffer_Temp;

    // Humidité extérieure
    _Humidite_Ext_Text = Lecture_Buffer();
    _Humidite_Ext = _Humidite_Ext_Text.toInt();
    _Humidite_Ext_Text = _Humidite_Ext_Text + "  %";

    // On enlève le #SALON
    _buffer_Temp = Lecture_Buffer();

    // Bruit dans le salon qu'on ne récupère pas
    _buffer_Temp = Lecture_Buffer(); // On enlève le bruit

    // Température intérieure
    _buffer_Temp = Lecture_Buffer();
    _Temp_Int = _buffer_Temp.toFloat();	// Il faut utiliser xxx.print(float, 1) pour afficher le nombre avec une décimale
    _Temp_Int_Text = String ( _Temp_Int, 1 );
    _Temp_Int_Text = _Temp_Int_Text + "°C";

    // Tendance de température intérieure
    _buffer_Temp = Lecture_Buffer();
    _Temp_Int_Tendance = _buffer_Temp;

    // Humidité intérieure
    _Humidite_Int_Text = Lecture_Buffer();
    _Humidite_Int = _Humidite_Int_Text.toInt();
    _Humidite_Int_Text = _Humidite_Int_Text + " %";

    // Pression
    _buffer_Temp = Lecture_Buffer();
    _Pression = ( int ) ( round ( _buffer_Temp.toFloat() ) );
    _Pression_Text = String ( _Pression );

    // Tendance de pression
    _buffer_Temp = Lecture_Buffer();
    _Pression_Tendance = _buffer_Temp;

    // CO2 dans le salon
    _CO2_Int_Text = Lecture_Buffer();
    _CO2_Int = _CO2_Int_Text.toInt();

    // On enlève le #CHAMBRE
    _buffer_Temp = Lecture_Buffer();

    // Température dans la chambre
    _buffer_Temp = Lecture_Buffer();
    _Temp_Chambre = _buffer_Temp.toFloat();
    _Temp_Chambre_Text = String ( _Temp_Chambre, 1 );
    _Temp_Chambre_Text = _Temp_Chambre_Text + "°C";

    // Tendance de température de la chambre
    _buffer_Temp = Lecture_Buffer();
    _Temp_Chambre_Tendance = _buffer_Temp;

    // Humidité Chambre
    _Humidite_Chambre_Text = Lecture_Buffer();
    _Humidite_Chambre = _Humidite_Chambre_Text.toInt();
    _Humidite_Chambre_Text = _Humidite_Chambre_Text + " %";

    // CO2 dans la chambre
    _CO2_Chambre_Text = Lecture_Buffer();
    _CO2_Chambre = _CO2_Chambre_Text.toInt();
}

void Decodage_Pression_Hist ( void ) {
    _cursor = 0;
    float val_press;
    Lecture_Buffer_Pourcent (); // On va au 1er %
    for ( int i = 0; i < 48; i++ ) {
        debug_buffer();
        val_press = Lecture_Buffer_Pourcent().toFloat();
        _HistoriquePressions[i] = ( int ) ( round ( val_press ) );

        // ----- DEBUG
        if ( i == 0 ) Serial.println ( F ( "--DEBUG--" ) );
        Serial.print ( "->" );
        Serial.print ( i );
        Serial.print ( "<-->" );
        Serial.print ( val_press, 1 );
        Serial.print ( "<-->" );
        Serial.println ( _HistoriquePressions[i] );
        if ( i == 47 ) Serial.println ( F ( "--FIN DEBUG--" ) );
        // ----- FIN DEBUG
    }
}

void Decodage_Temp_Hist ( void ) {
    _HistoriqueTemperatures [0][48] = -999;	// Valeurs d'initialisation pour les températures mini
    _HistoriqueTemperatures [1][48] = 999;	// Valeurs d'initialisation pour les températures maxi

    Lecture_Buffer_Pourcent ();	// On va sur le prochain %, mais sur la seconde ligne
    // /!\ Il ne faut donc pas réinitialiser le curseur à 0 !!!
    for ( int j = 0; j < 2; j++ ) { // j==0 -> Temp. MAX  || j==1 -> Temp. MIN
        for ( int i = 0; i < 48; i++ ) {	// 48 valeurs de températures
            debug_buffer();
            String valeur = Lecture_Buffer_Pourcent();
            _HistoriqueTemperatures[j][i] = valeur.toFloat();
            if ( ( j == 0 ) && ( valeur.toFloat() > _HistoriqueTemperatures[j][48] ) )
                _HistoriqueTemperatures[j][48] = valeur.toFloat();	// On stocke la valeur MAX dans la case de la 49ème valeur du tableau
            if ( ( j == 1 ) && ( valeur.toFloat() < _HistoriqueTemperatures[j][48] ) )
                _HistoriqueTemperatures[j][48] = valeur.toFloat(); // On stocke la valeur MIN dans la case de la 49ème valeur du tableau

            // ----- DEBUG
            debug_historique_temp_MaxMin ( i, j, valeur, _HistoriqueTemperatures[j][i] );
            // ----- FIN DEBUG
        }
        Lecture_Buffer_Pourcent (); // gotonext %
    }

    Serial.print ( F ( "Max Temp valeur =" ) );
    Serial.println ( _HistoriqueTemperatures[0][48] );
    Serial.print ( F ( "Min Temp valeur =" ) );
    Serial.println ( _HistoriqueTemperatures[1][48] );
}



void Decodage_Previsions_Meteo ( void ) {

    String _buffer_Temp = "";	// Un buffer de travail juste pour cette fonction
    _cursor = 0; // Remise à zéro du curseur de déplacement dans le buffer

    // ************ AUJOURD'HUI
    _buffer_Temp = Lecture_Buffer(); // On enlève le premier # et tout ce qui précède

    // Récupération de l'indication de temps (date) (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );
    // Températures du Jour (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _TempMin_Jour = _buffer_Temp.toInt();
    _TempMax_Jour = _buffer_Temp.toInt();
    // Météo du Jour (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Meteo_Du_Jour = _buffer_Temp.substring ( 0, 2 ).toInt();
    // Nuages du Jour (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Nuage_Jour = _buffer_Temp.toInt();
    // Pluie du Jour (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Pluie_Du_Jour = _buffer_Temp.toFloat();

    debug_Afficher_Meteo_Sur_Serial ( 1 );

    // Récupération des autres valeurs d'aujourd'hui
    // On gardera les plus mauvaises valeurs (histoire de ne pas donner de fausses espérances)
    int j = ( int ) ( ( 21 - hour ( _Temps_Meteo ) ) / 3 );
    for ( int i = 0; i < j; i++ ) {
        _buffer_Temp = Lecture_Buffer(); // Date de la prévision
        _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );

        _buffer_Temp = Lecture_Buffer(); // Températures
        int t = _buffer_Temp.toInt();
        if ( t < _TempMin_Jour ) _TempMin_Jour = t;
        if ( t > _TempMax_Jour ) _TempMax_Jour = t;

        _buffer_Temp = Lecture_Buffer(); // Météo
        int w = _buffer_Temp.substring ( 0, 2 ).toInt();
        if ( w > _Meteo_Du_Jour ) _Meteo_Du_Jour = w;

        _buffer_Temp = Lecture_Buffer(); // Nuages
        int c = _buffer_Temp.toInt();
        if ( c > _Nuage_Jour ) _Nuage_Jour = c;

        _buffer_Temp = Lecture_Buffer(); // Pluie
        float r = _buffer_Temp.toFloat();
        _Pluie_Du_Jour = _Pluie_Du_Jour + r;

        debug_Afficher_Meteo_Sur_Serial ( 1 );
    }

    // ************ DEMAIN
    // Récupération de l'indication de temps (date) (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );
    // Températures de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _TempMin_Demain = _buffer_Temp.toInt();
    _TempMax_Demain = _buffer_Temp.toInt();
    // Météo de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Meteo_Demain = _buffer_Temp.substring ( 0, 2 ).toInt();
    // Nuages de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Nuage_Demain = _buffer_Temp.toInt();
    // Pluie de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Pluie_Demain = _buffer_Temp.toFloat();

    debug_Afficher_Meteo_Sur_Serial ( 2 );

    // Récupération des autres valeurs de demain
    // On gardera les plus mauvaises valeurs (histoire de ne pas donner de fausses espérances)
    j = ( int ) ( ( 21 - hour ( _Temps_Meteo ) ) / 3 );
    for ( int i = 0; i < j; i++ ) {
        _buffer_Temp = Lecture_Buffer(); // timetag
        _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );

        _buffer_Temp = Lecture_Buffer(); //temp
        int t = _buffer_Temp.toInt();
        if ( t < _TempMin_Demain ) _TempMin_Demain = t;
        if ( t > _TempMax_Demain ) _TempMax_Demain = t;

        _buffer_Temp = Lecture_Buffer(); //weather
        int w = _buffer_Temp.substring ( 0, 2 ).toInt();
        if ( w > _Meteo_Demain ) _Meteo_Demain = w;

        _buffer_Temp = Lecture_Buffer(); //cloud
        int c = _buffer_Temp.toInt();
        if ( c > _Nuage_Demain ) _Nuage_Demain = c;

        _buffer_Temp = Lecture_Buffer(); //rain
        float r = _buffer_Temp.toFloat();
        _Pluie_Demain = _Pluie_Demain + r;

        debug_Afficher_Meteo_Sur_Serial ( 2 );
    }

    // ************ APRES=DEMAIN
    // Récupération de l'indication de temps (date) (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );
    // Températures de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _TempMin_Apres_Demain = _buffer_Temp.toInt();
    _TempMax_Apres_Demain = _buffer_Temp.toInt();
    // Météo de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Meteo_Apres_Demain = _buffer_Temp.substring ( 0, 2 ).toInt();
    // Nuages de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Nuage_Apres_Demain = _buffer_Temp.toInt();
    // Pluie de Demain (1ère valeur)
    _buffer_Temp = Lecture_Buffer();
    _Pluie_Apres_Demain = _buffer_Temp.toFloat();

    debug_Afficher_Meteo_Sur_Serial ( 3 );

    // Récupération des autres valeurs de demain
    // On gardera les plus mauvaises valeurs (histoire de ne pas donner de fausses espérances)
    j = ( int ) ( ( 21 - hour ( _Temps_Meteo ) ) / 3 );
    for ( int i = 0; i < j; i++ ) {
        _buffer_Temp = Lecture_Buffer(); // timetag
        _Temps_Meteo = Conversion_String_v_TimeT ( _buffer_Temp );

        _buffer_Temp = Lecture_Buffer(); //temp
        int t = _buffer_Temp.toInt();
        if ( t < _TempMin_Apres_Demain ) _TempMin_Apres_Demain = t;
        if ( t > _TempMax_Apres_Demain ) _TempMax_Apres_Demain = t;

        _buffer_Temp = Lecture_Buffer(); //weather
        int w = _buffer_Temp.substring ( 0, 2 ).toInt();
        if ( w > _Meteo_Apres_Demain ) _Meteo_Apres_Demain = w;

        _buffer_Temp = Lecture_Buffer(); //cloud
        int c = _buffer_Temp.toInt();
        if ( c > _Nuage_Apres_Demain ) _Nuage_Apres_Demain = c;

        _buffer_Temp = Lecture_Buffer(); //rain
        float r = _buffer_Temp.toFloat();
        _Pluie_Apres_Demain = _Pluie_Apres_Demain + r;

        debug_Afficher_Meteo_Sur_Serial ( 3 );
    }
}



String Lecture_Buffer_Pourcent ( void ) {
    /*
    Serial.print ("READBUFFER ROUTINE : ");
    Serial.print (_buffer.substring (_cursor, _cursor + 10));
    Serial.print(" : ");
    */
    String _buffer_local = "";
    while ( _cursor < _buffer.length() ) {
        debug_buffer();

        if ( _buffer[_cursor] == '%' ) {
            _cursor++;
            break;
        }
        _buffer_local += _buffer[_cursor];
        _cursor++;
    }
    //Serial.println (_buffer_local);
    return _buffer_local;
}

String Lecture_Buffer ( void ) {
    /*
    Serial.print ("READBUFFER ROUTINE : ");
    Serial.print (_buffer.substring (_cursor, _cursor + 10));
    Serial.print(" : ");
    */
    String _buffer_local = "";	// Un  autre buffer !

    while ( _cursor < _buffer.length() ) {
        debug_buffer();

        if ( _buffer[_cursor] == '#' ) {
            _cursor++;
            break;
        }
        _buffer_local += _buffer[_cursor];
        _cursor++;
    }

    //Serial.println (_buffer_local);
    return _buffer_local;
}

// ----------	Fin des fonctions de décodages des données Netatmo & Prévisions Météo


// ---------------------------------------
// -- Read GET request
// -- Impossible to parse for content at the same time because we miss characters
// -- Parsing is done when full buffer was received
// -- A 10 sec timeframe allowed to receive all data
// -- It just fills a buffer which is then decoded by _ProcessData
// --
void ReadSerial3forData ( void ) {
    unsigned long MILLIS = millis ();
    _buffer = "";
    _buffer_length = 0;

    while ( 1 ) {
        //timeout = 10sec
        if ( millis() - MILLIS > 10000 ) {
            Serial.println ( F ( "Timeout 10 secondes" ) );
            break;
        }

        // check for data and store it into buffer
        if ( Serial3.available () ) {
            c1 = Serial3.read();
            _buffer += c1;
            _buffer_length++;
        }
    }
}
// ---------------------------------------

// ---------------------------------------
// -- Simple Read Routine on ESP8266
// -- Used to check AT commands are properly processed
// -- It reads and wait for OK or FAIL or Timeout
// --
int ReadSerial3 ( void ) {
    unsigned long MILLIS = millis ();

    while ( 1 ) {
        if ( millis() - MILLIS > 10000 ) { //timeout=10sec
            Serial.println ( F ( "Timeout 10 secondes" ) );
            return -1;
        }

        delay ( 25 ); // necessary, otherwise it loops too fast and doesn't work
        c1 = Serial3.read();
        // Serial.print ("***"); // uncomment for debug
        // Serial.println (c1);

        if ( ( c1 == 'K' ) && ( c2 == 'O' ) ) { //OK
            Serial.println ( F ( "==OK==" ) );
            return 1;
        }
        else {
            c2 = c1;
        }

        if ( ( c1 == 'I' ) && ( c2 == 'L' ) ) { //FAIL
            Serial.println ( F ( "==FAIL==" ) );
            return -1;
        }
        else {
            c2 = c1;
        }
    }
}
// ---------------------------------------

// ---------------------------------------
void GetTimeFromBuffer ( void ) {
    int _buf_cursor = 0; // pointer used to parse the buffer
    int _monthInt;  // to store month as a INT
    int _dowInt;  // to store day of week as int
    int _DST = 0;   // daylightsavingtime

    if ( _Debug == true ) {
        Serial.print ( F ( "===== TIME STATUS : " ) );
        if ( timeStatus () == timeNotSet ) {
            Serial.println ( F ( "Time not set !!! =====" ) );
        }
        else if ( ( timeStatus () == timeSet ) ) {
            Serial.println ( F ( "Time is OK !!! =====" ) );
        }
    }

    // ======== search for 'DATE' within buffer
    while ( _buf_cursor + 4 < _buffer_length ) {
        debug_buffer();
        if ( _buffer.substring ( _buf_cursor, _buf_cursor + 4 ) == "Date" ) {
            Serial.println ( F ( "=====> Date found in buffer <=====" ) );
            break;
        }
        _buf_cursor++;
    }

    // ======== Store Dates values
    if ( _buf_cursor + 32 < _buffer_length ) { // check for complete data
        String _dow = _buffer.substring ( _buf_cursor + 6, _buf_cursor + 9 );
        String _day = _buffer.substring ( _buf_cursor + 11, _buf_cursor + 13 );
        String _month = _buffer.substring ( _buf_cursor + 14, _buf_cursor + 17 );
        String _year = _buffer.substring ( _buf_cursor + 18, _buf_cursor + 22 );
        String _hour = _buffer.substring ( _buf_cursor + 23, _buf_cursor + 25 );
        String _min = _buffer.substring ( _buf_cursor + 26, _buf_cursor + 28 );
        String _sec = _buffer.substring ( _buf_cursor + 29, _buf_cursor + 31 );

        /* 			// DEBUG
                    // displays strings variable to check for proper string matching - use for debug
                    Serial.println ( "=====> STRING TIME IS : " );
                    Serial.print ( "*" );
                    Serial.print ( _dow );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _day );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _month );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _year );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _hour );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _min );
                    Serial.println ( "*" );
                    Serial.print ( "*" );
                    Serial.print ( _sec );
                    Serial.println ( "*" );
        			// FIN DEBUG */

        if ( _dow == "Sun" ) _dowInt = 1;
        if ( _dow == "Mon" ) _dowInt = 2;
        if ( _dow == "Tue" ) _dowInt = 3;
        if ( _dow == "Wed" ) _dowInt = 4;
        if ( _dow == "Thu" ) _dowInt = 5;
        if ( _dow == "Fri" ) _dowInt = 6;
        if ( _dow == "Sat" ) _dowInt = 7;

        if ( _month == "Jan" ) _monthInt = 1;
        if ( _month == "Feb" ) _monthInt = 2;
        if ( _month == "Mar" ) _monthInt = 3;
        if ( _month == "Apr" ) _monthInt = 4;
        if ( _month == "May" ) _monthInt = 5;
        if ( _month == "Jun" ) _monthInt = 6;
        if ( _month == "Jul" ) _monthInt = 7;
        if ( _month == "Aug" ) _monthInt = 8;
        if ( _month == "Sep" ) _monthInt = 9;
        if ( _month == "Oct" ) _monthInt = 10;
        if ( _month == "Nov" ) _monthInt = 11;
        if ( _month == "Dec" ) _monthInt = 12;

        // manage DST
        // in France , last sunday of march (+1 hour) and last sunday of october (-1 hour)
        if ( _monthInt < 4 ) _DST = 1;                          // jan and feb and march -> winter
        if ( ( _monthInt ==  4 ) && ( _day.toInt() > 23 ) && ( ( _day.toInt() - _dowInt ) > 22 ) ) _DST = 2; // after last sun of march -> summer
        if ( _monthInt > 3 ) _DST = 2;                          // after march -> summer
        if ( ( _monthInt == 10 ) && ( _day.toInt() > 24 ) && ( ( _day.toInt() - _dowInt ) > 23 ) ) _DST = 1; // after last sun of october -> winter
        if ( _monthInt > 10 ) _DST = 1;                         // after oct -> winter


        if ( _DST == 1 ) heureEte = false;	// Heure d'hiver
        if ( _DST == 2 ) heureEte = true;	// Heure d'été


        /*             ///* used for debug DST calculation
                    Serial.println ( "------------ DST------------" );
                    Serial.println ( _buffer.substring ( _buf_cursor + 6, _buf_cursor + 31 ) );
                    Serial.println ( _monthInt );
                    Serial.println ( _day.toInt() );
                    Serial.println ( _dowInt );
                    Serial.println ( _DST );
                    Serial.println ( "------------EoDST-----------" );
                    // */

        //Serial.println ( _DST );


        setTime ( _hour.toInt(), _min.toInt(), _sec.toInt(), _day.toInt(), _monthInt, ( byte ) ( _year.toInt() ) );
        adjustTime ( _DST * 3600 ); // add 1 or 2 hour(s) according DST
        _CurrentTime = now();


        /* // DEBUG displays time stored and managed by arduino - use for debug
        Serial.println ( "=====> ARDUINO TIME IS : " );
        Serial.print ( "*" );
        Serial.print ( hour ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( minute ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( second ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( weekday ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( day ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( month ( _CurrentTime ) );
        Serial.println ( "*" );
        Serial.print ( "*" );
        Serial.print ( year ( _CurrentTime ) );
        Serial.println ( "*" );
        // FIN DEBUG */
    }
}
// ---------------------------------------