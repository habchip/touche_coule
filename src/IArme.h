#ifndef ARME_H
#define ARME_H

#include <string>
#include "Grille.h"

#define NB_CASE_RADAR 6

enum ARME {
  M4A1,
  SG_553,
  GATLING,
  AWP,
  LANCE_GRENADE,
  POSE_MINES,
  BOMBE_EM,
  RADAR,
  UNDEFINED_ARME
};

/*
 * Les attaques se déroulent de cette manière :
 *    - L'attaquant crée le msg de son attaque et l'envoie à l'attaqué
 *    - l'attaqué fait "attaque_ma_grille" et renvoie le résultat de l'attaque
 *    - enfin l'attaquant fait "attaque_sa_grille" à l'aide de ce résultat
 *    - Pour finir chacun affiche l'attaque 
 *      chaque message étant construit dans les deux fonctions précédentes
 */


/*
 * L'interface IArme doit être implémenter par chaque arme
 */

class IArme {
  public:
    // Renvoie le type de l'arme en cour
    virtual ARME get_type() = 0;
    // Renvoie le nombre de tir par tour de l'arme
    virtual int get_nb_tir_par_tour() = 0;
    // Renvoie si le joueur doit passer son tour ou non
    virtual bool passe_ton_tour() = 0;
    // La string associé à l'arme en cour
    virtual std::string to_string() = 0;
    // virtual ARME conv_to_type(std::string type) = 0;
    // Cree le msg qui sera envoyé à l'adversaire
    virtual std::string cree_msg(Grille grille) = 0;
    // Attaque la grille du joueur à partie de l'attaque de l'adversaire
    // Renvoie le resultat de l'attaque
    virtual std::string attaque_ma_grille(std::string msg_recu, Grille &ma_grille) = 0;
    // Attaque la grille de l'adversaire à partir de sa réponse
    virtual void attaque_sa_grille(std::string msg_recu, Grille &sa_grille) = 0;
    // Renvoie le msg qui sera affiché à l'utilisateur au tour par tour
    virtual std::string affiche_attaque(std::string msg_recu) = 0;
};


#endif
