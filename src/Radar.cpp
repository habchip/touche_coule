#include <stdexcept>
#include <ctime>

#include "Radar.h"
#include "User_input.h"

ARME Radar::get_type() {
  return RADAR;
}

int Radar::get_nb_tir_par_tour() {
  return 1;
}

bool Radar::passe_ton_tour() {
  return false;
}


std::string Radar::to_string() {
  return "RADAR";
}


std::string Radar::cree_msg(Grille grille) {
  std::string coods_atk = "";

  // Le format du message est le suivant : A1|B5|D:|...
  int nb_case_espionne = 0;
  int cases_espionne[16] = {0};
  bool a_deja_ete_vue = false;

  while(nb_case_espionne < NB_CASE_RADAR) {
    int ligne = std::rand() % 10;
    int colonne = std::rand() % 10;

    // On vérifie que les cases espionne ne l'ont pas déjà été faite lors de cet espionnage
    for(int i=0; i<nb_case_espionne; i++) {
      if(cases_espionne[i*2] == ligne && cases_espionne[i*2 + 1] == colonne)
        a_deja_ete_vue = true;
    }

    // Si la case a déjà été vue on recommence
    if(a_deja_ete_vue) {
      a_deja_ete_vue = false;

    } else {
      char conv[2] = {static_cast<char>(ligne + 65), static_cast<char>(colonne + 49)};
      std::string conv_str(conv);
      coods_atk += conv_str + "|";

      // On stock ces cases dans la liste pour l'itération suivante
      cases_espionne[nb_case_espionne * 2] = ligne;
      cases_espionne[nb_case_espionne * 2 + 1] = colonne;
      nb_case_espionne++;
    }
  }

  return coods_atk;
}


std::string Radar::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur() == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un Radar!");

  std::string res = "";
  this->message += "Votre adversaire vous espionne en : ";

  // Pour chaque case de la liste, on espionne et on envoie la réponse à l'adversaire
  // Le format du message est : coods Y/N ex: A1Y|B4N|G6Y|...
  // Avec Y qui indique qu'un bateau est sur la case et N le contraire
  for(int i=0; i<NB_CASE_RADAR; i++) {
    std::string position = msg_recu[i*3 + 1] == 58 ? msg_recu.substr(i*3, 1) + "10" : msg_recu.substr(i*3, 2);
    this->message += position + " ";
    bool res_espionnage = ma_grille.espionne(msg_recu[i*3] - 65, msg_recu[i*3 + 1] - 49);

    if(res_espionnage)
      res += msg_recu.substr(i*3, 2) + "Y|";
    else
      res += msg_recu.substr(i*3, 2) + "N|";
  }

  this->message += "\n";
  return res;
}


void Radar::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un Radar!");

  this->message += "Espionnage des cases : ";
  for(int i=0; i<NB_CASE_RADAR; i++) {
    int ligne = msg_recu[i*4 ] - 65;
    int colonne = msg_recu[i*4 + 1] - 49;
    bool res_espionnage = (msg_recu[i*4 + 2] == 'Y');

    std::string position = msg_recu[i*4 + 1] == 58 ? msg_recu.substr(i*4, 1) + "10" : msg_recu.substr(i*4, 2);
    this->message += position + " ";
    sa_grille.espionne(ligne, colonne, res_espionnage);
  }
  this->message += "\n";
}


std::string Radar::affiche_attaque(std::string msg_recu) {
  std::string res = this->message;
  this->message.clear();
  return res;
}
