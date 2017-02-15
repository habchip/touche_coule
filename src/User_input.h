#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <string>
#include "Bateau.h"
#include "Grille.h"
#include "IArme.h"

#define CHANGE_ARME 1
#define ATK_AVEC_ARME_ACTUELLE 2

// Demande au joueur si il veux heberge la partie ou non
int choix_hebergement();

// Demande au joueur si il veut changer d'arme ou attaquer :
//      1 = changer d'arme
//      2 = attaquer avec l'arme actuelle
int user_input_swap_arme(std::string arme_actuelle);

// Demande au joueur quelle arme il veut choisir
ARME choix_arme();

// Vérifie que les coordonnées sont bien sous la forme xy
// avec x une lettre entre A et J
// et y un nombre entre 1 et 10
std::string user_input_coods();

// Vérifie que le sens est bien v/h
char user_input_sens();

// Récupère le placement des bateaux à la création de la grille
void user_input_bateau(Type type, Bateau bateaux[5]);

// Récupère une attaque du joueur
std::string user_input_attaque(Grille grille, bool aoe);

// Récupère l'addresse ip sous le bon format
std::string user_input_addr_ip();

#endif
