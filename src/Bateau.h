#ifndef BATEAU_H
#define BATEAU_H

enum Direction { HORIZONTAL, VERTICAL, UNDEFINED_DIR };
enum Type { PORTE_AVION, CROISEUR, CONTRE_TORPILLEUR, SOUS_MARIN, TORPILLEUR, UNDEFINED_TYPE };

class Bateau {
  public:
    Bateau();
    //Bateau(Type t, int ligne, int colonne, Direction dir);
    void set_attributs(Type t, int ligne, int colonne, Direction dir);
    int get_taille();
    int get_ligne();
    int get_colonne();
    Direction get_direction();

  private:
    Type type;
    int ligne;
    int colonne;
    Direction direction;
};


#endif
