#include "TestArmeFactory.h"
#include "ArmeFactory.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestArmeFactory);


void TestArmeFactory::test_ArmeFactory() {
  ArmeFactory* arm_fact = new ArmeFactory();
  CPPUNIT_ASSERT(arm_fact != NULL);
}


void TestArmeFactory::test_creer_arme_by_arme() {
  ArmeFactory* arm_fact = new ArmeFactory();

  // Chaque fois on vérifie que l'objet creer est bien du type attendu
  CPPUNIT_ASSERT(arm_fact->creer_arme(M4A1)->get_type() == M4A1);
  CPPUNIT_ASSERT(arm_fact->creer_arme(SG_553)->get_type() == SG_553);
  CPPUNIT_ASSERT(arm_fact->creer_arme(GATLING)->get_type() == GATLING);
  CPPUNIT_ASSERT(arm_fact->creer_arme(AWP)->get_type() == AWP);
  CPPUNIT_ASSERT(arm_fact->creer_arme(LANCE_GRENADE)->get_type() == LANCE_GRENADE);
  CPPUNIT_ASSERT(arm_fact->creer_arme(POSE_MINES)->get_type() == POSE_MINES);
  CPPUNIT_ASSERT(arm_fact->creer_arme(BOMBE_EM)->get_type() == BOMBE_EM);
  CPPUNIT_ASSERT(arm_fact->creer_arme(RADAR)->get_type() == RADAR);
  CPPUNIT_ASSERT(arm_fact->creer_arme(M4A1)->get_type() == M4A1);

  // test des cas d'erreur
  try{arm_fact->creer_arme(UNDEFINED_ARME);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne peut pas creer une arme non référençée (Arme factory arme)");
  }

  try{arm_fact->creer_arme(static_cast<ARME> (100));}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne peut pas creer une arme non référençée (Arme factory arme)");
  }
}


void TestArmeFactory::test_creer_arme_by_string() {
  ArmeFactory* arm_fact = new ArmeFactory();

  // Chaque fois on vérifie que l'objet creer est bien du type attendu
  CPPUNIT_ASSERT(arm_fact->creer_arme("M4A1")->get_type() == M4A1);
  CPPUNIT_ASSERT(arm_fact->creer_arme("SG_553")->get_type() == SG_553);
  CPPUNIT_ASSERT(arm_fact->creer_arme("GATLING")->get_type() == GATLING);
  CPPUNIT_ASSERT(arm_fact->creer_arme("AWP")->get_type() == AWP);
  CPPUNIT_ASSERT(arm_fact->creer_arme("LANCE_GRENADE")->get_type() == LANCE_GRENADE);
  CPPUNIT_ASSERT(arm_fact->creer_arme("POSE_MINES")->get_type() == POSE_MINES);
  CPPUNIT_ASSERT(arm_fact->creer_arme("BOMBE_EM")->get_type() == BOMBE_EM);
  CPPUNIT_ASSERT(arm_fact->creer_arme("RADAR")->get_type() == RADAR);
  CPPUNIT_ASSERT(arm_fact->creer_arme("M4A1")->get_type() == M4A1);

  // test des cas d'erreur
  try{arm_fact->creer_arme("UNDEFINED_ARME");}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne peut pas creer une arme non référençée (Arme factory string)");
  }

  try{arm_fact->creer_arme("ERREUR");}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne peut pas creer une arme non référençée (Arme factory string)");
  }
}
