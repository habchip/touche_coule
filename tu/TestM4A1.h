#ifndef TEST_M4A1_H
#define TEST_M4A1_H

#include <cppunit/extensions/HelperMacros.h>


class TestM4a1 : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestM4a1);
    CPPUNIT_TEST(test_get_type);
    CPPUNIT_TEST(test_get_nb_tir_par_tour);
    CPPUNIT_TEST(test_passe_ton_tour);
    CPPUNIT_TEST(test_to_string);
    CPPUNIT_TEST(test_cree_msg);
    CPPUNIT_TEST(test_attaque_ma_grille);
    CPPUNIT_TEST(test_attaque_sa_grille);
    CPPUNIT_TEST(test_affiche_attaque);
    CPPUNIT_TEST_SUITE_END();



    void test_get_type();
    void test_get_nb_tir_par_tour();
    void test_passe_ton_tour();
    void test_to_string();
    void test_cree_msg();
    void test_attaque_ma_grille();
    void test_attaque_sa_grille();
    void test_affiche_attaque();
};

#endif
