#include <algorithm>
#include <ctime>

#include "TestRadar.h"
#include "Radar.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestRadar);


void TestRadar::test_get_type() {
  Radar* arme = new Radar();
  CPPUNIT_ASSERT(arme->get_type() == RADAR);
}


void TestRadar::test_get_nb_tir_par_tour() {
  Radar* arme = new Radar();
  CPPUNIT_ASSERT(arme->get_nb_tir_par_tour() == 1);
}


void TestRadar::test_passe_ton_tour() {
  Radar* arme = new Radar();
  CPPUNIT_ASSERT(arme->passe_ton_tour() == false);
}


void TestRadar::test_to_string() {
  Radar* arme = new Radar();
  CPPUNIT_ASSERT(arme->to_string() == "RADAR");
}


void TestRadar::test_cree_msg() {
  Radar* arme = new Radar();

  // On construit les grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);

  // Puis on fait une dizaine de tirs
  std::srand(std::time(0));

  for(int i=0; i<10; i++) {
    // Puis on vérifie qu'il ai bien 6 cases espionnées
    std::string msg_arme = arme->cree_msg(*grille);
    CPPUNIT_ASSERT(std::count(msg_arme.begin(), msg_arme.end(), '|') == 6);

    // Et on refait pareil pour l'autre grille
    std::string msg_arme2 = arme->cree_msg(*grille2);
    CPPUNIT_ASSERT(std::count(msg_arme2.begin(), msg_arme2.end(), '|') == 6);
  }
}


void TestRadar::test_attaque_ma_grille() {
  Radar* arme = new Radar();

  // On construit la grille
//  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
//  std::cin.rdbuf(in_buf);
//  Grille* grille = new Grille(JOUEUR_1);
//
//  // On test une dizaine de tirs
//  for(int i=0; i<10; i++) {
//    // Et on vérifie que la grille a bien été espionné
//    // TODO: En fonction de chaque message, vérifier que la grille est bien espionné
//    //CPPUNIT_ASSERT(grille->a_ete_attaque(i,j));
//  }

  // On test le cas où le mauvais joueur utilise cette méthode
  Grille* grille2 = new Grille(JOUEUR_2);
  try {arme->attaque_ma_grille("A1", *grille2);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 2 avec un Radar!");
  }
}


void TestRadar::test_attaque_sa_grille() {
  Radar* arme = new Radar();
  // Radar* arme2 = new Radar();

  // On construit les deux grilles
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  // Grille* grille2 = new Grille(JOUEUR_2);

  // Puis on test toutes les entrés possible
  for(int i=0; i<10; i++) {
    // Et on vérifie que la grille a bien été espionné
    // TODO: En fonction de chaque message, vérifier que la grille est bien espionné
    //CPPUNIT_ASSERT(grille->a_ete_attaque(i,j));
  }

  // On test le cas où le mauvais joueur utilise cette méthode
  try {arme->attaque_sa_grille("A1", *grille);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne fait pas d'attaque sur la grille du joueur 1 avec un Radar!");
  }
}


void TestRadar::test_affiche_attaque() {
  Radar* arme = new Radar();

  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  std::string res = arme->attaque_ma_grille("A1|B6|D4|J:|H:|F8|", *grille);
  CPPUNIT_ASSERT(arme->affiche_attaque(res) != "");
}
