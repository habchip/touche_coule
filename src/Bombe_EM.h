#ifndef BOMBE_EM_H
#define BOMBE_EM_H

#include "IArme.h"

class Bombe_EM : public IArme {
  public:
    Bombe_EM();
    virtual ARME get_type();
    virtual int get_nb_tir_par_tour();
    virtual bool passe_ton_tour();
    virtual std::string to_string();
    // Cree le msg qui sera envoyé à l'adversaire
    virtual std::string cree_msg(Grille grille);
    // Attaque la grille du joueur à partie de l'attaque de l'adversaire
    // Renvoie le resultat de l'attaque
    virtual std::string attaque_ma_grille(std::string msg_recu, Grille &ma_grille);
    // Attaque la grille de l'adversaire à partir de sa réponse
    virtual void attaque_sa_grille(std::string msg_recu, Grille &sa_grille);
    // Renvoie le msg qui sera affiché à l'utilisateur au tour par tour
    virtual std::string affiche_attaque(std::string msg_recu);

  private:
    std::string message;
    bool em_actif;
};


#endif
