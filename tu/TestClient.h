#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <cppunit/extensions/HelperMacros.h>


class TestClient : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestClient);
    CPPUNIT_TEST(test_Client);
    CPPUNIT_TEST(test_Client_dest);
    CPPUNIT_TEST(test_join_connection);
    CPPUNIT_TEST_SUITE_END();


    void test_Client();
    void test_Client_dest();
    void test_join_connection();
};

#endif
