#include <iostream>
#include <stdexcept>
#include <string>

#include "Bateau.h"

Bateau::Bateau() : type(UNDEFINED_TYPE), ligne(0), colonne(0), direction(UNDEFINED_DIR) {}

void Bateau::set_attributs(Type t, int ligne, int colonne, Direction dir) {
  // On test le type et la direction
  switch(t) {
    case PORTE_AVION:
      if(dir == HORIZONTAL && colonne > 5)
        throw std::out_of_range("Porte-avion mal placé: il ne rentre pas dans la grille");
      else if(dir == VERTICAL && ligne < 4)
        throw std::out_of_range("Porte-avion mal placé: il ne rentre pas dans la grille");
      else if(dir == UNDEFINED_DIR)
        throw std::invalid_argument("La direction du porte-avion doit être défini");
      else
        break;

    case CROISEUR:
      if(dir == HORIZONTAL && colonne > 6)
        throw std::out_of_range("Croiseur mal placé: il ne rentre pas dans la grille");
      else if(dir == VERTICAL && ligne < 3)
        throw std::out_of_range("Croiseur mal placé: il ne rentre pas dans la grille");
      else if(dir == UNDEFINED_DIR)
        throw std::invalid_argument("La direction du croiseur doit être défini");
      else
        break;

    case CONTRE_TORPILLEUR:
      if(dir == HORIZONTAL && colonne > 7)
        throw std::out_of_range("Contre-torpilleur mal placé: il ne rentre pas dans la grille");
      else if(dir == VERTICAL && ligne < 2)
        throw std::out_of_range("Contre-torpilleur mal placé: il ne rentre pas dans la grille");
      else if(dir == UNDEFINED_DIR)
        throw std::invalid_argument("La direction du contre-torpilleur doit être défini");
      else
        break;

    case SOUS_MARIN:
      if(dir == HORIZONTAL && colonne > 7)
        throw std::out_of_range("Sous-marin mal placé: il ne rentre pas dans la grille");
      else if(dir == VERTICAL && ligne < 2)
        throw std::out_of_range("Sous-marin mal placé: il ne rentre pas dans la grille");
      else if(dir == UNDEFINED_DIR)
        throw std::invalid_argument("La direction du sous-marin doit être défini");
      else
        break;

    case TORPILLEUR:
      if(dir == HORIZONTAL && colonne > 8)
        throw std::out_of_range("Torpilleur mal placé: il ne rentre pas dans la grille");
      else if(dir == VERTICAL && ligne < 1)
        throw std::out_of_range("Torpilleur mal placé: il ne rentre pas dans la grille");
      else if(dir == UNDEFINED_DIR)
        throw std::invalid_argument("La direction du torpilleur doit être défini");
      else
        break;

    case UNDEFINED_TYPE:
      throw std::domain_error("Type de bateau non défini (set_attribut)");

    default:
      throw std::domain_error("Type de bateau invalide (set_attribut)");
  }

  // On ne test pas la ligne et la colonne, ceci ce fera dans la grille
  // Une fois que tout est bon, on set les attributs

  this->type = t;
  this->ligne = ligne;
  this->colonne = colonne;
  this->direction = dir;

}

int Bateau::get_taille(){
  switch(this->type) {
    case PORTE_AVION:
      return 5;
    case CROISEUR:
      return 4;
    case CONTRE_TORPILLEUR:
      return 3;
    case SOUS_MARIN:
      return 3;
    case TORPILLEUR:
      return 2;
    case UNDEFINED_TYPE:
      throw std::domain_error("Type de bateau non défini (get_taille)");
    default:
      throw std::domain_error("Type de bateau invalide (get_taille)");
  }
  // Cette partie du code ne devrait pas être atteinte
  return 0;
}

int Bateau::get_ligne() { return this->ligne; }

int Bateau::get_colonne() { return this->colonne;}

Direction Bateau::get_direction() { return this->direction; }
