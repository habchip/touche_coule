#include <iostream>
#include <algorithm>
#include <ctime>

#include "Bombe_EM.h"
#include "User_input.h"


Bombe_EM::Bombe_EM() : em_actif(false) {}

ARME Bombe_EM::get_type() {
  return BOMBE_EM;
}

int Bombe_EM::get_nb_tir_par_tour() {
  return 3;
}

bool Bombe_EM::passe_ton_tour() {
  bool save = this->em_actif;

  if(this->em_actif) {
    std::cout << "La bombe EM fais passer le tour" << std::endl;
    this->em_actif = false;
  }

  return save;
}


std::string Bombe_EM::to_string() {
  return "BOMBE_EM";
}

std::string Bombe_EM::cree_msg(Grille grille) {
  std::string coods_atk = "";

  // On le met à la fin des coods
  if(std::rand() < (RAND_MAX/10) * 3){
    coods_atk = user_input_attaque(grille, false).substr(0,2) + "Y";
    this->em_actif = true;
  }
  else {
    coods_atk = user_input_attaque(grille, false).substr(0,2) + "N";
  }

  return coods_atk;
}


std::string Bombe_EM::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur() == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec une Bombe EM!");

  // On lit le message reçu : il indique si on passe notre tour ou non
  if(msg_recu[2] == 'Y')
    this->em_actif = true;

  // On attaque la grille et on fait l'accumulation de message pour tout lançer à la fin
  // Le format du message à envoyer est : POSITION  ATTAQUE  ex: A1ALO
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu.substr(0,2);
  Attaque atk = ma_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49);
  this->message += "Votre adversaire attaque avec une Bombe_EM en " + position + " : " + to_string_attaque(atk)  + "\n";

  return msg_recu.substr(0,2) + to_string_attaque(atk);
}


void Bombe_EM::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec une Bombe EM!");

  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu.substr(0,2);

  // On attaque la grille et on fait l'accumulation de message pour tout lançer à la fin
  // Le format du message reçu est : POSITION  ATTAQUE  ex: A1ALO
  this->message += "Votre attaque en " + position + " : " + msg_recu.substr(2)  + "\n";
  sa_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49, conv_to_attaque(msg_recu.substr(2)));
}


std::string Bombe_EM::affiche_attaque(std::string msg_recu) {
  std::string res = "";

  if (std::count(this->message.begin(), this->message.end(), '\n') == this->get_nb_tir_par_tour()) {
    res = this->message;
    this->message.clear();
  }

  return res;
}
