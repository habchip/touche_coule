#include <stdexcept>
#include <iostream>
#include <string>

#include "Grille.h"
#include "User_input.h"

using namespace std;

Grille::Grille(int joueur) : joueur(joueur), nb_bateau_coule(0) {
  bool err = false;

  if(joueur == JOUEUR_1){
    for(int i=0;i<5;i++){
      // On commence par demander la positionn de chaque bateau
      if(!err)
        this->affiche_grille(joueur);
      err = false;
      try{
#if TEST == 0
        if(i==0) user_input_bateau(PORTE_AVION, bateaux);
        if(i==1) user_input_bateau(CROISEUR, bateaux);
        if(i==2) user_input_bateau(CONTRE_TORPILLEUR, bateaux);
        if(i==3) user_input_bateau(SOUS_MARIN, bateaux);
        if(i==4) user_input_bateau(TORPILLEUR, bateaux);
#else
        if(i==0) bateaux[i].set_attributs(PORTE_AVION, 0, 0, HORIZONTAL);
        if(i==1) bateaux[i].set_attributs(CROISEUR, 1, 0, HORIZONTAL);
        if(i==2) bateaux[i].set_attributs(CONTRE_TORPILLEUR, 2, 0, HORIZONTAL);
        if(i==3) bateaux[i].set_attributs(SOUS_MARIN, 3, 0, HORIZONTAL);
        if(i==4) bateaux[i].set_attributs(TORPILLEUR, 4, 0, HORIZONTAL);
#endif

        // On positionne le bateau dans la grille
        for(int j=0;j<bateaux[i].get_taille(); j++){
          if(bateaux[i].get_direction() == VERTICAL){
            // On check le chevauchement
            if(cases[bateaux[i].get_ligne() - j][bateaux[i].get_colonne()].contient_bateau()){
              cout << "Attention vos bateaux ne peuvent pas se chevaucher, veuillez recommençer" << endl;
              err = true;
              for(int k=j-1; k>=0; k--)
                cases[bateaux[i].get_ligne() - k][bateaux[i].get_colonne()].remove_bateau();
              i--;
              break;
            }
            // Si tout est OK on place le bateau
            cases[bateaux[i].get_ligne() - j][bateaux[i].get_colonne()].set_bateau();

          } else if(bateaux[i].get_direction() == HORIZONTAL){
            // On check le chevauchement
            if(cases[bateaux[i].get_ligne()][bateaux[i].get_colonne() + j].contient_bateau()){
              cout << "Attention vos bateaux ne peuvent pas se chevaucher, veuillez recommençer" << endl;
              err = true;
              for(int k=j-1; k>=0; k--)
                cases[bateaux[i].get_ligne()][bateaux[i].get_colonne() + k].remove_bateau();
              i--;
              break;
            }
            // Si tout est OK on place le bateau
            cases[bateaux[i].get_ligne()][bateaux[i].get_colonne() + j].set_bateau();

          } else if(bateaux[i].get_direction() == UNDEFINED_DIR){
            throw std::invalid_argument("Lors de la creation de la grille, direction du bateau non défini");
          }
          else
            throw std::invalid_argument("Lors de la creation de la grille, direction du bateau invalide");
        }
      } catch(out_of_range const& e) {
        cerr << "Attention : " << e.what() << ", recommençez !" << endl;
        err = true;
        i--;
      } catch(exception const& e){
        throw;
      }
    }
    this->affiche_grille(joueur);
  }
}

/*
 * L'ordre d'importance pour l'affichage est :
 * mine -> touche -> vue -> grise
 */
void Grille::affiche_ligne(int ligne){
  for(int j=0; j<LARGEUR; j++){
    if(this->cases[ligne][j].contient_bateau() && this->joueur == joueur){
      if(this->cases[ligne][j].est_mine() > -1)
        // affiche en rouge
        cout << "| \033[31mM\033[0m ";
      else if(this->cases[ligne][j].est_touche())
        // affiche en rouge
        cout << "| \033[31mB\033[0m ";
      else if(this->cases[ligne][j].est_vue())
        // affiche en bleu
        cout << "| \033[34mB\033[0m ";
      else
        // affiche en vert
        cout << "| \033[32mB\033[0m ";

    } else if(this->cases[ligne][j].contient_bateau() && this->joueur != joueur){
      if(this->cases[ligne][j].est_mine() > -1)
        // affiche en rouge
        cout << "| \033[31mM\033[0m ";
      else if(this->cases[ligne][j].est_touche())
        // affiche en rouge
        cout << "| \033[31mX\033[0m ";
      else if(this->cases[ligne][j].est_vue())
        // affiche en bleu
        cout << "| \033[34mB\033[0m ";
      else
        cout << "|   ";

    } else {
      if(this->cases[ligne][j].est_mine() > -1)
        // affiche en rouge
        cout << "| \033[31mM\033[0m ";
      else if(this->cases[ligne][j].est_touche())
        cout << "| X ";
      else if(this->cases[ligne][j].est_vue())
        // affiche en bleu
        cout << "| \033[34mO\033[0m ";
      else
        cout << "|   ";
    }
  }
  cout << "|";
}


void Grille::affiche_grille(int joueur) {
  cout << endl;
  cout << "    1   2   3   4   5   6   7   8   9   10" << endl;
  for(int i=0; i<LONGEUR; i++){
    char lettre = 65 + i;
    cout << lettre << " ";
    this->affiche_ligne(i);
    cout << endl;
    cout << "  ***************************************** "<< endl;
  }
  cout << endl;
}

// Si la grille n'est pas celle du joueur elle n'affiche pas les bateaux
void Grille::affiche_grille(int joueur, Grille adversaire) {
  cout << endl;
  cout << "    1   2   3   4   5   6   7   8   9   10       |          1   2   3   4   5   6   7   8   9   10" << endl;
  for(int i=0; i<LONGEUR; i++){
    char lettre = 65 + i;
    cout << lettre << " ";
    this->affiche_ligne(i);
    cout << "      |      ";
    cout << lettre << " ";
    adversaire.affiche_ligne(i);
    cout << endl;
    cout << "  *****************************************      |        *****************************************" << endl;
  }
  cout << endl;
}

int Grille::get_joueur() { return this->joueur;  }


std::list<int> Grille::retrouve_bateau(int ligne, int colonne) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_2)
    throw std::domain_error("On ne recherche pas de bateau sur la grille du joueur 2 !");

  // On cherche si un bateau est bien sur la case indiqué
  // Pour cela on regarde la position de chaque case de chaque bateau
  // que l'on compare avec la position en argument

  std::list<int> res;

  int bateau_trouve = -1;
  for(int i=0; i<5; i++){
    for(int j=0; j<bateaux[i].get_taille(); j++){
      if(bateaux[i].get_direction() == VERTICAL){
        if(bateaux[i].get_ligne() - j == ligne && bateaux[i].get_colonne() == colonne){
          bateau_trouve = i;
          break;
        }
      } else if (bateaux[i].get_direction() == HORIZONTAL) {
        if(bateaux[i].get_ligne() == ligne && bateaux[i].get_colonne() + j == colonne){
          bateau_trouve = i;
          break;
        }
      } else
        throw std::invalid_argument("Grille::retrouve_bateau => Bateau non définit");
    }

    if(bateau_trouve != -1)
      break;
  }

  if(bateau_trouve == -1) {
    std::cout << "Erreur pour la ligne " << ligne << " et la colonne  " << colonne << std::endl;
    throw std::invalid_argument("Grille::retrouve_bateau => Pas de bateau trouvé");
  }

  for(int k=0; k<bateaux[bateau_trouve].get_taille(); k++){
    if(bateaux[bateau_trouve].get_direction() == VERTICAL){
      res.push_back(bateaux[bateau_trouve].get_ligne() - k);
      res.push_back(bateaux[bateau_trouve].get_colonne());
    } else {
      res.push_back(bateaux[bateau_trouve].get_ligne());
      res.push_back(bateaux[bateau_trouve].get_colonne() + k);
    }
  }
  return res;
}


int Grille::get_nb_bateau_coule() {
  return this->nb_bateau_coule;
}


Attaque Grille::attaque(int ligne, int colonne){ 
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_2)
    throw std::domain_error("On n'attaque pas de bateau sur la grille du joueur 2 !");

  // On mémorise si la case n'a pas déjà été attaquée
  // afin de ne pas couler plusieurs fois le même bateau
  bool deja_attaque = cases[ligne][colonne].est_touche();

  if(cases[ligne][colonne].attaque() == false)
    return ALO;

  // On retrouve le bateau qui s'est fait touché
  // et on regarde si il est coulé
  std::list<int> coods_bateau = retrouve_bateau(ligne, colonne);

  while (!coods_bateau.empty()) {
    // On dépile les coordonnée de chaque bateau
    int ligne_bateau = coods_bateau.front();
    coods_bateau.pop_front();
    int colonne_bateau = coods_bateau.front();
    coods_bateau.pop_front();

    // Si une seul case du bateau n'est pas touché, alors il n'est pas coulé
    if(cases[ligne_bateau][colonne_bateau].est_touche() == false)
      return TOUCHE;
  }

  if(!deja_attaque)
    this->nb_bateau_coule++;

  return COULE;
}


void Grille::attaque(int ligne, int colonne, Attaque res){
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_1)
    throw std::domain_error("On n'attaque pas de bateau sur la grille du joueur 1 !");

  // On mémorise si la case n'a pas déjà été attaquée
  // afin de ne pas couler plusieurs fois le même bateau
  bool deja_attaque = cases[ligne][colonne].est_touche();

  // Si le tir n'est pas à l'eau c'est qu'il y avait un bateau
  if(res != ALO)
    cases[ligne][colonne].set_bateau();
  cases[ligne][colonne].attaque();

  if(res == COULE && !deja_attaque)
    nb_bateau_coule++;
}


bool Grille::a_ete_attaque(int ligne, int colonne) { return this->cases[ligne][colonne].est_touche(); }


void Grille::espionne(int ligne, int colonne, bool res) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_1)
    throw std::domain_error("On n'espionne pas sur la grille du joueur 1 !");

  if(res)
    cases[ligne][colonne].set_bateau();
  this->cases[ligne][colonne].regarde();
}

bool Grille::espionne(int ligne, int colonne) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_2)
    throw std::domain_error("On n'espionne pas sur la grille du joueur 2 !");

  this->cases[ligne][colonne].regarde();
  return this->cases[ligne][colonne].contient_bateau();
}

bool Grille::a_ete_espionne(int ligne, int colonne) {
  return this->cases[ligne][colonne].est_touche() || this->cases[ligne][colonne].est_vue();
}

void Grille::set_mine(int ligne, int colonne) {this->cases[ligne][colonne].set_mine();}


void Grille::explose(int ligne, int colonne, Attaque * atks) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_2)
    throw std::domain_error("On n'explose pas de bateau sur la grille du joueur 2 !");

  /*
   * Dans l'ordre on met :
   * centre -> nord -> sud -> est -> ouest
   */
  if(!this->a_ete_attaque(ligne, colonne))
    atks[0] = this->attaque(ligne, colonne);
  else
    atks[0] = UNDEFINED_ATK;

  if(ligne > 0 && !this->a_ete_attaque(ligne - 1, colonne))
    atks[1] = this->attaque(ligne - 1, colonne);
  else 
    atks[1] = UNDEFINED_ATK;

  if(ligne < 9 && !this->a_ete_attaque(ligne + 1, colonne))
    atks[2] = this->attaque(ligne + 1, colonne);
  else 
    atks[2] = UNDEFINED_ATK;

  if(colonne < 9 && !this->a_ete_attaque(ligne, colonne + 1))
    atks[3] = this->attaque(ligne, colonne + 1);
  else 
    atks[3] = UNDEFINED_ATK;

  if(colonne > 0 && !this->a_ete_attaque(ligne, colonne - 1))
    atks[4] = this->attaque(ligne, colonne - 1);
  else 
    atks[4] = UNDEFINED_ATK;
}


void Grille::explose_adversaire(int ligne, int colonne, Attaque * res) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_1)
    throw std::domain_error("On n'explose pas de bateau sur la grille du joueur 1 !");

  /*
   * Dans l'ordre il y a :
   * centre -> nord -> sud -> est -> ouest
   */
  if(res[0] != UNDEFINED_ATK)
    this->attaque(ligne, colonne, res[0]);
  if(ligne > 0 && res[1] != UNDEFINED_ATK)
    this->attaque(ligne - 1, colonne, res[1]);
  if(ligne < 9 && res[2] != UNDEFINED_ATK)
    this->attaque(ligne + 1, colonne, res[2]);
  if(colonne < 9 && res[3] != UNDEFINED_ATK)
    this->attaque(ligne, colonne + 1, res[3]);
  if(colonne > 0 && res[4] != UNDEFINED_ATK)
    this->attaque(ligne, colonne - 1, res[4]);
}


std::string Grille::passe_un_tour() {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_2)
    throw std::domain_error("On ne passe pas de tour sur la grille du joueur 2 !");

  std::string res = "";
  for(int i=0; i<LONGEUR; i++) {
    for(int j=0; j<LARGEUR; j++) {
      cases[i][j].decremente_mine();
      if(cases[i][j].est_mine() == 0) {
        char const_position[2] = {static_cast<char>(i+65), static_cast<char>(j+49)};
        // Afin de différencier chaque mine on met un * au début de la string
        res += "*";
        // Si la mine doit exploser on retire la mine de la case et on fait tout exploser
        cases[i][j].decremente_mine();
        Attaque atks[5];
        this->explose(i, j, atks);
        // Puis on construit la string de retour
        for(int k = 0; k < 5; k++) {
          std::string position(const_position);
          if(k == 1) position[0] -= 1;
          if(k == 2) position[0] += 1;
          if(k == 3) position[1] += 1;
          if(k == 4) position[1] -= 1;
          res += position.substr(0,2) + to_string_attaque(atks[k]) + "|";
        }
      }
    }
  }
  return res;
}


void Grille::passe_un_tour(std::string res) {
  // On s'assure qu'on execute pas cette fonction dans la mauvaise grille
  if(this->joueur == JOUEUR_1)
    throw std::domain_error("On ne passe pas de tour sur la grille du joueur 1 !");

  // On commence par décrémenter le compteur de toute les mines
  for(int i=0; i<LONGEUR; i++) {
    for(int j=0; j<LARGEUR; j++) {
      cases[i][j].decremente_mine();
      if(cases[i][j].est_mine() == 0)
        cases[i][j].decremente_mine();
    }
  }
  // Puis on lit le message pour écrire les résultats dans la grille
  // Et ceux pour chaque mine (que l'on distingue par * posé en début de string)
  int debut_mine_string = res.find('*');
  while(debut_mine_string != -1) {
    int next_debut_mine_string = res.find('*', debut_mine_string + 1);
    std::string parser;
    if(next_debut_mine_string != -1)
      parser = res.substr(debut_mine_string, next_debut_mine_string - debut_mine_string);
    else
      parser = res.substr(debut_mine_string);
    int separateur = 0;
    while(parser[separateur + 1] != 0){
      int next_separateur = parser.find('|', separateur + 1);
      std::string etat_attaque = parser.substr(separateur + 3, next_separateur - separateur - 3);
      // Puis on attaque la grille
      this->attaque(parser[separateur + 1] - 65, parser[separateur + 2] - 49, conv_to_attaque(etat_attaque));
      separateur = next_separateur;
    }
    debut_mine_string = next_debut_mine_string;
  }
}


void Grille::affiche_explosion(std::string msg_explosion) {
  // On lit le message pour écrire les résultats dans la grille
  // Et ceux pour chaque mine (que l'on distingue par * posé en début de string)
  int debut_mine_string = msg_explosion.find('*');
  while(debut_mine_string != -1) {
    int next_debut_mine_string = msg_explosion.find('*', debut_mine_string + 1);
    std::string parser;
    if(next_debut_mine_string != -1)
      parser = msg_explosion.substr(debut_mine_string, next_debut_mine_string - debut_mine_string);
    else
      parser = msg_explosion.substr(debut_mine_string);
    int separateur = 0;
    std::string position = parser[2] == 58 ? parser.substr(1,1) + "10" : parser.substr(1,2);
    cout << "La mine posé en " + position + " explose :\n";
    while(parser[separateur + 1] != 0){
      int next_separateur = parser.find('|', separateur + 1);
      // On lit les deux informations présentes dans le message
      std::string position = parser[separateur  + 2] == 58 ? parser.substr(separateur + 1,1) + "10" : parser.substr(separateur + 1,2);
      std::string etat_attaque = parser.substr(separateur + 3, next_separateur - separateur - 3);
      // Puis on affiche l'attaque
      if(etat_attaque != "VOID")
        cout << "     - " + position + " : " + etat_attaque  + "\n";
      separateur = next_separateur;
    }
    debut_mine_string = next_debut_mine_string;
  }
}
