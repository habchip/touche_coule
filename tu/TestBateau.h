#ifndef TEST_BATEAU_H
#define TEST_BATEAU_H

#include <cppunit/extensions/HelperMacros.h>


class TestBateau : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestBateau);
    CPPUNIT_TEST(test_Bateau);
    CPPUNIT_TEST(test_set_attributs);
    CPPUNIT_TEST(test_get_taille);
    CPPUNIT_TEST(test_get_ligne);
    CPPUNIT_TEST(test_get_colonne);
    CPPUNIT_TEST(test_get_direction);
    CPPUNIT_TEST_SUITE_END();

    void test_Bateau();
    void test_set_attributs();
    void test_get_taille();
    void test_get_ligne();
    void test_get_colonne();
    void test_get_direction();
};

#endif
