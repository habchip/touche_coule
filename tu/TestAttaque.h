#ifndef TEST_ATTAQUE_H
#define TEST_ATTAQUE_H

#include <cppunit/extensions/HelperMacros.h>


class TestAttaque : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestAttaque);
    CPPUNIT_TEST(test_to_string_attaque);
    CPPUNIT_TEST(test_conv_to_attaque);
    CPPUNIT_TEST_SUITE_END();


    void test_to_string_attaque();
    void test_conv_to_attaque();
};

#endif
