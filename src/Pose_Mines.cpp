#include <stdexcept>
#include <algorithm>

#include "Pose_Mines.h"
#include "User_input.h"

ARME Pose_Mines::get_type() {
  return POSE_MINES;
}

int Pose_Mines::get_nb_tir_par_tour() {
  return 2;
}

bool Pose_Mines::passe_ton_tour() {
  return false;
}


std::string Pose_Mines::to_string() {
  return "POSE_MINES";
}

std::string Pose_Mines::cree_msg(Grille grille) {
  return user_input_attaque(grille, true).substr(0,2);
}

std::string Pose_Mines::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur() == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un Pose Mines!");

  int ligne = msg_recu[0] - 65;
  int colonne = msg_recu[1] - 49;

  ma_grille.set_mine(ligne, colonne);
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0, 1) + "10" : msg_recu.substr(0, 2);
  this->message += "Votre adversaire pose une mine en " + position + "\n";

  return msg_recu;
}

void Pose_Mines::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un Pose Mines!");

  int ligne = msg_recu[0] - 65;
  int colonne = msg_recu[1] - 49;

  sa_grille.set_mine(ligne, colonne);
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0, 1) + "10" : msg_recu.substr(0, 2);
  this->message += "Votre mine est posé en : " + position + "\n";
}

std::string Pose_Mines::affiche_attaque(std::string msg_recu) {
  std::string res = "";

  if (std::count(this->message.begin(), this->message.end(), '\n') == 2) {
    res = this->message;
    this->message.clear();
  }

  return res;
}
