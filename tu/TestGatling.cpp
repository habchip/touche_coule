#include "TestGatling.h"
#include "Gatling.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestGatling);


void TestGatling::test_Gatling() {
  Gatling* arme = new Gatling();
  CPPUNIT_ASSERT(arme != NULL);
}


void TestGatling::test_get_type() {
  Gatling* arme = new Gatling();
  CPPUNIT_ASSERT(arme->get_type() == GATLING);
}


void TestGatling::test_get_nb_tir_par_tour() {
  Gatling* arme = new Gatling();
  CPPUNIT_ASSERT(arme->get_nb_tir_par_tour() == 1);
}


void TestGatling::test_passe_ton_tour() {
  // On construit une grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // La première attaque ne pose pas de poblème
  Gatling* arme = new Gatling();
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);

  // La deuxième attaque doit passer son tour
  arme->attaque_ma_grille("B5", *grille);
  CPPUNIT_ASSERT(arme->passe_ton_tour() == true);

  // Mais pas la troisième
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);
}


void TestGatling::test_to_string() {
  Gatling* arme = new Gatling();
  CPPUNIT_ASSERT(arme->to_string() == "GATLING");
}


void TestGatling::test_cree_msg() {
  Gatling* arme = new Gatling();

  // On construit les grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

  // Puis on test toutes les entrés possible
  for(int i=1; i<9; i++) {
    for(int j=1; j<9; j++) {
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


void TestGatling::test_attaque_ma_grille() {
  Gatling* arme = new Gatling();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // Puis on test toutes les entrés possible
  for(int i=1; i<9; i++) {
    for(int j=1; j<9; j++) {
      std::string res = "";
      char const_str_gatling[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string str_in_gatling(const_str_gatling);

      for(int i2=-1; i2<2; i2++){
        for(int j2=-1; j2<2; j2++){
          // On commence par construire le message reçu
          char const_str[2] = {static_cast<char> (i+i2+65), static_cast<char> (j+j2+49)};
          std::string str_in(const_str);

          // On check la valeur de sortie
          std::string etat_atk;
          if     (i+i2 == 0 && j+j2 == 0) etat_atk = "TOUCHE";
          else if(i+i2 == 0 && j+j2 == 1) etat_atk = "TOUCHE";
          else if(i+i2 == 0 && j+j2 == 2) etat_atk = "TOUCHE";
          else if(i+i2 == 0 && j+j2 == 3) etat_atk = "TOUCHE";
          else if(i+i2 == 0 && j+j2 == 4) etat_atk = "COULE";
          else if(i+i2 == 0 && j+j2 == 9) etat_atk = "TOUCHE";
          else if(i+i2 == 1 && j+j2 == 9) etat_atk = "COULE";
          else if(i+i2 == 3 && j+j2 == 5) etat_atk = "TOUCHE";
          else if(i+i2 == 4 && j+j2 == 5) etat_atk = "TOUCHE";
          else if(i+i2 == 5 && j+j2 == 5) etat_atk = "TOUCHE";
          else if(i+i2 == 6 && j+j2 == 5) etat_atk = "COULE";
          else if(i+i2 == 7 && j+j2 == 9) etat_atk = "TOUCHE";
          else if(i+i2 == 8 && j+j2 == 9) etat_atk = "TOUCHE";
          else if(i+i2 == 9 && j+j2 == 0) etat_atk = "TOUCHE";
          else if(i+i2 == 9 && j+j2 == 1) etat_atk = "TOUCHE";
          else if(i+i2 == 9 && j+j2 == 2) etat_atk = "COULE";
          else if(i+i2 == 9 && j+j2 == 9) etat_atk = "COULE";
          else etat_atk = "ALO";

          if(!grille->a_ete_attaque(i+i2, j+j2))
            res += str_in.substr(0,2) + etat_atk + "|";
        }
      }
      CPPUNIT_ASSERT(arme->attaque_ma_grille(str_in_gatling.substr(0,2), *grille) == res);

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
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 2 avec une Gatling!");
  }
}


void TestGatling::test_attaque_sa_grille() {
  Gatling* arme = new Gatling();
  Gatling* arme2 = new Gatling();

  // On construit les deux grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

  // Puis on test toutes les entrés possible
  for(int i=1; i<9; i++) {
    for(int j=1; j<9; j++) {
      // On commence par construire le message reçu
      char const_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string str_in(const_str);

      // Et on vérifie que la grille a bien été attaquée
      std::string res = arme->attaque_ma_grille(str_in.substr(0,2), *grille);
      arme2->attaque_sa_grille(res, *grille2);

      // Ceux sur chaque case frappée par la gatling
      for(int i2=-1; i2<2; i2++){
        for(int j2=-1; j2<2; j2++){
          CPPUNIT_ASSERT(grille2->a_ete_attaque(i+i2,j+j2));
        }
      }
    }
  }

  // On test le cas où le mauvais joueur utilise cette méthode
  try {arme->attaque_sa_grille("A1", *grille);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 1 avec une Gatling!");
  }
}


void TestGatling::test_affiche_attaque() {
  Gatling* arme = new Gatling();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  std::string res = arme->attaque_ma_grille("G4", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) != "");
}
