#include <thread>
#include <unistd.h>

#include "TestClient.h"
#include "Client.h"
#include "Server.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestClient);

void TestClient::test_Client() {
  Client* c = new Client("10.0.2.15");
  CPPUNIT_ASSERT(c != NULL);
}

void TestClient::test_Client_dest() {
  Client* c = new Client("10.0.2.15");
  c->~Client();
  CPPUNIT_ASSERT(c != NULL);
}


void server_create_connection() {
  try {
  Server s;
  s.create_connection();
  s.~Server();
  } catch (std::exception const& e){
    // On est forcement dans un cas d'erreur
    CPPUNIT_ASSERT(false);
  }
}

void TestClient::test_join_connection() {
  Client* c = new Client("10.0.2.15");

  // On commence par tester le cas d'erreur
  try { c->join_connection(); }
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Creation de la connection vers le serveur impossible");
  }

  // Puis on cree le server pour tester la connection
  // TODO: Faire pareil avec un mutex
  try{
  std::thread thread_server(server_create_connection);
  sleep(1);
  c->join_connection();
  thread_server.join();
  } catch (std::exception const& e){
    // On est forcement dans un cas d'erreur
    CPPUNIT_ASSERT(false);
  }
}

