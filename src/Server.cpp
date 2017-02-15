#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

#include "Server.h"

using namespace std;

Server::Server() {}

Server::~Server() {}

int Server::create_connection() {
    int client, server;
    int portNum = 1500;

    struct sockaddr_in server_addr;
    socklen_t size;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
      throw runtime_error("Etablissement de la socket serveur impossible");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */

    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
        throw runtime_error("Bind connection impossible, la connection est déjà établie");

    size = sizeof(server_addr);
    cout << "En attente de client...";
    cout.flush();

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(client, 1);

    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) 
        throw runtime_error("Acceptation de la conneciton client impossible");

    cout << "client trouvé" << endl;

    // TODO: Faire cette ligne à la fin du main
    // close(client);
    return server;
}
