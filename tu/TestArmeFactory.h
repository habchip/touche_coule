#ifndef TEST_ARMEFACTORY_H
#define TEST_ARMEFACTORY_H

#include <cppunit/extensions/HelperMacros.h>


class TestArmeFactory : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestArmeFactory);
    CPPUNIT_TEST(test_ArmeFactory);
    CPPUNIT_TEST(test_creer_arme_by_arme);
    CPPUNIT_TEST(test_creer_arme_by_string);
    CPPUNIT_TEST_SUITE_END();


    void test_ArmeFactory();
    void test_creer_arme_by_arme();
    void test_creer_arme_by_string();
};

#endif
