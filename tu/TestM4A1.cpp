#include "TestM4A1.h"
#include "M4A1.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestM4a1);


void TestM4a1::test_get_type() {
  M4a1* arme = new M4a1();
  CPPUNIT_ASSERT(arme->get_type() == M4A1);
}


void TestM4a1::test_get_nb_tir_par_tour() {
  M4a1* arme = new M4a1();
  CPPUNIT_ASSERT(arme->get_nb_tir_par_tour() == 4);
}


void TestM4a1::test_passe_ton_tour() {
  M4a1* arme = new M4a1();
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);
}


void TestM4a1::test_to_string() {
  M4a1* arme = new M4a1();
  CPPUNIT_ASSERT(arme->to_string() == "M4A1");
}


void TestM4a1::test_cree_msg() {
  M4a1* arme = new M4a1();

  // On construit les grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

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

      // Puis on vérifie la valeur de la sortie
      CPPUNIT_ASSERT(arme->cree_msg(*grille) == str_out.substr(0,2));

      // Et on refait pareil pour l'autre grille
      in_buf = new std::stringbuf(str_in);
      std::cin.rdbuf(in_buf);
      CPPUNIT_ASSERT(arme->cree_msg(*grille2) == str_out.substr(0,2));
    }
  }
}


void TestM4a1::test_attaque_ma_grille() {
  M4a1* arme = new M4a1();

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
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 2 avec un M4A1!");
  }
}


void TestM4a1::test_attaque_sa_grille() {
  M4a1* arme = new M4a1();
  M4a1* arme2 = new M4a1();

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
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 1 avec un M4A1!");
  }
}


void TestM4a1::test_affiche_attaque() {
  M4a1* arme = new M4a1();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  std::string res = arme->attaque_ma_grille("A1", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("B7", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("H10", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("J4", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) != "");
}
