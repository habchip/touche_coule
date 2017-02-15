#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include <cppunit/extensions/HelperMacros.h>


class TestServer : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestServer);
    CPPUNIT_TEST(test_Server);
    CPPUNIT_TEST(test_Server_dest);
    CPPUNIT_TEST(test_create_connection);
    CPPUNIT_TEST_SUITE_END();


    void test_Server();
    void test_Server_dest();
    void test_create_connection();
};

#endif
