#include <iostream>
#include <stdexcept>
#include <cstring>
#include <stdio.h>
#include <fstream>

#include "User_input.h"

using namespace std;

int choix_hebergement() {
  string choix;
  int choix_int = 0;

  cout << "Que voulez-vous faire ?" << endl;
  cout << "    1: Héberger une partie" << endl;
  cout << "    2: Rejoindre une partie" << endl;
  cin >> choix;

  while(choix != "1" && choix != "2"){
    cout << "Erreur dans la saisie de votre choix, veuillez recommençer !" << endl;
    cin >> choix;
  }
  sscanf(choix.c_str(), "%d", &choix_int);
  return choix_int;
}



int user_input_swap_arme(std::string arme_actuelle) {
  string choix;
  int choix_int = 0;

  cout << "Que voulez-vous faire ?" << endl;
  cout << "    1: Changer d'arme" << endl;
  cout << "    2: Attaquer avec l'arme actuelle (" << arme_actuelle << ")" << endl;
  cin >> choix;

  while(choix != "1" && choix != "2"){
    cout << "Erreur dans la saisie de votre choix, veuillez recommençer !" << endl;
    cin >> choix;
  }
  sscanf(choix.c_str(), "%d", &choix_int);
  return choix_int;
}



ARME choix_arme() {
  cout << "Choisissez votre arme :" << endl;
  cout << "    1: M4A1" << endl;
  cout << "    2: SG 553" << endl;
  cout << "    3: Gatling" << endl;
  cout << "    4: AWP" << endl;
  cout << "    5: Lance grenade" << endl;
  cout << "    6: Pose mine" << endl;
  cout << "    7: Bombe EM" << endl;
  cout << "    8: Radar" << endl;

  string choix;
  int choix_int = 0;
  cin >> choix;
  while(choix != "1" && choix != "2" && choix != "3" && choix != "4" && 
        choix != "5" && choix != "6" && choix != "7" && choix != "8"){
    cout << "Erreur dans la saisie de votre choix, veuillez recommençer !" << endl;
    cin >> choix;
  }
  sscanf(choix.c_str(), "%d", &choix_int);

  switch(choix_int) {
    case 1:
      return M4A1;
    case 2:
      return SG_553;
    case 3:
      return GATLING;
    case 4:
      return AWP;
    case 5:
      return LANCE_GRENADE;
    case 6:
      return POSE_MINES;
    case 7:
      return BOMBE_EM;
    case 8:
      return RADAR;
    default:
      break;
  }

  return UNDEFINED_ARME;
}



string user_input_coods(){
  string input;
  cin >> input;
  input[0] = toupper(input[0]);
  while(input.size() != 2 ||
      (input[0] != 'A' && input[0] != 'B' && input[0] != 'C'
       && input[0] != 'D' && input[0] != 'E' && input[0] != 'F'
       && input[0] != 'G' && input[0] != 'H' && input[0] != 'I'
       && input[0] != 'J') ||
      (input[1] != '1' && input[1] != '2' && input[1] != '3'
       && input[1] != '4' && input[1] != '5' && input[1] != '6'
       && input[1] != '7' && input[1] != '8' && input[1] != '9'))
  {
    if(input.size() == 3 && 
        (input[0] == 'A' || input[0] == 'B' || input[0] == 'C'
         || input[0] == 'D' || input[0] == 'E' || input[0] == 'F'
         || input[0] == 'G' || input[0] == 'H' || input[0] == 'I'
         || input[0] == 'J') &&
        input[1] == '1' && input[2] == '0')
      break;
    cout << "Erreur dans la saisie de coordonnée, veuillez recommençer !" << endl;
    cin >> input;
  }
  return input;
}



char user_input_sens(){
  char input;
  cin >> input;
  input = tolower(input);
  while(input != 'v' && input != 'h') {
    cout << "Erreur dans la saisie de sens, veuillez recommençer ! "<< input << endl;
    cin >> input;
  }
  return input;
}


void user_input_bateau(Type type, Bateau bateaux[5]){
  string coordonnee, nom_bateau;
  char sens;
  int i = -1;

  switch(type){
    case PORTE_AVION:
      i = 0;
      nom_bateau = "porte-avion (5)";
      break;
    case CROISEUR:
      i = 1;
      nom_bateau = "croiseur (4)";
      break;
    case CONTRE_TORPILLEUR:
      i = 2;
      nom_bateau = "contre-torpilleur (3)";
      break;
    case SOUS_MARIN:
      i = 3;
      nom_bateau = "sous-marin (3)";
      break;
    case TORPILLEUR:
      i = 4;
      nom_bateau = "torpilleur (2)";
      break;
    case UNDEFINED_TYPE:
      throw std::invalid_argument("Lors du user_input, type de bateau indéfini");
    default:
      throw std::invalid_argument("Lors du user_input, type de bateau invalide");
  }

  cout << "Donnez la position de votre " << nom_bateau << ": " << endl;
  coordonnee = user_input_coods();
  cout << "Positionné horizontalement ou verticalement ? h/v" << endl;
  sens = user_input_sens();

  // Si on le place sur la dernière colonne, on "bricole" une solution
  if(coordonnee.size() == 3)
    coordonnee[1] = 58;

  if(sens == 'v')
    bateaux[i].set_attributs(type, coordonnee[0] - 65, coordonnee[1] - 49, VERTICAL);
  else
    bateaux[i].set_attributs(type, coordonnee[0] - 65, coordonnee[1] - 49, HORIZONTAL);
}


std::string user_input_attaque(Grille grille, bool aoe) {
  cout << "Quelle est votre prochaine attaque ?" << endl;
  string coordonnee = user_input_coods();
  // Si on le place sur la dernière colonne, on "bricole" une solution
  if(coordonnee.size() == 3) 
    coordonnee[1] = 58;

  while(grille.a_ete_attaque(coordonnee[0] - 65, coordonnee[1] - 49) && !aoe){
    cout << "Oups vous avez déjà attaqué cette case, veuillez recommençer !" << endl;
    coordonnee = user_input_coods();
  }

  return coordonnee;
}


bool IsIPAddress(string ipaddr) {
  char * token = strtok(&ipaddr[0], ".");
  for(int i=0; i<4; i++){
    if(token == NULL)
      return false;

    int j = 0;
    while(token[j] != 0x00){
      if(!isdigit(token[j]) || j > 2)
        return false;
      j++;
    }

    token = strtok(NULL, ".");
  }
  if(token != NULL)
    return false;
  return true;
}


string user_input_addr_ip() {
  // On commence par regarder si il existe le fichier ip.txt qui contient l'adresse ip
  ifstream stream("ip.txt", ifstream::in);
  if(stream.is_open()){
    char r_stream[17];
    stream.read(r_stream, 17);
    string read(r_stream);
    read.erase(read.find("\n"), read.size() - read.find("\n"));
    if(IsIPAddress(read)){
      cout << "adresse ip récupérée automatiquement" << endl;
      stream.close();
      return read;
    }
  }
  stream.close();

  // Si c'est pas le cas l'utilisateur le rentre lui-même
  string input;
  cout << "Entrez l'adresse ip de l'hôte : ";
  cin >> input;
  while(!IsIPAddress(input)){
    cout << "Votre adresse IP n'est pas valide, veuillez recommençer : ";
    cin >> input;
  }
  cout << endl;
  return input;
}
