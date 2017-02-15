#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

#include "Client.h"

using namespace std;

Client::Client(string addr_ip) : ip(addr_ip) {}

Client::~Client() {}


int Client::join_connection() {
    int client;
    int portNum = 1500; // NOTE that the port number is same for both client and server

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (client < 0)
        throw runtime_error("Etablissement de la socket client impossible");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());

    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        throw runtime_error("Creation de la connection vers le serveur impossible");

    cout << "connection au client réussi" << endl;


    return client;
}
