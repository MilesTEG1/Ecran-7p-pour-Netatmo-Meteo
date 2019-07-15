// ***********************************************************************************
// *****************  Netatmo - Afficheurs LCD - Connexion Internet  *****************
// ******
// ****** Fonctions Pour afficher les données sur l'écran
// ******
// ------ Date de création : 15 Avril 2019
// ------ Date de dernière révision : 09 juillet 2019
// ------ Auteur : MilesTEG
// ------
// ***********************************************************************************
// ***********************************************************************************

// Les include pour le bon déroulement de la compilation
#include "TimeLib.h"
#include <UTFT.h>
#include <UTFT_Geometry.h>
#include "Netatmo_Defines.h"
#include "Netatmo_Variables_Externes.h"
#include "Netatmo_Fonctions_Affichage.h"
#include "Netatmo_Fonctions_Autres.h"




void Initialisation_Affichage_LCD () {

    myGLCD.clrScr();

    // Trace de la grille d'affichage des valeurs
    // L'écran fait 800px (axe X) par 480 px (axe Y)
    // Mais X et Y commence à 0, donc X € [0;799] et Y € [0;479]
    myGLCD.setColor ( VGA_WHITE );
    myGLCD.setBackColor ( VGA_TRANSPARENT );
    myGLCD.drawRect ( 0, 0, 799, 479 );		// Rectangle extérieur
    myGLCD.drawLine ( 0, 26, 799, 26 );		// Délimitation de la 1ère zone supérieure dans laquelle on écrira le nom de la station et on placera les jauges de connexion wifi
    myGLCD.drawLine ( 0, 97, 799, 97 );		// Délimitation de la 2ème zone supérieure dans laquelle on écrira la date
    myGLCD.drawLine ( 0, 264, 597, 264 );		// Délimitation de la zone Temp. Ext (incluant Min / Max)
    myGLCD.drawLine ( 199, 97, 199, 344 );		// Délimitation de la zone Temp. Ext (incluant Min / Max)
    myGLCD.drawLine ( 398, 97, 398, 344 );		// Délimitation de la zone Temp. Salon (incluant Min / Max)
    myGLCD.drawLine ( 597, 97, 597, 479 );		// Délimitation de la zone Temp. Chambre (incluant Min / Max)
    myGLCD.fillRect ( 0, 345, 597, 347 );		// Séparation entre zone Humidité et Prévisions 3 jours
    myGLCD.drawLine ( 597, 203, 799, 203 );		// Délimitation de la zone Heure
    myGLCD.drawLine ( 597, 295, 799, 295 );		// Délimitation de la zone Pression
    myGLCD.drawLine ( 597, 387, 799, 387 );		// Délimitation de la zone CO2 Salon
    // DEBUG, on rempli les différentes zones avec la couleur PURPLE
    /*     myGLCD.setColor ( PURPLE );
        myGLCD.fillRect ( 1, 1, 798, 25 );	// Zone de titre
        myGLCD.fillRect ( 1, 27, 798, 96 );	// Zone de la Date
        myGLCD.fillRect ( 1, 98, 198, 263 );	// Zone de la Temp Ext (avec Min/Max)
        myGLCD.fillRect ( 200, 98, 397, 263 );	// Zone de la Temp Salon (avec Min/Max)
        myGLCD.fillRect ( 399, 98, 596, 263 );	// Zone de la Temp Chambre (avec Min/Max)
        myGLCD.fillRect ( 1, 265, 198, 344 );	// Zone de l'humidité Ext
        myGLCD.fillRect ( 200, 265, 397, 344 );	// Zone de l'humidité Salon
        myGLCD.fillRect ( 399, 265, 596, 344 );	// Zone de l'humidité Chambre
        myGLCD.fillRect ( 1, 348, 596, 367 );		// Délimitation de la zone des Prévision - Titre
        myGLCD.fillRect ( 1, 369, 198, 478 );		// Délimitation de la zone des prévisions du jour J
        myGLCD.fillRect ( 200, 369, 397, 478 );		// Délimitation de la zone des prévisions du jour J+1
        myGLCD.fillRect ( 399, 369, 596, 478 );		// Délimitation de la zone des prévisions du jour J+2
        myGLCD.fillRect ( 598, 98, 798, 202 );	// Zone de l'heure
        myGLCD.fillRect ( 598, 204, 798, 294 );	// Zone de la pression
        myGLCD.fillRect ( 598, 296, 798, 386 );	// Zone du CO2 Salon
        myGLCD.fillRect ( 598, 388, 798, 478 );	// Zone du CO2 Chambre */
    Tracer_Ligne_Horiz_en_Pointille ( 0, 597, 203, VGA_WHITE, 4, 6 );	// Délimitation des Temp. Max / Min
    Tracer_Ligne_Horiz_en_Pointille ( 0, 597, 368, VGA_WHITE, 4, 6 );	// Délimitation du titre Prévisions des prévisions
    Tracer_Ligne_Vert_en_Pointille ( 199, 368, 479, VGA_WHITE, 4, 6 );	// Délimitation prévisions J de J+1
    Tracer_Ligne_Vert_en_Pointille ( 398, 368, 479, VGA_WHITE, 4, 6 );	// Délimitation prévisions J+1 de J+2

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
    myGLCD.print ( F ( "Min=" ), 4, 218 );	// Temp. Ext. Min
    myGLCD.print ( F ( "Max=" ), 4, 243 );	// Temp. Ext. Max
    myGLCD.print ( F ( "Min=" ), 205, 218 );	// Temp. Salon Min
    myGLCD.print ( F ( "Max=" ), 205, 243 );	// Temp. Salon Max
    myGLCD.print ( F ( "Min=" ), 403, 218 );	// Temp. Chambre Min
    myGLCD.print ( F ( "Max=" ), 403, 243 );	// Temp. Chambre Min

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
    myGLCD.print ( F ( "Nuages:" ), 34, 445 );	// Jour J
    myGLCD.print ( F ( "Pluie:" ), 42, 460 );		// Jour J
    myGLCD.print ( F ( "Nuages:" ), 233, 445 );	// Jour J+1
    myGLCD.print ( F ( "Pluie:" ), 241, 460 );	// Jour J+1
    myGLCD.print ( F ( "Nuages:" ), 432, 445 );	// Jour J+2
    myGLCD.print ( F ( "Pluie:" ), 440, 460 );	// Jour J+2
}

void Centrer_Texte_dans_Zone ( String _texte, int Y, int X1, int X2, int COULEUR ) {
    // Fonction pour afficher du texte centré horizontalement dans une zone définie par X1 et X2
    // On va faire en sorte que X1 soit toujours < X2 pour faciliter l'algorythme
    int X;
    if ( X2 > X1 ) {
        X = X1 + ( X2 - X1 + 1 - _texte.length() * myGLCD.getFontXsize() ) / 2;
    }
    else {
        X = X2 + ( X1 - X2 - myGLCD.getFontXsize() ) / 2;
    }
    if ( X <= 0 ) {
        Serial.print ( F ( "-- Erreur dans le fonction Centrer_Texte_dans_Zone : la valeur calculée de X est négative ou nulle, elle vaut :" ) );
        Serial.println ( X );
        Serial.print ( F ( "Le texte qui génère cette erreur est : " ) );
        Serial.println ( _texte );
    }
    else {
        myGLCD.setColor ( COULEUR );
        myGLCD.print ( _texte, X, Y );
    }
}

void Tracer_Ligne_Horizontale ( int posY, int COULEUR ) {	// Tracer une ligne horizontale au niveau de la coordonnée posY
    myGLCD.setColor ( COULEUR );							// Ne pas oublier de refaire un .setColor() après...
    myGLCD.drawLine ( 0, posY, myGLCD.getDisplayXSize() - 1, posY );
}
void Tracer_Ligne_Vertiale ( int posX, int COULEUR ) {		// Tracer une ligne verticale au niveau de la coordonnée posX
    myGLCD.setColor ( COULEUR );							// Ne pas oublier de refaire un .setColor() après...
    myGLCD.drawLine ( posX, 0, posX, myGLCD.getDisplayYSize() - 1 );
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

        if ( position_curseur + longueur > X2 ) {	// La prochaine ligne dépassera la valeur de X2, on trace une ligne plus petite.
            Serial.println ( F ( "--DEBUG Ligne pointillée Horizontale" ) );
            Serial.println ( F ( "--La prochaine ligne dépassera la valeur de X2, on trace une ligne plus petite." ) );
            Serial.println ( F ( "-- " ) );
            myGLCD.drawLine ( position_curseur, Y, X2, Y );		// On trace une ligne jusqu'à X2
            break;
        }

        myGLCD.drawLine ( position_curseur, Y, position_curseur + longueur - 1, Y );		// On trace une ligne de jusqu'à position_curseur + longueur - 1          (-1 parce que sinon on a un px de trop)
        position_curseur += longueur + espace;		// On déplace le curseur de la valeur px tracés + des espace px à ne pas tracer pour se placer au début de la prochaine ligne à tracer
        if ( position_curseur > X2 ) {	// Le curseur est déjà au-dela de X2, on ne trace donc rien ici...
            Serial.println ( F ( "--DEBUG Ligne pointillée Horizontale" ) );
            Serial.println ( F ( "--Le curseur est déjà au-dela de X2, on ne trace donc rien ici..." ) );
            Serial.println ( F ( "-- " ) );
            break;
        }
    }
}

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

        if ( position_curseur + longueur > Y2 ) {	// La prochaine ligne dépassera la valeur de Y2, on trace une ligne plus petite.

            Serial.println ( F ( "--DEBUG Ligne pointillée Verticale" ) );
            Serial.println ( F ( "--La prochaine ligne dépassera la valeur de Y2, on trace une ligne plus petite." ) );
            Serial.println ( F ( "-- " ) );
            myGLCD.drawLine ( X, position_curseur, X, Y2 );		// On trace une ligne jusqu'à Y2
            break;
        }

        myGLCD.drawLine ( X, position_curseur, X, position_curseur + longueur - 1 );		// On trace une ligne de jusqu'à position_curseur + longueur - 1          (-1 parce que sinon on a un px de trop)
        position_curseur += longueur + espace;		/// On déplace le curseur de la valeur px tracés + des espace px à ne pas tracer pour se placer au début de la prochaine ligne à tracer
        if ( position_curseur > Y2 ) {	// Le curseur est déjà au-dela de Y2, on ne trace donc rien ici...

            Serial.println ( F ( "--DEBUG Ligne pointillée Verticale" ) );
            Serial.println ( F ( "--Le curseur est déjà au-dela de Y2, on ne trace donc rien ici..." ) );
            Serial.println ( F ( "-- " ) );
            break;
        }
    }
}

void Affiche_Statut_Internet ( int COULEUR ) {
    myGLCD.setColor ( COULEUR );
    myGLCD.setBackColor ( VGA_TRANSPARENT );
    myGLCD.fillRoundRect ( 693, 6, 793, 20 );		// Zone coloré indiquant la connexion internet OK ou KO
    myGLCD.setFont ( SmallFont );
    if ( COULEUR == GREEN ) {		// La connexion internet fonctionne, donc zone verte
        Centrer_Texte_dans_Zone ( F ( "WIFI OK" ), 7, 693, 793, DARKBLUE );
    }
    else if ( COULEUR == RED ) {
        Centrer_Texte_dans_Zone ( F ( "pas de WIFI" ), 7, 693, 793, VGA_YELLOW );
    }
}

void Affiche_Decompte_Actualisation ( ) {
    // De   0s à  50s : 1 barre de 14px								D
    // De  50s à 100s : 2 barres de 14px avec 1 espace de 4px		D D
    // De 100s à 150s : 3 barres de 14px avec 2 espaces de 4px		D D D
    // De 150s à 200s : 4 barres de 14px avec 3 espaces de 4px		D D D D
    // De 200s à 250s : 5 barres de 14px avec 4 espaces de 4px		D D D D D
    // De 250s à 300s : 6 barres de 14px avec 5 espaces de 4px		D D D D D D

    myGLCD.setColor ( VGA_GRAY );
    myGLCD.setBackColor ( VGA_TRANSPARENT );

    _Decompte = ( millis() - MILLIS_INTERNET ) / 50000; // Toutes les 50 s, _Decompte prends des valeurs de 0 à 6

	Serial.print ( F ( "--DEBUG - Valeur du décompte = " ) );
	Serial.println ( _Decompte );

    if ( _Decompte != _Decompte_Precedent ) {
        if ( _Decompte == 0 ) { // On réinitialise le compteur, avec une seule barre
            myGLCD.setColor ( VGA_BLACK );
            myGLCD.fillRoundRect ( 5, 6, 108, 20 );		// zone de 104px pour des 6 cases de 14px et Les 5 espaces de 4px
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