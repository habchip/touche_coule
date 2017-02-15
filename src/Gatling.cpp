#include <iostream>

#include "Gatling.h"
#include "User_input.h"


Gatling::Gatling() : a_tire(false) {}

ARME Gatling::get_type() {
  return GATLING;
}

int Gatling::get_nb_tir_par_tour() {
  return 1;
}

bool Gatling::passe_ton_tour() {
  bool save = this->a_tire;

  if(this->a_tire) {
    std::cout << "Recharge de la gatling" << std::endl;
    this->a_tire = false;;
  }

  return save;
}


std::string Gatling::to_string() {
  return "GATLING";
}

std::string Gatling::cree_msg(Grille grille) {
  std::string coods_atk = user_input_attaque(grille, true).substr(0,2);

  while(coods_atk[0] == 65 || coods_atk[0] == 74 ||
      coods_atk[1] == 49 || coods_atk[1] == 58) {
    std::cout << "On ne tire pas avec la Gatling sur les bord, c'est stupide ! Veuillez recommençer !" << std::endl;
    coods_atk = user_input_attaque(grille, true).substr(0,2);
  }

  return coods_atk;
}


std::string Gatling::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur()  == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec une Gatling!");

  this->a_tire = true;
  std::string res = "";

  // On attaque la grille et on attend un tour
  // Le format du message à envoyer est : msg1|msg2|...  ex: A1ALO|A2TOUCHE|...
  for(int i=-1; i<2; i++) {
    for(int j=-1; j<2; j++) {
      // On construit le message "position" qui sera affiché à l'ecran
      char const_position[2] = {static_cast<char> (static_cast<int>(msg_recu[0]) + i),
        static_cast<char> (static_cast<int>(msg_recu[1]) + j)};
      std::string position(const_position);

      if(const_position[1] == 58)
        position = position.substr(0,1) + "10";
      else
        position = position.substr(0,2);

      // Puis on attaque la grille que si la case n'a pas été attaquée
      if(!ma_grille.a_ete_attaque(msg_recu[0] - 65 + i, msg_recu[1] - 49 + j)) {
        Attaque atk = ma_grille.attaque(msg_recu[0] - 65 + i, msg_recu[1] - 49 + j);
        this->message += "Votre adversaire attaque avec la Gatling en " + position + " : " + to_string_attaque(atk)  + "\n";

        // Enfin on concatène les messages
        std::string position_2(const_position);
        res += position_2.substr(0,2) + to_string_attaque(atk) + "|";
      }
    }
  }

  return res;
}


void Gatling::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur()  == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec une Gatling!");

  this->a_tire = true;

  // On parse le message reçu
  std::string parser = msg_recu;
  int separateur = -1;

  while(parser[separateur + 1] != 0){
    int next_separateur = parser.find('|', separateur + 1);

    // On lit les deux informations présentes dans le message
    std::string position = parser.substr(separateur + 1, 2);
    std::string etat_attaque = parser.substr(separateur + 3, next_separateur - separateur - 3);

    // On construit le message "position" qui sera affiché à l'ecran
    if(position[1] == 58)
      position = position.substr(0,1) + "10";

    // Puis on attaque la grille
    this->message += "Votre attaque en " + position + " : " + etat_attaque  + "\n";
    sa_grille.attaque(parser[separateur + 1] - 65, parser[separateur + 2] - 49, conv_to_attaque(etat_attaque));
    separateur = next_separateur;
  }
}


std::string Gatling::affiche_attaque(std::string msg_recu) {
  std::string res = this->message;
  this->message.clear();

  return res;
}
