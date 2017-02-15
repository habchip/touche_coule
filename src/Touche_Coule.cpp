#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

#include "Grille.h"
#include "Case.h"
#include "Bateau.h"
#include "Client.h"
#include "Server.h"
#include "User_input.h"
#include "Dessin.h"
#include "IArme.h"
#include "ArmeFactory.h"
#include "Attaque.h"

using namespace std;


void send_msg(int connection, string msg, int size) {
  char buffer[size] = {0};
  memmove(buffer, &msg, size);
  send(connection, buffer, size, 0);
}

void atk_reponse(Grille &sa_grille, Grille ma_grille, int connection,
    IArme *arme, char * buffer, int bufsize) {

  string msg_envoi;
  for(int i=0; i<arme->get_nb_tir_par_tour(); i++){
    // On commence par construire le message d'envoi
    msg_envoi = arme->cree_msg(sa_grille);
    send_msg(connection, msg_envoi, msg_envoi.size());

    // Et on écoute la réponse de l'adversaire
    memset(buffer, 0, bufsize);
    recv(connection, buffer, bufsize, 0);
    string msg_recu(buffer);
    arme->attaque_sa_grille(msg_recu, sa_grille);
    string affiche_atk = arme->affiche_attaque(msg_recu);

    if(affiche_atk != "") {
      ma_grille.affiche_grille(JOUEUR_1, sa_grille);
      cout << affiche_atk << endl;
    }
    msg_envoi.clear();
    msg_recu.clear();
  }
}


int main(){
  int choix = 0, connection = 0, commence = 0, i = 0;
  string addr_ip;
  int bufsize = 100;
  char buffer[bufsize] = {0};

  // On commen par initialiser la graine pour tout les nombre random
  std::srand(std::time(0));

  try {
    choix = choix_hebergement();

    // Connection Client <-> Server
    switch(choix) {
      case 1:
        {
          // Le serveur lance le dès pour savoir qui commence
          std::srand(std::time(0));
          if(std::rand() > RAND_MAX/2)
            commence = 2;
          else
            commence = 1;

          Server server;
          connection = server.create_connection();
          server.~Server();
          // On informe le client sur l'identité du joueur qui commence
          // Ainsi que le mode de jeu
          memset(buffer, 0, bufsize);
          buffer[0] = commence;
          send(connection, buffer, bufsize, 0);
          break;
        }
      case 2:
        {
          addr_ip = user_input_addr_ip();
          Client client(addr_ip);
          connection = client.join_connection();
          client.~Client();
          // On récupère l'identité du joueur qui commence
          // Ainsi que le mode de jeu
          memset(buffer, 0, bufsize);
          recv(connection, buffer, bufsize, 0);
          commence = buffer[0];
          break;
        }
      default:
        cout << "Erreur: choix non valide !" << endl;
        break;
    }

    // Construciton des Grilles et choix de l'arme
    Grille ma_grille(JOUEUR_1);
    Grille sa_grille(JOUEUR_2);

    // On creer la factory qui va gérer la création et le changement d'arme
    ArmeFactory arm_fact;
    IArme *mon_arme = arm_fact.creer_arme(choix_arme());

    cout << "Attente de l'adversaire ..." << endl;

    // On est prêt lorsque on envoie la nature de l'arme
    if(choix == 2){
      send_msg(connection, mon_arme->to_string(), bufsize);
      memset(buffer, 0, bufsize);
      recv(connection, buffer, bufsize, 0);
    } else {
      memset(buffer, 0, bufsize);
      recv(connection, buffer, bufsize, 0);
      send_msg(connection, mon_arme->to_string(), bufsize);
    }

    string nom_arme_adverse(buffer);
    IArme* son_arme = arm_fact.creer_arme(nom_arme_adverse);

    cout << "L'adversaire est prêt la partie peut commençer !" << endl;

    if(choix == commence){
      // On commence par attaquer
      cout << "Vous commençez ! " << endl;
      // Mais avant on envoie le message des mines (car rien ne peut se passer)
      send_msg(connection, "NO_MINE", 7);
      sleep(1);
      atk_reponse(sa_grille, ma_grille, connection, mon_arme, buffer, bufsize);
    } else {
      cout << "Votre adversaire commence !" << endl;
    }

    // Déroulement de la partie

    while(ma_grille.get_nb_bateau_coule() != 5){
      // On récupère le résultat des mines adverses
      // Et on écrit le résultat sur notre grille
      memset(buffer, 0, bufsize);
      recv(connection, buffer,bufsize, 0);
      string msg_res_mine(buffer);
      sa_grille.passe_un_tour(msg_res_mine);

      // Si une mine explose on affiche la grille
      if(msg_res_mine != "NO_MINE") {
        ma_grille.affiche_grille(JOUEUR_1, sa_grille);
        sa_grille.affiche_explosion(msg_res_mine);
      }

      // Puis on récupère l'attaque de l'adversaire
      memset(buffer, 0, bufsize);
      if(!mon_arme->passe_ton_tour()) {
        for(i =0; i<son_arme->get_nb_tir_par_tour(); i++){
          recv(connection, buffer,bufsize, 0);
          string msg_recu(buffer);

          if(msg_recu.substr(0,4) == "SWAP") {
            son_arme = arm_fact.creer_arme(msg_recu.substr(4));
            cout << "Votre adversaire change d'arme" << endl;
            break;
          }

          memset(buffer, 0, bufsize);
          // On regarde le résultat
          strcpy(buffer, son_arme->attaque_ma_grille(msg_recu, ma_grille).c_str());

          // Que l'on renvoie à l'adversaire
          send_msg(connection, buffer, bufsize);
          memset(buffer, 0, bufsize);
          string affiche_atk = son_arme->affiche_attaque(msg_recu);

          if(affiche_atk != "") {
            ma_grille.affiche_grille(JOUEUR_1, sa_grille);
            cout << affiche_atk << endl;
          }
        }
      }

      if(sa_grille.get_nb_bateau_coule() == 5)
        break;

      // A chaque tour on s'occupe des mines déjà posée
      std::string res_mines = ma_grille.passe_un_tour();
      if(res_mines == "") {
        send_msg(connection, "NO_MINE", 7);

      } else {
        send_msg(connection, res_mines, res_mines.size());
        ma_grille.affiche_grille(JOUEUR_1, sa_grille);
        ma_grille.affiche_explosion(msg_res_mine);
      }

      // Puis on attaque si on ne passe pas notre tour
      if(!son_arme->passe_ton_tour()) {
        if(user_input_swap_arme(mon_arme->to_string()) == ATK_AVEC_ARME_ACTUELLE) {
          atk_reponse(sa_grille, ma_grille,  connection, mon_arme, buffer, bufsize);

        } else {
          mon_arme = arm_fact.creer_arme(choix_arme());
          std::string msg_chgmt_arme = "SWAP" + mon_arme->to_string();
          send_msg(connection, msg_chgmt_arme, msg_chgmt_arme.size());
        }
      }
    }

    // Desallocation
    arm_fact.~ArmeFactory();

    // On affiche le dénoument
    if(sa_grille.get_nb_bateau_coule() == 5)
      ta_perdu();
    else
      ta_gagne();

  }catch(exception const& e) {
    cerr << "ERROR: " << e.what() << endl;
  }
  close(connection);
}
