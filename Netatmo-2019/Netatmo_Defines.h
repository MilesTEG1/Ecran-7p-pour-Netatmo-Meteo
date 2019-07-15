// ***********************************************************************************
// Netatmo_Defines.h
// ***********************************************************************************

#ifndef NETATMO_DEFINES_H_
#define NETATMO_DEFINES_H_

// Assign human-readable names to some common 16-bit color values:
// Certaines couleurs sont déjà définies dans UTFT.h  avec pour certaines un nom pas tout à fait correct...
// #define BLACK       0x0000		// VGA_BLACK 		dans UTFT.h
// #define WHITE       0xFFFF		// VGA_WHITE 		dans UTFT.h
#define RED         0xF800			// VGA_RED 			dans UTFT.h
#define GREEN       0x07E0			// !! VGA_LIME 		dans UTFT.h
// #define BLUE        0x001F		// VGA_BLUE 		dans UTFT.h
// #define YELLOW      0xFFE0		// VGA_YELLOW 		dans UTFT.h
// #define CYAN        0x07FF		// VGA_AQUA			dans UTFT.h
// #define MAGENTA     0xF81F		// !! VGA_FUCHSIA 	dans UTFT.h
#define NAVY        0x000F
//#define DARKGREEN   0x0400		// VGA_GREEN  	dans UTFT.h
#define DARKBLUE	0x0010
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINKK       0xF81F   // PINK est déjà définie dans une include système... et ce n'est pas une couleur

// Ce qui suit est définit dans le UTFT.h
// #define VGA_SILVER	0xC618
// #define VGA_GRAY		0x8410
// #define VGA_MAROON	0x8000
// #define VGA_OLIVE	0x8400
// #define VGA_TEAL		0x0410
// #define VGA_NAVY		0x0010
// #define VGA_PURPLE	0x8010
// #define VGA_TRANSPARENT	0xFFFFFFFF	// Ne fonctionne que pour .setBackColor()
// ***********************************************************************************

#endif /* NETATMO_DEFINES_H_ */
