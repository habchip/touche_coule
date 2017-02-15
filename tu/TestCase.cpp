#include "TestCase.h"
#include "Case.h"

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestCase);

void TestCase::test_Case() {
  Case *c = new Case();
  CPPUNIT_ASSERT(c != NULL);
}

void TestCase::test_set_bateau() {
  Case *c = new Case();
  c->set_bateau();
  CPPUNIT_ASSERT(c->contient_bateau());
}

void TestCase::test_remove_bateau() {
  Case *c = new Case();
  c->set_bateau();
  CPPUNIT_ASSERT(c->contient_bateau());
  c->remove_bateau();
  CPPUNIT_ASSERT(!c->contient_bateau());
}

void TestCase::test_contient_bateau() {
  Case *c = new Case();
  CPPUNIT_ASSERT(!c->contient_bateau());
  c->set_bateau();
  CPPUNIT_ASSERT(c->contient_bateau());
  c->remove_bateau();
  CPPUNIT_ASSERT(!c->contient_bateau());
}

void TestCase::test_est_touche() {
  Case *c = new Case();
  CPPUNIT_ASSERT(!c->est_touche());
  c->attaque();
  CPPUNIT_ASSERT(c->est_touche());
}

void TestCase::test_attaque() {
  Case *c = new Case();
  CPPUNIT_ASSERT(!c->attaque());
  c->set_bateau();
  CPPUNIT_ASSERT(c->attaque());
}

void TestCase::test_est_vue() {
  Case *c = new Case();
  CPPUNIT_ASSERT(!c->est_vue());
  c->regarde();
  CPPUNIT_ASSERT(c->est_vue());
}

void TestCase::test_regarde() {
  Case *c = new Case();
  c->regarde();
  CPPUNIT_ASSERT(c->est_vue());

  Case* b = new Case();
  b->attaque();
  b->regarde();
  CPPUNIT_ASSERT(!b->est_vue());
}

void TestCase::test_est_mine() {
  Case *c = new Case();
  CPPUNIT_ASSERT(c->est_mine() == -1);
}

void TestCase::test_set_mine() {
  Case *c = new Case();
  c->set_mine();
  CPPUNIT_ASSERT(c->est_mine() == NB_TOUR_MINE);
}

void TestCase::test_decremente_mine() {
  Case *c = new Case();
  c->set_mine();
  for(int i=0; i<NB_TOUR_MINE; i++) {
    c->decremente_mine();
    CPPUNIT_ASSERT(c->est_mine() == NB_TOUR_MINE - i - 1);
  }
}

