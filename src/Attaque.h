#ifndef ATTAQUE_H
#define ATTAQUE_H

#include <string>

enum Attaque { ALO, TOUCHE, COULE, UNDEFINED_ATK };

// Convertie une attaque en string
std::string to_string_attaque(Attaque a);

// Convertie une string en attaque
Attaque conv_to_attaque(std::string s);

#endif
