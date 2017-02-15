#include <algorithm>
#include <stdexcept>

#include "Lance_Grenade.h"
#include "User_input.h"

ARME Lance_Grenade::get_type() {
  return LANCE_GRENADE;
}

int Lance_Grenade::get_nb_tir_par_tour() {
  return 2;
}

bool Lance_Grenade::passe_ton_tour() {
  return false;
}


std::string Lance_Grenade::to_string() {
  return "LANCE_GRENADE";
}

std::string Lance_Grenade::cree_msg(Grille grille) {
  return user_input_attaque(grille, true).substr(0,2);
}

std::string Lance_Grenade::attaque_ma_grille(std::string msg_recu, Grille &ma_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(ma_grille.get_joueur()  == JOUEUR_2)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 2 avec un Lance Grenade!");

  // On attaque la grille et si ça touche on fait exploser comme une mine
  // Le format du message à envoyer est : POSITION  ATTAQUE  ex: A1ALO
  std::string position = msg_recu[1] == 58 ? msg_recu.substr(0,1) + "10" : msg_recu;
  Attaque atk = ma_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49);

  // On fait la différence pour la première attaque avec une *
  this->message += "*Votre adversaire attaque avec un Lance Grenade en " + position + " : " + to_string_attaque(atk)  + "\n";
  std::string res = msg_recu + to_string_attaque(atk);

  if (atk == TOUCHE || atk == COULE) {
    res += "|";

    // Dans le cas où ça explose le format du msg est : A1TOUCHE|ALO|COULE|TOUCHE|...
    // Il est inutile de mettre la position de chaque attaque, mais uniquement le résultat
    Attaque atks[5];
    ma_grille.explose(msg_recu[0] - 65, msg_recu[1] - 49, atks);

    for(int i=1; i<5; i++) {
      if(atks[i] != UNDEFINED_ATK) {
        // Evidemment on reconstruit la position à chaque fois
        if(i == 1) position[0] -= 1;
        if(i == 2) position[0] += 1;
        if(i == 3) position[1] += 1;
        if(i == 4) position[1] -= 1;
        this->message += "L'explosion en " + position + " : " + to_string_attaque(atks[i])  + "\n";
      }
      res += to_string_attaque(atks[i]) + "|";
    }
  }

  return res;
}


void Lance_Grenade::attaque_sa_grille(std::string msg_recu, Grille &sa_grille) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(sa_grille.get_joueur() == JOUEUR_1)
    throw std::domain_error("On ne fait pas d'attaque sur la grille du joueur 1 avec un Lance Grenade!");

  // On commence par lire le premier message
  // On différencie les cas où ça touche ou non
  std::string parser = msg_recu;
  std::string position = parser.substr(0, 2);
  if(position[1] == 58)
    position = position.substr(0,1) + "10";
  int separateur = parser.find('|', 0);

  // Si ça n'a pas touché
  if(separateur == -1) {
    std::string etat_attaque = parser.substr(2, 3);
    this->message += "*Votre attaque en " + position + " : " + etat_attaque  + "\n";
    sa_grille.attaque(msg_recu[0] - 65, msg_recu[1] - 49, conv_to_attaque(etat_attaque));
  } else {

    // Si ça touche, on prend le premier message pour les coods
    // Puis on stock les resultats des attaques dans un tableau pour faire exploser.
    int ligne = static_cast<int> (msg_recu[0]) - 65;
    int colonne = static_cast<int> (msg_recu[1]) - 49;
    int i = 0;
    Attaque atks[5];
    separateur = 1;

    // On parse le message reçu
    while(parser[separateur + 1] != 0){
      int next_separateur = parser.find('|', separateur + 1);

      // On lit l'etat de chaque attaque
      std::string etat_attaque = parser.substr(separateur + 1, next_separateur - separateur - 1);

      // Puis on stock le tout dans atks
      atks[i] = conv_to_attaque(etat_attaque);

      // On vérifie qu'il n'y a pas de débordement
      if(etat_attaque != "VOID") {
        // Evidemment on reconstruit la position à chaque fois
        if(i == 1) position[0] -= 1;
        if(i == 2) position[0] += 1;
        if(i == 3) position[1] += 1;
        if(i == 4) position[1] -= 1;

        // On fait la différence pour la première attaque avec une *
        if(i == 0)
          this->message += "*Votre attaque en " + position + " : " + etat_attaque  + "\n";
        else
          this->message += "Votre attaque en " + position + " : " + etat_attaque  + "\n";
      }

      separateur = next_separateur;
      i++;
    }
    sa_grille.explose_adversaire(ligne, colonne, atks);
  }
}

std::string Lance_Grenade::affiche_attaque(std::string msg_recu) {
  std::string res = "";

  if (std::count(this->message.begin(), this->message.end(), '*') == 2) {
    res = this->message;
    this->message.clear();
  }

  return res;
}
