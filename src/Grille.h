#ifndef GRILLE_H
#define GRILLE_H

#define LONGEUR   10
#define LARGEUR   10

#define JOUEUR_1 1
#define JOUEUR_2 2

#define TEST 0

#include <list>

#include "Case.h"
#include "Bateau.h"
#include "Attaque.h"


class Grille {
  public:
    // Le constructeur avec un seul argument demande la position
    // des bateaux diréctement à l'utilisateur
    Grille(int joueur);
    // Ici joueur est le joueur qui regarde la grille
    void affiche_grille(int joueur);
    void affiche_grille(int joueur, Grille adversaire);
    int get_joueur();
    // Renvoie la liste des cases du bateau sur une case donnée
    std::list<int> retrouve_bateau(int ligne, int colonne);
    // Renvoie le nombre de bateau coulé
    int get_nb_bateau_coule();
    // On utilise cette fonction lorsque l'adversaire attaque notre grille
    Attaque attaque(int ligne, int colonne);
    // On utilise cette fonction lorsqu'on attaque la grille de l'adversaire
    // Le resultat de l'attaque est celui rendu par l'adversaire
    void attaque(int ligne, int colonne, Attaque res);
    // Renvoie si une case a déjà été attaquée
    bool a_ete_attaque(int ligne, int colonne);
    // Met la case en mode vue et remplit la grille en fonction du resultat retourné par l'attaqué
    void  espionne(int ligne, int colonne, bool res);
    // Met la case en mode vue et indique si la case contient un bateau
    bool  espionne(int ligne, int colonne);
    // Indique si une case à été espionnée ou attaquée
    bool a_ete_espionne(int ligne, int colonne);
    // Pose une mine
    void set_mine(int ligne, int colonne);
    // Fait exploser la mine sur la grille du joueur
    void explose(int ligne, int colonne, Attaque * atks);
    // Fait exploser la mine sur la grille de l'adversaire
    void explose_adversaire(int ligne, int colonne, Attaque * res);
    // Décrémente tous les compteur de mine et fait exploser les mines qui doivent l'être
    // Renvoie le resultat sous forme de string
    // ex: B4ALO|B:TOUCHE|...
    std::string passe_un_tour();
    // Décrémente tous les compteur de mine 
    // et fait exploser les mines en fonction de la string donnée en paramétre
    // ex: B4ALO|B:TOUCHE|...
    void passe_un_tour(std::string res);
    // Affiche le message d'explosion génerer par les fonctions "passe_un_tour"
    void affiche_explosion(std::string msg_explosion);

  private:
    Case cases[LONGEUR][LARGEUR];
    int joueur;
    Bateau bateaux[5];
    void affiche_ligne(int ligne);
    int nb_bateau_coule;
};

#endif
