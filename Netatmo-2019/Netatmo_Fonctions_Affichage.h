// ***********************************************************************************
// Netatmo_Fonctions_Affichage.h
// ***********************************************************************************
#ifndef _NETATMO_FONCTIONS_AFFICHAGE_h
#define _NETATMO_FONCTIONS_AFFICHAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

#include "TimeLib.h"
#include "Netatmo_Defines.h"


void Initialisation_Affichage_LCD ( void );

void Centrer_Texte_dans_Zone ( String _texte, int Y, int X1, int X2, int COULEUR );
void Tracer_Ligne_Horizontale ( int posY, int COULEUR );
void Tracer_Ligne_Vertiale ( int posX, int COULEUR );
void Tracer_Ligne_Horiz_en_Pointille ( int X1, int X2, int Y, int COULEUR, int longueur, int espace );
void Tracer_Ligne_Vert_en_Pointille ( int X, int Y1, int Y2, int COULEUR, int longueur, int espace );

void Affiche_Statut_Internet ( int COULEUR );
void Affiche_Decompte_Actualisation ( void );

void Affichage_Heure ( void );
void Affichage_Date ( void );
void Texte_Bonjour ( void );

#endif /* _NETATMO_FONCTIONS_AFFICHAGE_h */