#ifndef CASE_H
#define CASE_H

#define NB_TOUR_MINE 3

class Case {
  public:
    Case();
    void set_bateau();
    void remove_bateau();
    bool contient_bateau();
    // Renvoie si la case a été attaquee
    bool est_touche();
    // Renvoie si l'attaque à touche un bateau
    bool attaque();
    // Renvoie si la case est juste vue et pas attaquée
    bool est_vue();
    // Met la case vue si elle n'a pas déjà été attaquée
    void regarde();
    // =-1 si il n'y a pas de mine
    // Sinon donne le nombre de tour restant pour fair exploser la mine
    int est_mine();
    // Pose une mine
    void set_mine();
    // Décrémente le compteur de mine
    void decremente_mine();

  private:
    bool bateau;
    bool touche;
    bool vue;
    int mine;
};

#endif
