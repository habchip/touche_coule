#include <algorithm>
#include <stdexcept>

#include "M4A1.h"
#include "User_input.h"

ARME M4a1::get_type() {
  return M4A1;
}

int M4a1::get_nb_tir_par_tour() {
  return 4;
}

bool M4a1::passe_ton_tour() {
  return false;
}


std::string M4a1::to_string() {
  return "M4A1";
}

std::string M4a1::cree_msg(Grille grille) {
  return user_input_attaque(grille, false).substr(0,2);
}

std::string M4a1::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur() == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un M4A1!");

  // On attaque la grille et on fait l'accumulation de message pour tout lançer à la fin
  // Le format du message à envoyer est : POSITION  ATTAQUE  ex: A1ALO
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu;
  Attaque atk = ma_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49);

  this->message += "Votre adversaire attaque avec un M4A1 en " + position + " : " + to_string_attaque(atk)  + "\n";

  return msg_recu + to_string_attaque(atk);
}

void M4a1::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur()  == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un M4A1!");

  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu.substr(0,2);

  // On attaque la grille et on fait l'accumulation de message pour tout lançer à la fin
  // Le format du message reçu est : POSITION  ATTAQUE  ex: A1ALO
  this->message += "Votre attaque en " + position + " : " + msg_recu.substr(2)  + "\n";
  sa_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49, conv_to_attaque(msg_recu.substr(2)));
}

std::string M4a1::affiche_attaque(std::string msg_recu) {
  std::string res = "";

  // On n'affiche le message qu'une fois les 4 coups terminés
  // Et on clear la string d'accumulation des messages
  if (std::count(this->message.begin(), this->message.end(), '\n') == 4) {
    res = this->message;
    this->message.clear();
  }

  return res;
}
