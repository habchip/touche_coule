#ifndef TEST_USER_INPUT_H
#define TEST_USER_INPUT_H

#include <cppunit/extensions/HelperMacros.h>


class TestUser_input : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestUser_input);
    CPPUNIT_TEST(test_choix_hebergement);
    CPPUNIT_TEST(test_user_input_swap_arme);
    CPPUNIT_TEST(test_choix_arme);
    CPPUNIT_TEST(test_user_input_coods);
    CPPUNIT_TEST(test_user_input_sens);
    CPPUNIT_TEST(test_user_input_bateau);
    CPPUNIT_TEST(test_user_input_attaque);
    CPPUNIT_TEST(test_user_input_addr_ip);
    CPPUNIT_TEST_SUITE_END();

    void test_choix_hebergement();
    void test_user_input_swap_arme();
    void test_choix_arme();
    void test_user_input_coods();
    void test_user_input_sens();
    void test_user_input_bateau();
    void test_user_input_attaque();
    void test_user_input_addr_ip();
};

#endif
