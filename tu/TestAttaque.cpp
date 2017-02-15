#include "TestAttaque.h"
#include "Attaque.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestAttaque);

void TestAttaque::test_to_string_attaque() {
  CPPUNIT_ASSERT(to_string_attaque(ALO) == "ALO");
  CPPUNIT_ASSERT(to_string_attaque(TOUCHE) == "TOUCHE");
  CPPUNIT_ASSERT(to_string_attaque(COULE) == "COULE");
  CPPUNIT_ASSERT(to_string_attaque(UNDEFINED_ATK) == "VOID");

  try { to_string_attaque(static_cast<Attaque> (10)); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Wrong attaque to string");
  }
}

void TestAttaque::test_conv_to_attaque() {
  CPPUNIT_ASSERT(conv_to_attaque("ALO") == ALO);
  CPPUNIT_ASSERT(conv_to_attaque("TOUCHE") == TOUCHE);
  CPPUNIT_ASSERT(conv_to_attaque("COULE") == COULE);
  CPPUNIT_ASSERT(conv_to_attaque("VOID") == UNDEFINED_ATK);

  try {conv_to_attaque("ERR");}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Bad string to convert to attaque ERR");
  }
}

