// Fichier pour tester les fonctions d'affichage
#define VERSION "Netatmo Affichage sur écran 7p - V1 - 15/07/2019"

#include <UTFT.h>
#include <UTFT_Geometry.h>

// Déclaration des polices utilisées
extern uint8_t SmallFont[];     // 8x12 font
extern uint8_t BigFont[];   // 16x16 font
// extern uint8_t Grotesk16x32[];
extern uint8_t Grotesk32x64[];
extern uint8_t Grotesk24x48[];
// extern uint8_t Ubuntu[];         // 24x32 font
extern uint8_t hallfetica_normal[];     // 16x16 font
extern uint8_t arial_normal[];  // 16x16 font
// extern uint8_t arial_bold[];              // 16x16 font
// extern uint8_t arial_italic[];            // 16x16 font
// extern uint8_t franklingothic_normal[];   // 16x16 font
// extern uint8_t TinyFont[];                // 8x8 font

// ***********************************************************************************
// Netatmo_Defines.h
// ***********************************************************************************
// Assign human-readable names to some common 16-bit color values:
// Certaines couleurs sont déjà définies dans UTFT.h  avec pour certaines un nom pas tout à fait correct...
// #define BLACK       0x0000       // VGA_BLACK        dans UTFT.h
// #define WHITE       0xFFFF       // VGA_WHITE        dans UTFT.h
#define RED   0xF800// VGA_RED          dans UTFT.h
#define GREEN 0x07E0    // !! VGA_LIME      dans UTFT.h
// #define BLUE        0x001F       // VGA_BLUE         dans UTFT.h
// #define YELLOW      0xFFE0       // VGA_YELLOW       dans UTFT.h
// #define CYAN        0x07FF       // VGA_AQUA         dans UTFT.h
// #define MAGENTA     0xF81F       // !! VGA_FUCHSIA   dans UTFT.h
#define NAVY        0x000F
// #define DARKGREEN   0x0400        // VGA_GREEN    dans UTFT.h
#define DARKBLUE    0x0010
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINKK       0xF81F  // PINK est déjà définie dans une include système... et ce n'est pas une couleur

// Ce qui suit est définit dans le UTFT.h
// #define VGA_SILVER   0xC618
// #define VGA_GRAY     0x8410
// #define VGA_MAROON   0x8000
// #define VGA_OLIVE    0x8400
// #define VGA_TEAL     0x0410
// #define VGA_NAVY     0x0010
// #define VGA_PURPLE   0x8010
// #define VGA_TRANSPARENT  0xFFFFFFFF  // Ne fonctionne que pour .setBackColor()
// ***********************************************************************************

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// *-*-*-*  Les variables utilisées dans tous les modules
// *-*-*-*  (Internet - Affichage - Temps)
// Les données actuelles et précédentes sont utilisées pour raffraichir l'affichage seulement si nécessaire
// Les valeurs sont en Text lorsqu'elles sont récupérées du flux internet

// Définition des structures de données
typedef struct Exterieur Exterieur;
struct Exterieur {  // Structure qui regroupe toutes les variables de la station météo
    float  temp_num;
    float  temp_num_prec;   // La valeur précédente pour la comparaison
    int    humidite;
    int    humidite_prec;   // La valeur précédente pour la comparaison
    String temp_tendance;   // La variable text récupérée du flux Internet
    String temp_texte;      // La variable text récupérée du flux Internet
    String humidite_texte;  // La variable text récupérée du flux Internet
    Exterieur () :
                 temp_num ( -99.9 ),
                 temp_num_prec ( -99.9 ),
                 humidite ( 0 ),
                 humidite_prec ( 0 ),
                 temp_tendance ( "up" ),
                 temp_texte ( "" ),
                 humidite_texte ( "" ) {}
};

typedef struct Salon Salon;
struct Salon {  // Structure qui regroupe toutes les variables de la station météo
    float  temp_num;
    float  temp_num_prec;       // La valeur précédente pour la comparaison
    int    CO2;
    int    CO2_prec;            // La valeur précédente pour la comparaison
    int    pression;
    int    pression_prec;       // La valeur précédente pour la comparaison
    int    humidite;
    int    humidite_prec;       // La valeur précédente pour la comparaison
    String temp_tendance;
    String temp_texte;          // La variable text récupérée du flux Internet
    String CO2_texte;           // La variable text récupérée du flux Internet
    String pression_texte;      // La variable text récupérée du flux Internet
    String pression_tendance;   // La variable text récupérée du flux Internet
    String humidite_texte;      // La variable text récupérée du flux Internet
    Salon() :
            temp_num ( -99.9 ),
            temp_num_prec ( -99.9 ),
            CO2 ( 9999 ),
            CO2_prec ( 9999 ),
            pression ( 9999 ),
            pression_prec ( 9999 ),
            humidite ( 0 ),
            humidite_prec ( 0 ),
            temp_tendance ( "up" ),
            temp_texte ( "" ),
            CO2_texte ( "" ),
            pression_texte ( "" ),
            pression_tendance ( "up" ),
            humidite_texte ( "" ) {}
};

typedef struct Chambre Chambre;
struct Chambre {    // Structure qui regroupe toutes les variables de la station météo
    float  temp_num;
    float  temp_num_prec;   // La valeur précédente pour la comparaison
    int    CO2;
    int    CO2_prec;        // La valeur précédente pour la comparaison
    int    humidite;
    int    humidite_prec;   // La valeur précédente pour la comparaison
    String temp_tendance;
    String temp_texte;      // La variable text récupérée du flux Internet
    String CO2_texte;       // La variable text récupérée du flux Internet
    String humidite_texte;  // La variable text récupérée du flux Internet
    Chambre() :
              temp_num ( -99.9 ),
              temp_num_prec ( -99.9 ),
              CO2 ( 9999 ),
              CO2_prec ( 9999 ),
              humidite ( 0 ),
              humidite_prec ( 0 ),
              temp_tendance ( "up" ),
              temp_texte ( "" ),
              CO2_texte ( "" ),
              humidite_texte ( "" ) {}
};
typedef struct Station_Meteo Station_Meteo;

struct Station_Meteo {  // Structure qui regroupe toutes les variables de la station météo
    Exterieur exterieur;
    Salon     salon;
    Chambre   chambre;
};

// Station_Meteo _ma_Station = { { -99.9, -99.9, 0, 0, "up", "", "" }, { -99.9, -99.9, 9999, 9999, 9999, 9999, 0, 0, "up", "", "", "", "up", "" }, { -99.9, -99.9, 9999, 9999, 0, 0, "up", "", "", "up" } };
Station_Meteo _ma_Station;


unsigned long MILLIS_INTERNET = 99999999;
unsigned long MILLIS_TIME     = 99999999;
int _Decompte = -1;
int _Decompte_Precedent = -1;

// Déclaration de l'écran LCD
UTFT myGLCD ( SSD1963_800, 38, 39, 40, 41 );    // (byte model, int RS, int WR, int CS, int RST, int SER)
UTFT_Geometry geo_myGLCD ( &myGLCD );
int Ysize;  //   Pour stocker le nombre de pixel de l'écran sur les Y (hauteur)
int Xsize;  //   Pour stocker le nombre de pixel de l'écran sur les X (largeur)


// VARIABLES UTILES POUR LES ESSAIS, mais INUTILES POUR LE PROGRAMME FINAL --> NE PAS COPIER
const char *jour_semaine[] = {
    "\0",
    "Lundi\0",
    "Mardi\0",
    "Mercredi\0",
    "Jeudi\0",
    "Vendredi\0",
    "Samedi\0",
    "Dimanche\0"
};

const char *mois[] = {
    "\0",
    "Janvier\0",
    "Fevrier\0",
    "Mars\0",
    "Avril\0",
    "Mai\0",
    "Juin\0",
    "Juillet\0 ",
    "Aout\0",
    "Septembre\0",
    "Octobre\0",
    "Novembre\0",
    "Decembre\0"
};

// On défini artificiellement le temps  jeudi 4 Juillet 2019 (4ème jours de la semaine) - 13h45min12s
int Heures      = 13;
int Minutes     = 45;
int Secondes    = 12;
int Jour_mois   = 30;
int Mois        = 11;
int Annee       = 2019;
int jour_numero = 3;
bool heureEte   = true;     // Si true alors l'heure d'été est en place, sinon, c'est l'heure d'hiver



void setup ( void );
void loop ( void );
void Initialisation_Affichage_LCD ( void );

bool Centrer_dans_Zone_Verif ( String _texte, int Y, int X1, int X2, int &X );
void Centrer_Nombre_Int_dans_Zone ( int _nbr, int Y, int X1, int X2, int COULEUR );
void Centrer_Nombre_Float_dans_Zone ( float _nbr, int Y, int X1, int X2, int COULEUR );
void Centrer_Texte_dans_Zone ( String _texte, int Y, int X1, int X2, int COULEUR );



/*void Centrer_Texte_dans_Zone ( String _texte, int Y, int X1, int X2, int COULEUR );
  * void Centrer_Nombre_dans_Zone ( void *_nbr_ptr, int Y, int X1, int X2, int COULEUR, int _type = 0 );
  * void Centrer_Nombre_Int_dans_Zone ( int _nbr, int Y, int X1, int X2, int COULEUR );
  * void Centrer_Nombre_Float_dans_Zone ( float _nbr, int Y, int X1, int X2, int COULEUR );*/

void Tracer_Ligne_Horizontale ( int posY, int COULEUR );
void Tracer_Ligne_Vertiale ( int posX, int COULEUR );
void Tracer_Ligne_Horiz_en_Pointille ( int X1, int X2, int Y, int COULEUR, int longueur, int espace );
void Tracer_Ligne_Vert_en_Pointille ( int X, int Y1, int Y2, int COULEUR, int longueur, int espace );

void Affiche_Statut_Internet ( int COULEUR );
void Affiche_Decompte_Actualisation ( void );

void Affichage_Heure ( void );
void Affichage_Date ( void );
void Texte_Bonjour ( void );

void setup () {
    // === INITIALISATOIN ===

    Serial.begin ( 115200 );
    Serial3.begin ( 115200 );   // baudrate par défaut de l'ESP8266
    Serial.println ( VERSION );
    Serial.println ( F ( "===== DÉBUT DU SETUP =====" ) );

    // On s'occupe de l'écran LCD
    Serial.println ( F ( "Allumage de l'écran LCD..." ) );
    myGLCD.InitLCD ();
    pinMode ( 8, OUTPUT );  //  backlight
    digitalWrite ( 8, HIGH );   //    ON

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

    Serial.println ( F ( "===== FIN DU SETUP =====" ) );


    // Ce qui suit est là pour faire des tests sur ces fonctions, NE PAS RECOPIER
    Affiche_Statut_Internet ( GREEN );
    MILLIS_INTERNET = millis ();    // On considère qu'on a une connexion internet OK, et qu'on a récupéré les données.

    Serial.print ( F ( "-- MILLIS_INTERNET = " ) );
    Serial.print ( MILLIS_INTERNET );

    Affiche_Decompte_Actualisation ();
}   // setup

void loop () {
    // Pour les tests :

    // ------ TOUTES LES 5 MINUTES ------
    // ------ CONNECTION À INTERNET ET RÉCUPÉRATION DES DONNÉES NETATMO ------
    if ( millis () - MILLIS_INTERNET > 300000 ) {
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
}

void Initialisation_Affichage_LCD () {
    myGLCD.clrScr ();

    // Trace de la grille d'affichage des valeurs
    // L'écran fait 800px (axe X) par 480 px (axe Y)
    // Mais X et Y commence à 0, donc X € [0;799] et Y € [0;479]
    myGLCD.setColor ( VGA_WHITE );
    myGLCD.setBackColor ( VGA_TRANSPARENT );
    myGLCD.drawRect ( 0, 0, 799, 479 );     // Rectangle extérieur
    myGLCD.drawLine ( 0, 26, 799, 26 );     // Délimitation de la 1ère zone supérieure dans laquelle on écrira le nom de la station et on placera les jauges de connexion wifi
    myGLCD.drawLine ( 0, 97, 799, 97 );     // Délimitation de la 2ème zone supérieure dans laquelle on écrira la date
    myGLCD.drawLine ( 0, 264, 597, 264 );   // Délimitation de la zone Temp. Ext (incluant Min / Max)
    myGLCD.drawLine ( 199, 97, 199, 344 );  // Délimitation de la zone Temp. Ext (incluant Min / Max)
    myGLCD.drawLine ( 398, 97, 398, 344 );  // Délimitation de la zone Temp. Salon (incluant Min / Max)
    myGLCD.drawLine ( 597, 97, 597, 479 );  // Délimitation de la zone Temp. Chambre (incluant Min / Max)
    myGLCD.fillRect ( 0, 345, 597, 347 );   // Séparation entre zone Humidité et Prévisions 3 jours
    myGLCD.drawLine ( 597, 203, 799, 203 );     // Délimitation de la zone Heure
    myGLCD.drawLine ( 597, 295, 799, 295 );     // Délimitation de la zone Pression
    myGLCD.drawLine ( 597, 387, 799, 387 );     // Délimitation de la zone CO2 Salon
    // DEBUG, on rempli les différentes zones avec la couleur PURPLE
    myGLCD.setColor ( PURPLE );
/*    myGLCD.fillRect ( 1, 1, 798, 25 );  // Zone de titre
    myGLCD.fillRect ( 1, 27, 798, 96 );     // Zone de la Date
    myGLCD.fillRect ( 1, 98, 198, 263 );    // Zone de la Temp Ext (avec Min/Max)
    myGLCD.fillRect ( 200, 98, 397, 263 );  // Zone de la Temp Salon (avec Min/Max)
    myGLCD.fillRect ( 399, 98, 596, 263 );  // Zone de la Temp Chambre (avec Min/Max)
    myGLCD.fillRect ( 1, 265, 198, 344 );   // Zone de l'humidité Ext
    myGLCD.fillRect ( 200, 265, 397, 344 );     // Zone de l'humidité Salon
    myGLCD.fillRect ( 399, 265, 596, 344 );     // Zone de l'humidité Chambre
    myGLCD.fillRect ( 1, 348, 596, 367 );       // Délimitation de la zone des Prévision - Titre
    myGLCD.fillRect ( 1, 369, 198, 478 );       // Délimitation de la zone des prévisions du jour J
    myGLCD.fillRect ( 200, 369, 397, 478 );     // Délimitation de la zone des prévisions du jour J+1
    myGLCD.fillRect ( 399, 369, 596, 478 );     // Délimitation de la zone des prévisions du jour J+2
    myGLCD.fillRect ( 598, 98, 798, 202 );  // Zone de l'heure
    myGLCD.fillRect ( 598, 204, 798, 294 );     // Zone de la pression
    myGLCD.fillRect ( 598, 296, 798, 386 );     // Zone du CO2 Salon
    myGLCD.fillRect ( 598, 388, 798, 478 );     // Zone du CO2 Chambre
  */
    Tracer_Ligne_Horiz_en_Pointille ( 0, 597, 203, VGA_WHITE, 4, 6 );   // Délimitation des Temp. Max / Min
    Tracer_Ligne_Horiz_en_Pointille ( 0, 597, 368, VGA_WHITE, 4, 6 );   // Délimitation du titre Prévisions des prévisions
    Tracer_Ligne_Vert_en_Pointille ( 199, 368, 479, VGA_WHITE, 4, 6 );  // Délimitation prévisions J de J+1
    Tracer_Ligne_Vert_en_Pointille ( 398, 368, 479, VGA_WHITE, 4, 6 );  // Délimitation prévisions J+1 de J+2

    // Ecriture des en-têtes de données
    myGLCD.setFont ( BigFont );
    myGLCD.setColor ( VGA_BLUE );
    myGLCD.print ( F ( "Station Meteo Netatmo" ), CENTER, 5 );

    myGLCD.setColor ( VGA_WHITE );
    myGLCD.setFont ( BigFont );
    Centrer_Texte_dans_Zone ( F ( "Temp. Ext." ), 105, 1, 198, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Temp. Salon" ), 105, 200, 397, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Temp. Chbr." ), 105, 399, 596, VGA_WHITE );

    myGLCD.setFont ( arial_normal );
    myGLCD.print ( F ( "Min=" ), 4, 218 );      // Temp. Ext. Min
    myGLCD.print ( F ( "Max=" ), 4, 243 );      // Temp. Ext. Max
    myGLCD.print ( F ( "Min=" ), 205, 218 );    // Temp. Salon Min
    myGLCD.print ( F ( "Max=" ), 205, 243 );    // Temp. Salon Max
    myGLCD.print ( F ( "Min=" ), 403, 218 );    // Temp. Chambre Min
    myGLCD.print ( F ( "Max=" ), 403, 243 );    // Temp. Chambre Min

    myGLCD.setFont ( BigFont );
    Centrer_Texte_dans_Zone ( F ( "Humid. Ext." ), 269, 1, 198, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Humid. Salon" ), 269, 200, 397, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Humid. Chbr." ), 269, 399, 596, VGA_WHITE );

    Centrer_Texte_dans_Zone ( F ( "Heure" ), 105, 598, 798, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Pression" ), 210, 598, 798, VGA_WHITE );

    myGLCD.print ( F ( "CO2 Salon" ), 605, 301 );
    myGLCD.print ( F ( "CO2 Chbr." ), 605, 393 );
    myGLCD.setFont ( SmallFont );
    myGLCD.print ( F ( "(ppm)" ), 755, 305 );
    myGLCD.print ( F ( "(ppm)" ), 755, 397 );

    myGLCD.setFont ( hallfetica_normal );
    Centrer_Texte_dans_Zone ( F ( "Previsions sur 3 jours" ), 349, 1, 596, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Aujourd'hui" ), 370, 1, 198, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Demain" ), 370, 200, 397, VGA_WHITE );
    Centrer_Texte_dans_Zone ( F ( "Apres-demain" ), 370, 399, 596, VGA_WHITE );

    myGLCD.setColor ( VGA_SILVER );
    Centrer_Texte_dans_Zone ( F ( "Pluvieux" ), 390, 1, 198, VGA_SILVER );



    myGLCD.setColor ( VGA_WHITE );
    myGLCD.setFont ( SmallFont );
    myGLCD.print ( F ( "Nuages:" ), 34, 445 );  // Jour J
    myGLCD.print ( F ( "Pluie:" ), 42, 460 );   // Jour J
    myGLCD.print ( F ( "Nuages:" ), 233, 445 );     // Jour J+1
    myGLCD.print ( F ( "Pluie:" ), 241, 460 );  // Jour J+1
    myGLCD.print ( F ( "Nuages:" ), 432, 445 );     // Jour J+2
    myGLCD.print ( F ( "Pluie:" ), 440, 460 );  // Jour J+2
}   // Initialisation_Affichage_LCD

bool Centrer_dans_Zone_Verif ( String _texte, int Y, int X1, int X2, int &X ) {
    // Fonction pour afficher du texte centré horizontalement dans une zone définie par X1 et X2
    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    if ( X2 > X1 ) {
        X = X1 + ( X2 - X1 + 1 - _texte.length () * myGLCD.getFontXsize () ) / 2;
    }
    else {
        X = X2 + ( X1 - X2 - myGLCD.getFontXsize () ) / 2;
    }
    if ( X <= 0 ) {
        Serial.print ( F ( "-- Erreur dans le fonction Centrer_dans_Zone_Verif : la valeur calculée de X est négative ou nulle, elle vaut :" ) );
        Serial.println ( X );
        Serial.print ( F ( "Le texte qui génère cette erreur est : " ) );
        Serial.print ( _texte );
        return false;
    }
    return true;
}

void Centrer_Nombre_Int_dans_Zone ( int _nbr, int Y, int X1, int X2, int COULEUR ) {
    // Fonction pour afficher un nombre int centré horizontalement dans une zone définie par X1 et X2
    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    int X         = -1;
    String _texte = String ( _nbr, 1 );
    if ( Centrer_dans_Zone_Verif ( _texte, Y, X1, X2, X ) ) {
        myGLCD.setColor ( COULEUR );
        myGLCD.printNumI ( _nbr, X, Y );
    }
    else {
        Serial.println ( F ( "  -- envoyé depuis fonction Centrer_Nombre_Int_dans_Zone." ) );
    }
}

void Centrer_Nombre_Float_dans_Zone ( float _nbr, int Y, int X1, int X2, int COULEUR ) {
    // Fonction pour afficher un nombre float centré horizontalement dans une zone définie par X1 et X2
    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    int X         = -1;
    String _texte = String ( _nbr, 1 );
    if ( Centrer_dans_Zone_Verif ( _texte, Y, X1, X2, X ) ) {
        myGLCD.setColor ( COULEUR );
        myGLCD.printNumF ( _nbr, 1, X, Y, ',' );
    }
    else {
        Serial.println ( F ( "  -- envoyé depuis fonction Centrer_Nombre_Float_dans_Zone." ) );
    }
}

void Centrer_Texte_dans_Zone ( String _texte, int Y, int X1, int X2, int COULEUR ) {
    // Fonction pour afficher du texte centré horizontalement dans une zone définie par X1 et X2
    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    int X = -1;
    if ( Centrer_dans_Zone_Verif ( _texte, Y, X1, X2, X ) ) {
        myGLCD.setColor ( COULEUR );
        myGLCD.print ( _texte, X, Y );
    }
    else {
        Serial.println ( F ( "  -- envoyé depuis fonction Centrer_Texte_dans_Zone." ) );
    }
}


/*void Centrer_Nombre_Int_dans_Zone ( int _nbr, int Y, int X1, int X2, int COULEUR ) {
  *  // Fonction pour afficher du texte centré horizontalement dans une zone définie par X1 et X2
  *  // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
  *  int X;
  *  String _texte = String ( _nbr, 1 );
  *  if ( X2 > X1 ) {
  *      X = X1 + ( X2 - X1 + 1 - _texte.length() * myGLCD.getFontXsize() ) / 2;
  *  }
  *  else {
  *      X = X2 + ( X1 - X2 - myGLCD.getFontXsize() ) / 2;
  *  }
  *  if ( X <= 0 ) {
  *      Serial.print ( F ( "-- Erreur dans le fonction Centrer_Nombre_Int_dans_Zone : la valeur calculée de X est négative ou nulle, elle vaut :" ) );
  *      Serial.println ( X );
  *      Serial.print ( F ( "Le texte qui génère cette erreur est : " ) );
  *      Serial.println ( _texte );
  *  }
  *  else {
  *      myGLCD.setColor ( COULEUR );
  *      myGLCD.printNumI ( _nbr, X, Y );
  *  }
  * }*/

/*void Centrer_Nombre_Float_dans_Zone ( float _nbr, int Y, int X1, int X2, int COULEUR ) {
  *  // Fonction pour afficher du texte centré horizontalement dans une zone définie par X1 et X2
  *  // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
  *  int X;
  *  String _texte = String ( _nbr, 1 );
  *  if ( X2 > X1 ) {
  *      X = X1 + ( X2 - X1 + 1 - _texte.length() * myGLCD.getFontXsize() ) / 2;
  *  }
  *  else {
  *      X = X2 + ( X1 - X2 - myGLCD.getFontXsize() ) / 2;
  *  }
  *  if ( X <= 0 ) {
  *      Serial.print ( F ( "-- Erreur dans le fonction Centrer_Nombre_Int_dans_Zone : la valeur calculée de X est négative ou nulle, elle vaut :" ) );
  *      Serial.println ( X );
  *      Serial.print ( F ( "Le texte qui génère cette erreur est : " ) );
  *      Serial.println ( _texte );
  *  }
  *  else {
  *      myGLCD.setColor ( COULEUR );
  *      myGLCD.printNumF ( _nbr, 1, X, Y, ',' );
  *  }
  * }*/

void Tracer_Ligne_Horizontale ( int posY, int COULEUR ) {   // Tracer une ligne horizontale au niveau de la coordonnée posY
    myGLCD.setColor ( COULEUR );    // Ne pas oublier de refaire un .setColor() après...
    myGLCD.drawLine ( 0, posY, myGLCD.getDisplayXSize () - 1, posY );
}

void Tracer_Ligne_Vertiale ( int posX, int COULEUR ) {  // Tracer une ligne verticale au niveau de la coordonnée posX
    myGLCD.setColor ( COULEUR );    // Ne pas oublier de refaire un .setColor() après...
    myGLCD.drawLine ( posX, 0, posX, myGLCD.getDisplayYSize () - 1 );
}

void Tracer_Ligne_Horiz_en_Pointille ( int X1, int X2, int Y, int COULEUR, int longueur, int espace ) {
    // Fonction pour tracer une ligne horizontale en pointillés
    // "longueur" est la taille en pixel du trait tracé
    // "espace" est l'espace en pixel de l'espace entre deux traits tracés

    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    int variable_temp;
    if ( X2 < X1 ) {
        variable_temp = X1;
        X1 = X2;
        X2 = variable_temp;
    }
    int position_curseur = X1;

    myGLCD.setColor ( COULEUR );
    while ( position_curseur <= X2 ) {
        if ( position_curseur + longueur > X2 ) {       // La prochaine ligne dépassera la valeur de X2, on trace une ligne plus petite.
            Serial.println ( F ( "--DEBUG Ligne pointillée Horizontale" ) );
            Serial.println ( F ( "--La prochaine ligne dépassera la valeur de X2, on trace une ligne plus petite." ) );
            Serial.println ( F ( "-- " ) );
            myGLCD.drawLine ( position_curseur, Y, X2, Y );     // On trace une ligne jusqu'à X2
            break;
        }

        myGLCD.drawLine ( position_curseur, Y, position_curseur + longueur - 1, Y );        // On trace une ligne de jusqu'à position_curseur + longueur - 1          (-1 parce que sinon on a un px de trop)
        position_curseur += longueur + espace;      // On déplace le curseur de la valeur px tracés + des espace px à ne pas tracer pour se placer au début de la prochaine ligne à tracer
        if ( position_curseur > X2 ) {      // Le curseur est déjà au-dela de X2, on ne trace donc rien ici...
            Serial.println ( F ( "--DEBUG Ligne pointillée Horizontale" ) );
            Serial.println ( F ( "--Le curseur est déjà au-dela de X2, on ne trace donc rien ici..." ) );
            Serial.println ( F ( "-- " ) );
            break;
        }
    }
}   // Tracer_Ligne_Horiz_en_Pointille

void Tracer_Ligne_Vert_en_Pointille ( int X, int Y1, int Y2, int COULEUR, int longueur, int espace ) {
    // Fonction pour tracer une ligne verticale en pointillés
    // "longueur" est la taille en pixel du trait tracé
    // "espace" est l'espace en pixel de l'espace entre deux traits tracés

    // On va faire en sorte que Y2 soit toujours < Y2 pour faciliter l'algorythme
    int variable_temp;
    if ( Y2 < Y1 ) {
        variable_temp = Y1;
        Y1 = Y2;
        Y2 = variable_temp;
    }
    int position_curseur = Y1;

    myGLCD.setColor ( COULEUR );
    while ( position_curseur <= Y2 ) {
        if ( position_curseur + longueur > Y2 ) {       // La prochaine ligne dépassera la valeur de Y2, on trace une ligne plus petite.
            Serial.println ( F ( "--DEBUG Ligne pointillée Verticale" ) );
            Serial.println ( F ( "--La prochaine ligne dépassera la valeur de Y2, on trace une ligne plus petite." ) );
            Serial.println ( F ( "-- " ) );
            myGLCD.drawLine ( X, position_curseur, X, Y2 );     // On trace une ligne jusqu'à Y2
            break;
        }

        myGLCD.drawLine ( X, position_curseur, X, position_curseur + longueur - 1 );        // On trace une ligne de jusqu'à position_curseur + longueur - 1          (-1 parce que sinon on a un px de trop)
        position_curseur += longueur + espace;      /// On déplace le curseur de la valeur px tracés + des espace px à ne pas tracer pour se placer au début de la prochaine ligne à tracer
        if ( position_curseur > Y2 ) {      // Le curseur est déjà au-dela de Y2, on ne trace donc rien ici...
            Serial.println ( F ( "--DEBUG Ligne pointillée Verticale" ) );
            Serial.println ( F ( "--Le curseur est déjà au-dela de Y2, on ne trace donc rien ici..." ) );
            Serial.println ( F ( "-- " ) );
            break;
        }
    }
}   // Tracer_Ligne_Vert_en_Pointille

void Affiche_Statut_Internet ( int COULEUR ) {
    myGLCD.setColor ( COULEUR );
    myGLCD.setBackColor ( VGA_TRANSPARENT );
    myGLCD.fillRoundRect ( 693, 6, 793, 20 );   // Zone coloré indiquant la connexion internet OK ou KO
    myGLCD.setFont ( SmallFont );
    if ( COULEUR == GREEN ) {   // La connexion internet fonctionne, donc zone verte
        Centrer_Texte_dans_Zone ( F ( "WIFI OK" ), 7, 693, 793, DARKBLUE );
    }
    else if ( COULEUR == RED ) {
        Centrer_Texte_dans_Zone ( F ( "pas de WIFI" ), 7, 693, 793, VGA_YELLOW );
    }
}

void Affiche_Decompte_Actualisation () {
    // De   0s à  50s : 1 barre de 14px                             D
    // De  50s à 100s : 2 barres de 14px avec 1 espace de 4px       D D
    // De 100s à 150s : 3 barres de 14px avec 2 espaces de 4px      D D D
    // De 150s à 200s : 4 barres de 14px avec 3 espaces de 4px      D D D D
    // De 200s à 250s : 5 barres de 14px avec 4 espaces de 4px      D D D D D
    // De 250s à 300s : 6 barres de 14px avec 5 espaces de 4px      D D D D D D

    myGLCD.setColor ( VGA_GRAY );
    myGLCD.setBackColor ( VGA_TRANSPARENT );

    _Decompte = ( millis () - MILLIS_INTERNET ) / 50000;    // Toutes les 50 s, _Decompte prends des valeurs de 0 à 6

    Serial.print ( F ( "--DEBUG - Valeur du décompte = " ) );
    Serial.println ( _Decompte );

    if ( _Decompte != _Decompte_Precedent ) {
        if ( _Decompte == 0 ) {         // On réinitialise le compteur, avec une seule barre
            myGLCD.setColor ( VGA_BLACK );
            myGLCD.fillRoundRect ( 5, 6, 108, 20 );     // zone de 104px pour des 6 cases de 14px et Les 5 espaces de 4px
        }
        myGLCD.setColor ( VGA_GREEN );
        myGLCD.fillRoundRect ( _Decompte * 18 + 5, 6, _Decompte * 18 + 5 + 13, 20 );
        _Decompte_Precedent = _Decompte;
    }
}

void Affichage_Heure () {
    // Affichage de l'heure
    // à placer dans une fonction dédiée


    // -- Fin Affichage Heure
}

void Affichage_Date () {
    // Affichage de la date
    // à placer dans une fonction dédiée
    myGLCD.setFont ( Grotesk24x48 );
    myGLCD.setColor ( 255, 255, 255 );
}

void Texte_Bonjour () {
    myGLCD.setColor ( VGA_AQUA );
    myGLCD.setBackColor ( VGA_TRANSPARENT );

    myGLCD.setFont ( Grotesk32x64 );
    myGLCD.print ( F ( "BONJOUR" ), CENTER, 20 );
    myGLCD.setFont ( BigFont );
    myGLCD.print ( F ( "*** NETATMO AFFICHAGE DEPORTE ***" ), CENTER, 100 );
    myGLCD.print ( F ( "Debut : Mai 2019 / MAJ : Juillet 2019" ), CENTER, 120 );
}



