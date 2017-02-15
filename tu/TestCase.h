#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <cppunit/extensions/HelperMacros.h>


class TestCase : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestCase);
    CPPUNIT_TEST(test_Case);
    CPPUNIT_TEST(test_set_bateau);
    CPPUNIT_TEST(test_remove_bateau);
    CPPUNIT_TEST(test_contient_bateau);
    CPPUNIT_TEST(test_est_touche);
    CPPUNIT_TEST(test_attaque);
    CPPUNIT_TEST(test_est_vue);
    CPPUNIT_TEST(test_regarde);
    CPPUNIT_TEST(test_est_mine);
    CPPUNIT_TEST(test_set_mine);
    CPPUNIT_TEST(test_decremente_mine);
    CPPUNIT_TEST_SUITE_END();

    void test_Case();
    void test_set_bateau();
    void test_remove_bateau();
    void test_contient_bateau();
    void test_est_touche();
    void test_attaque();
    void test_est_vue();
    void test_regarde();
    void test_est_mine();
    void test_set_mine();
    void test_decremente_mine();
};

#endif
