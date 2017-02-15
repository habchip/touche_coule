#ifndef TEST_DESSIN_H
#define TEST_DESSIN_H

#include <cppunit/extensions/HelperMacros.h>


class TestDessin : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestDessin);
    CPPUNIT_TEST(test_ta_perdu);
    CPPUNIT_TEST(test_ta_gagne);
    CPPUNIT_TEST_SUITE_END();


    void test_ta_perdu();
    void test_ta_gagne();
};

#endif
