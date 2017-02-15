#include "TestBateau.h"
#include "Bateau.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestBateau);


void TestBateau::test_Bateau() {
  Bateau* b = new Bateau();
  CPPUNIT_ASSERT(b != NULL);
}

void TestBateau::test_set_attributs() {
  Bateau* b = new Bateau();
  // Ici on ne testera que les cas d'erreur

  // Pour le porte-avion
  try { b->set_attributs(PORTE_AVION, 0, 7, HORIZONTAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Porte-avion mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(PORTE_AVION, 0, 7, VERTICAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Porte-avion mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(PORTE_AVION, 0, 7, UNDEFINED_DIR); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "La direction du porte-avion doit être défini");
  }

  // Pour le croiseur
  try { b->set_attributs(CROISEUR, 0, 9, HORIZONTAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Croiseur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(CROISEUR, 0, 9, VERTICAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Croiseur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(CROISEUR, 0, 9, UNDEFINED_DIR); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "La direction du croiseur doit être défini");
  }

  // Pour le contre-torpilleur
  try { b->set_attributs(CONTRE_TORPILLEUR, 0, 9, HORIZONTAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Contre-torpilleur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(CONTRE_TORPILLEUR, 0, 9, VERTICAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Contre-torpilleur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(CONTRE_TORPILLEUR, 0, 9, UNDEFINED_DIR); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "La direction du contre-torpilleur doit être défini");
  }

  // Pour le sous-marin
  try { b->set_attributs(SOUS_MARIN, 0, 9, HORIZONTAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Sous-marin mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(SOUS_MARIN, 0, 9, VERTICAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Sous-marin mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(SOUS_MARIN, 0, 9, UNDEFINED_DIR); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "La direction du sous-marin doit être défini");
  }

  // Pour le torpilleur
  try { b->set_attributs(TORPILLEUR, 0, 9, HORIZONTAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Torpilleur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(TORPILLEUR, 0, 9, VERTICAL); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Torpilleur mal placé: il ne rentre pas dans la grille");
  }
  try { b->set_attributs(TORPILLEUR, 0, 9, UNDEFINED_DIR); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "La direction du torpilleur doit être défini");
  }
}

void TestBateau::test_get_taille() {
  Bateau* b = new Bateau();
  // Test d'un cas d'erreur
  try { b->get_taille(); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Type de bateau non défini (get_taille)");
  }

  // Test des cas conventionnels
  b->set_attributs(PORTE_AVION, 0, 0, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_taille() == 5);
  b->set_attributs(CROISEUR, 0, 0, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_taille() == 4);
  b->set_attributs(SOUS_MARIN, 0, 0, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_taille() == 3);
  b->set_attributs(CONTRE_TORPILLEUR, 0, 0, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_taille() == 3);
  b->set_attributs(TORPILLEUR, 0, 0, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_taille() == 2);
}

void TestBateau::test_get_ligne() {
  Bateau* b = new Bateau();
  for(int i = 0; i<10; i++) {
    b->set_attributs(PORTE_AVION, i, 0, HORIZONTAL);
    CPPUNIT_ASSERT(b->get_ligne() == i);
  }
}

void TestBateau::test_get_colonne() {
  Bateau* b = new Bateau();
  for(int i = 0; i<10; i++) {
    b->set_attributs(PORTE_AVION, 9, i, VERTICAL);
    CPPUNIT_ASSERT(b->get_colonne() == i);
  }
}

void TestBateau::test_get_direction() {
  Bateau* b = new Bateau();
  b->set_attributs(PORTE_AVION, 5, 5, VERTICAL);
  CPPUNIT_ASSERT(b->get_direction() == VERTICAL);
  b->set_attributs(PORTE_AVION, 5, 5, HORIZONTAL);
  CPPUNIT_ASSERT(b->get_direction() == HORIZONTAL);
}

