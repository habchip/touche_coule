#include <stdexcept>

#include "Awp.h"
#include "User_input.h"

ARME Awp::get_type() {
  return AWP;
}

int Awp::get_nb_tir_par_tour() {
  return 1;
}

bool Awp::passe_ton_tour() {
  return false;
}


std::string Awp::to_string() {
  return "AWP";
}

std::string Awp::cree_msg(Grille grille) {
  return user_input_attaque(grille, false).substr(0,2);
}

std::string Awp::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur()  == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un Awp!");

  // On attaque la grille et si l'attaque touche on coule le bateau
  // Le format du message à envoyer est : msg1|msg2|...  ex: A1TOUCHE|A2TOUCHE|...
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu;
  Attaque atk = ma_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49);
  this->message += "Votre adversaire attaque avec un AWP en " + position + " : " + to_string_attaque(atk)  + "\n";
  std::string res = msg_recu + to_string_attaque(atk);

  if(atk == TOUCHE) {
    std::list<int> coods_bateau = ma_grille.retrouve_bateau(msg_recu[0] - 65, msg_recu[1] - 49);
    res += "|";

    // Pour chaque case de bateau on regarde si il n'a jamais été attaqué
    // Dans ce cas on attaque la case pour coulé le bateau entierrement
    while(!coods_bateau.empty()) {
      int ligne_bateau = coods_bateau.front();
      coods_bateau.pop_front();
      int colonne_bateau = coods_bateau.front();
      coods_bateau.pop_front();

      // On construit le message "position" qui sera affiché à l'ecran
      char const_position[2] = {static_cast<char> (ligne_bateau + 65), static_cast<char> (colonne_bateau + 49)};
      std::string position2(const_position);
      std::string position_a_envoye(const_position);
      if(const_position[1] == 58)
        position2 = position2.substr(0,1) + "10";
      else
        position2 = position2.substr(0,2);

      if(!ma_grille.a_ete_attaque(ligne_bateau, colonne_bateau)) {
        Attaque atk = ma_grille.attaque(ligne_bateau, colonne_bateau);
        this->message += "Comme votre adversaire a touché avec un AWP, la case " + position2 +  " est touché\n";
        res += position_a_envoye.substr(0,2) + to_string_attaque(atk) + "|";
      }
    }
  }

  return res;
}


void Awp::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un Awp!");

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

    // Si il n'y a pas de séparateur c'est que l'attaque est à l'eau
    if(separateur == -1)
      break;
  }
}

std::string Awp::affiche_attaque(std::string msg_recu) {
  std::string res = this->message;
  this->message.clear();
  return res;
}
