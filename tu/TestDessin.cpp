#include "TestDessin.h"
#include "Dessin.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDessin);

void TestDessin::test_ta_perdu() {
  ta_perdu();
}

void TestDessin::test_ta_gagne() {
  ta_gagne();
}

