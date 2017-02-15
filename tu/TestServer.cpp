#include "TestServer.h"
#include "Server.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestServer);

void TestServer::test_Server() {
  Server* s = new Server();
  CPPUNIT_ASSERT(s != NULL);
}

void TestServer::test_Server_dest() {
  Server* s = new Server();
  s->~Server();
  CPPUNIT_ASSERT(s != NULL);
}

void TestServer::test_create_connection() {
  // TODO: Il faut tester ici les cas d'erreur de la fonction
}

