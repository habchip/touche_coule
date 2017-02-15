#include <ctime>

#include "TestBombe_EM.h"
#include "Bombe_EM.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestBombe_EM);

void TestBombe_EM::test_Bombe_EM() {
  Bombe_EM* arme = new Bombe_EM();
  CPPUNIT_ASSERT(arme != NULL);
}


void TestBombe_EM::test_get_type() {
  Bombe_EM* arme = new Bombe_EM();
  CPPUNIT_ASSERT(arme->get_type() == BOMBE_EM);
}


void TestBombe_EM::test_get_nb_tir_par_tour() {
  Bombe_EM* arme = new Bombe_EM();
  CPPUNIT_ASSERT(arme->get_nb_tir_par_tour() == 3);
}


void TestBombe_EM::test_passe_ton_tour() {
  Bombe_EM* arme = new Bombe_EM();
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);
}


void TestBombe_EM::test_to_string() {
  Bombe_EM* arme = new Bombe_EM();
  CPPUNIT_ASSERT(arme->to_string() == "BOMBE_EM");
}


void TestBombe_EM::test_cree_msg() {
  Bombe_EM* arme = new Bombe_EM();
  int nb_EM = 0;

  // On construit les grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

  std::srand(std::time(0));
  // Puis on test toutes les entrés possible
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On commence par construire l'entré standard
      char const_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string str_in(const_str);
      std::string str_out(const_str);

      // La dixième boucle est plus délicate
      if(j == 9)
        str_in = str_out.substr(0,1) + "10";
      else
        str_in = str_in.substr(0,2);

      // On charge cin
      in_buf = new std::stringbuf(str_in);
      std::cin.rdbuf(in_buf);

      // On commence par compter le nombre de fois que l'adversaire passe son tour
      std::string msg_creer = arme->cree_msg(*grille);
      if(msg_creer.substr(2) == "Y")
        nb_EM++;

      // Puis on vérifie la valeur de la sortie mais que pour les coordonnées
      CPPUNIT_ASSERT(msg_creer.substr(0,2) == str_out.substr(0,2));

      // Et on refait pareil pour l'autre grille
      in_buf = new std::stringbuf(str_in);
      std::cin.rdbuf(in_buf);
      CPPUNIT_ASSERT(arme->cree_msg(*grille2).substr(0,2) == str_out.substr(0,2));
    }
  }

  // Enfin on fait une analyse statistique sur le nombre de fois
  // où l'adversaire à dûe passer son tour
  std::cout << "nb_EM : " << nb_EM << std::endl;
  CPPUNIT_ASSERT(nb_EM > 20 && nb_EM < 40);
}


void TestBombe_EM::test_attaque_ma_grille() {
  Bombe_EM* arme = new Bombe_EM();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // Puis on test toutes les entrés possible
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On commence par construire le message reçu
      char const_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string str_in(const_str);

      // On check la valeur de sortie
      std::string etat_atk;
      if     (i == 0 && j == 0) etat_atk = "TOUCHE";
      else if(i == 0 && j == 1) etat_atk = "TOUCHE";
      else if(i == 0 && j == 2) etat_atk = "TOUCHE";
      else if(i == 0 && j == 3) etat_atk = "TOUCHE";
      else if(i == 0 && j == 4) etat_atk = "COULE";
      else if(i == 0 && j == 9) etat_atk = "TOUCHE";
      else if(i == 1 && j == 9) etat_atk = "COULE";
      else if(i == 3 && j == 5) etat_atk = "TOUCHE";
      else if(i == 4 && j == 5) etat_atk = "TOUCHE";
      else if(i == 5 && j == 5) etat_atk = "TOUCHE";
      else if(i == 6 && j == 5) etat_atk = "COULE";
      else if(i == 7 && j == 9) etat_atk = "TOUCHE";
      else if(i == 8 && j == 9) etat_atk = "TOUCHE";
      else if(i == 9 && j == 0) etat_atk = "TOUCHE";
      else if(i == 9 && j == 1) etat_atk = "TOUCHE";
      else if(i == 9 && j == 2) etat_atk = "COULE";
      else if(i == 9 && j == 9) etat_atk = "COULE";
      else etat_atk = "ALO";

      std::string res = str_in.substr(0,2) + etat_atk;
      CPPUNIT_ASSERT(arme->attaque_ma_grille(str_in.substr(0,2), *grille) == res);

      // Et on vérifie que la grille a bien été attaquée
      CPPUNIT_ASSERT(grille->a_ete_attaque(i,j));
    }
  }

  // Par acquis de conscience on vérifie que le nombre de bateau coulé
  // est bien égal à 5 !
  CPPUNIT_ASSERT(grille->get_nb_bateau_coule() == 5);

  // On test le cas où le mauvais joueur utilise cette méthode
  Grille* grille2 = new Grille(JOUEUR_2);
  try {arme->attaque_ma_grille("A1", *grille2);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 2 avec une Bombe EM!");
  }
}


void TestBombe_EM::test_attaque_sa_grille() {
  Bombe_EM* arme = new Bombe_EM();
  Bombe_EM* arme2 = new Bombe_EM();

  // On construit les deux grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

  // Puis on test toutes les entrés possible
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On commence par construire le message reçu
      char const_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string str_in(const_str);

      // Et on vérifie que la grille a bien été attaquée
      std::string res = arme->attaque_ma_grille(str_in.substr(0,2), *grille);
      arme2->attaque_sa_grille(res, *grille2);
      CPPUNIT_ASSERT(grille2->a_ete_attaque(i,j));
    }
  }

  // On test le cas où le mauvais joueur utilise cette méthode
  try {arme->attaque_sa_grille("A1", *grille);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 1 avec une Bombe EM!");
  }
}


void TestBombe_EM::test_affiche_attaque() {
  Bombe_EM* arme = new Bombe_EM();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  std::string res = arme->attaque_ma_grille("A1", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("H10", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("J4", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) != "");
}
