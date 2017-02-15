#include "Case.h"

Case::Case() : bateau(false), touche(false), vue(false), mine(-1) {}

void Case::set_bateau(){
  this->bateau = true;
}

void Case::remove_bateau(){
  this->bateau = false;
}

bool Case::contient_bateau(){
  return this->bateau;
}

bool Case::est_touche(){
  return this->touche;
}

bool Case::attaque(){
  this->touche = true;
  this->vue = false;
  if(this->bateau)
    return true;
  return false;
}


bool Case::est_vue(){
  return this->vue;
}

void Case::regarde() {
  if(this->touche == false)
    this->vue = true;
}

int Case::est_mine() {return this->mine;}

void Case::set_mine() {this->mine = NB_TOUR_MINE;}

void Case::decremente_mine() {
  if(this->mine > -1)
    this->mine--;
}
