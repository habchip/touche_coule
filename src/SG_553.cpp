#include <stdexcept>

#include "SG_553.h"
#include "User_input.h"

ARME SG553::get_type() {
  return SG_553;
}

int SG553::get_nb_tir_par_tour() {
  return 3;
}

bool SG553::passe_ton_tour() {
  return false;
}


std::string SG553::to_string() {
  return "SG_553";
}

std::string SG553::cree_msg(Grille grille) {
  return user_input_attaque(grille, false).substr(0,2);
}

std::string SG553::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur()  == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un SG 553!");

  // On attaque la grille et on réinitialise le message
  // Le format du message à envoyer est : POSITION  ATTAQUE  ex: A1ALO
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu;
  Attaque atk = ma_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49);

  this->message = "Votre adversaire attaque avec un SG 553 en " + position + " : " + to_string_attaque(atk)  + "\n";

  return msg_recu + to_string_attaque(atk);
}

void SG553::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un SG 553!");

  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu.substr(0,2);

  // On attaque la grille et on réinitialise le message
  // Le format du message reçu est : POSITION  ATTAQUE  ex: A1ALO
  this->message = "Votre attaque en " + position + " : " + msg_recu.substr(2)  + "\n";
  sa_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49, conv_to_attaque(msg_recu.substr(2)));
}

std::string SG553::affiche_attaque(std::string msg_recu) {
  std::string res = this->message;
  this->message.clear();

  return res;
}
