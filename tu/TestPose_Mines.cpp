#include "TestPose_Mines.h"
#include "Pose_Mines.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestPose_Mines);


void TestPose_Mines::test_get_type() {
  Pose_Mines* arme = new Pose_Mines();
  CPPUNIT_ASSERT(arme->get_type() == POSE_MINES);
}


void TestPose_Mines::test_get_nb_tir_par_tour() {
  Pose_Mines* arme = new Pose_Mines();
  CPPUNIT_ASSERT(arme->get_nb_tir_par_tour() == 2);
}


void TestPose_Mines::test_passe_ton_tour() {
  Pose_Mines* arme = new Pose_Mines();
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);
}


void TestPose_Mines::test_to_string() {
  Pose_Mines* arme = new Pose_Mines();
  CPPUNIT_ASSERT(arme->to_string() == "POSE_MINES");
}


void TestPose_Mines::test_cree_msg() {
  Pose_Mines* arme = new Pose_Mines();

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


void TestPose_Mines::test_attaque_ma_grille() {
  Pose_Mines* arme = new Pose_Mines();

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

      std::string res = str_in.substr(0,2);
      CPPUNIT_ASSERT(arme->attaque_ma_grille(str_in.substr(0,2), *grille) == res);

      // Et on vérifie que la grille n'a pas été attaquée
      CPPUNIT_ASSERT(!grille->a_ete_attaque(i,j));
    }
  }

  // Par acquis de conscience on vérifie que le nombre de bateau coulé
  // est bien égal à 0 !
  CPPUNIT_ASSERT(grille->get_nb_bateau_coule() == 0);

  // On test le cas où le mauvais joueur utilise cette méthode
  Grille* grille2 = new Grille(JOUEUR_2);
  try {arme->attaque_ma_grille("A1", *grille2);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 2 avec un Pose Mines!");
  }
}


void TestPose_Mines::test_attaque_sa_grille() {
  Pose_Mines* arme = new Pose_Mines();
  Pose_Mines* arme2 = new Pose_Mines();

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

      // Et on vérifie que la grille n'a pas été attaquée
      std::string res = arme->attaque_ma_grille(str_in.substr(0,2), *grille);
      arme2->attaque_sa_grille(res, *grille2);
      CPPUNIT_ASSERT(!grille2->a_ete_attaque(i,j));
    }
  }

  // On test le cas où le mauvais joueur utilise cette méthode
  try {arme->attaque_sa_grille("A1", *grille);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 1 avec un Pose Mines!");
  }
}


void TestPose_Mines::test_affiche_attaque() {
  Pose_Mines* arme = new Pose_Mines();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  std::string res = arme->attaque_ma_grille("A1", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) == "");
  res = arme->attaque_ma_grille("J4", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) != "");
}
