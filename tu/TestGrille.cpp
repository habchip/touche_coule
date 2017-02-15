#include "TestGrille.h"
#include "Grille.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestGrille);

void TestGrille::test_Grille() {
  // On ne fait pas tout les tests possible ce serait trop fastidieu
  // Test pour une grille vide
  Grille* grille2 = new Grille(JOUEUR_2);
  CPPUNIT_ASSERT(grille2 != NULL);

  // Test pour une grille qu'on remplie
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  CPPUNIT_ASSERT(grille != NULL);
}

void TestGrille::test_affiche_grille() {
  // Il n'y a pas d'assert, il faudrait check le cout ...
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  grille->affiche_grille(1);
  grille->affiche_grille(2);
}

void TestGrille::test_affiche_grille_2() {
  // Il n'y a pas d'assert, il faudrait check le cout ...
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // On créer la grille adverse
  Grille* grille_adv = new Grille(JOUEUR_2);

  // On fait le test
  grille->affiche_grille(1, *grille_adv);
  grille->affiche_grille(2, *grille_adv);
}

void TestGrille::test_get_joueur() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  CPPUNIT_ASSERT(grille->get_joueur() == 1);

  Grille* grille2 = new Grille(JOUEUR_2);
  CPPUNIT_ASSERT(grille2->get_joueur() == 2);
}

void TestGrille::test_get_nb_bateau_coule() {
  // On construit la grille du joueur 1
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // Et celle du joueur 2
  Grille* grille2 = new Grille(JOUEUR_2);


  int resultat_attendu = 0;
  CPPUNIT_ASSERT(grille->get_nb_bateau_coule() == resultat_attendu);
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On attaque les deux grilles
      Attaque res_atk = grille->attaque(i,j);
      grille2->attaque(i,j,res_atk);

      // Si l'attaque coule un bateau alors le resultat attendu s'incrémente
      if(res_atk == COULE)
        resultat_attendu++;

      // Enfin les tests
      CPPUNIT_ASSERT(grille->get_nb_bateau_coule() == resultat_attendu);
      CPPUNIT_ASSERT(grille2->get_nb_bateau_coule() == resultat_attendu);
    }
  }
}


void TestGrille::test_retrouve_bateau() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // Test de cas d'erreurs
  try {grille->retrouve_bateau(2,1);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "Grille::retrouve_bateau => Pas de bateau trouvé");
  }

  Grille* grille2 = new Grille(JOUEUR_2);
  try {grille2->retrouve_bateau(0,0);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne recherche pas de bateau sur la grille du joueur 2 !");
  }

  // Test du cas où ça fonctionne

  // Pour le porte-avion
  for(int i=0; i<5; i++) {
    std::list<int> res = grille->retrouve_bateau(0,i);
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 1); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 2); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 3); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 4); res.pop_front();
  }

  // Pour le croiseur
  for(int i=0; i<4; i++) {
    std::list<int> res = grille->retrouve_bateau(6 - i,5);
    CPPUNIT_ASSERT(res.front() == 6); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 5); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 5); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 5); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 4); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 5); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 3); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 5); res.pop_front();
  }

  // Pour le contre_torpilleur
  for(int i=0; i<3; i++) {
    std::list<int> res = grille->retrouve_bateau(9 - i,9);
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 8); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 7); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
  }

  // Pour le sous-marin
  for(int i=0; i<3; i++) {
    std::list<int> res = grille->retrouve_bateau(9,i);
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 1); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 2); res.pop_front();
  }

  // Pour le torpilleur
  for(int i=0; i<2; i++) {
    std::list<int> res = grille->retrouve_bateau(1 - i,9);
    CPPUNIT_ASSERT(res.front() == 1); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 0); res.pop_front();
    CPPUNIT_ASSERT(res.front() == 9); res.pop_front();
  }

}

void TestGrille::test_attaque() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      Attaque res = grille->attaque(i,j);
      if     (i == 0 && j == 0) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 0 && j == 1) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 0 && j == 2) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 0 && j == 3) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 0 && j == 4) CPPUNIT_ASSERT(res == COULE);
      else if(i == 0 && j == 9) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 1 && j == 9) CPPUNIT_ASSERT(res == COULE);
      else if(i == 3 && j == 5) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 4 && j == 5) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 5 && j == 5) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 6 && j == 5) CPPUNIT_ASSERT(res == COULE);
      else if(i == 7 && j == 9) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 8 && j == 9) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 9 && j == 0) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 9 && j == 1) CPPUNIT_ASSERT(res == TOUCHE);
      else if(i == 9 && j == 2) CPPUNIT_ASSERT(res == COULE);
      else if(i == 9 && j == 9) CPPUNIT_ASSERT(res == COULE);

      else CPPUNIT_ASSERT(res == ALO);
    }
  }

  // Test de cas d'erreur
  Grille* grille2 = new Grille(JOUEUR_2);
  try {grille2->attaque(0,0);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'attaque pas de bateau sur la grille du joueur 2 !");
  }

}

void TestGrille::test_attaque_2() {
  // On construit la grille
  Grille* grille = new Grille(JOUEUR_2);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On fait notre attaque
      Attaque atk = ((i+j)%3 == 0) ? ALO : ((i+j)%3 == 1) ? TOUCHE : COULE;
      grille->attaque(i,j,atk);

      // On vérifie que la donnée est bien rentrée
      CPPUNIT_ASSERT(grille->a_ete_attaque(i,j));
    }
  }

  // Test de cas d'erreur
  // On construit la grille du joueur 1
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille2 = new Grille(JOUEUR_1);

  // On ne peut pas faire ce genre d'attaque sur cette grille
  try {grille2->attaque(0,0);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'attaque pas de bateau sur la grille du joueur 1 !");
  }
}

void TestGrille::test_a_ete_attaque() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On attaque une fois sur deux
      if((i+j) % 2 == 0)
        grille->attaque(i,j);

      CPPUNIT_ASSERT(grille->a_ete_attaque(i,j) == ((i+j) % 2 == 0));
    }
  }
}

void TestGrille::test_espionne() {
  // On construit la grille
  Grille* grille = new Grille(JOUEUR_2);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On espionne
      grille->espionne(i,j,((i+j) % 2 == 0));

      // On vérifie qu'on à bien espionné
      CPPUNIT_ASSERT(grille->a_ete_espionne(i,j));
    }
  }

  // Test de cas d'erreur
  // On construit la grille du joueur 1
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille2 = new Grille(JOUEUR_1);

  // On ne peut pas faire ce genre d'attaque sur cette grille
  try {grille2->espionne(0,0, true);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'espionne pas sur la grille du joueur 1 !");
  }
}

void TestGrille::test_espionne_2() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);


  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      bool res = grille->espionne(i,j);
      if     (i == 0 && j == 0) CPPUNIT_ASSERT(res);
      else if(i == 0 && j == 1) CPPUNIT_ASSERT(res);
      else if(i == 0 && j == 2) CPPUNIT_ASSERT(res);
      else if(i == 0 && j == 3) CPPUNIT_ASSERT(res);
      else if(i == 0 && j == 4) CPPUNIT_ASSERT(res);
      else if(i == 0 && j == 9) CPPUNIT_ASSERT(res);
      else if(i == 1 && j == 9) CPPUNIT_ASSERT(res);
      else if(i == 3 && j == 5) CPPUNIT_ASSERT(res);
      else if(i == 4 && j == 5) CPPUNIT_ASSERT(res);
      else if(i == 5 && j == 5) CPPUNIT_ASSERT(res);
      else if(i == 6 && j == 5) CPPUNIT_ASSERT(res);
      else if(i == 7 && j == 9) CPPUNIT_ASSERT(res);
      else if(i == 8 && j == 9) CPPUNIT_ASSERT(res);
      else if(i == 9 && j == 0) CPPUNIT_ASSERT(res);
      else if(i == 9 && j == 1) CPPUNIT_ASSERT(res);
      else if(i == 9 && j == 2) CPPUNIT_ASSERT(res);
      else if(i == 9 && j == 9) CPPUNIT_ASSERT(res);

      else CPPUNIT_ASSERT(!res);
    }
  }

  // Test de cas d'erreur
  // On construit la grille du joueur 2
  Grille* grille2 = new Grille(JOUEUR_2);

  // On ne peut pas faire ce genre d'attaque sur cette grille
  try {grille2->espionne(0,0);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'espionne pas sur la grille du joueur 2 !");
  }
}

void TestGrille::test_a_ete_espionne() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On espionne une fois sur deux
      if((i+j) % 2 == 0)
        grille->espionne(i,j);

      CPPUNIT_ASSERT(grille->a_ete_espionne(i,j) == ((i+j) % 2 == 0));
    }
  }
}

void TestGrille::test_set_mine() {
  // TODO: trouver un moyen de tester cette fonction
  // On construit la grille
  //std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  //std::cin.rdbuf(in_buf);
  //Grille* grille = new Grille(JOUEUR_1);
}

void TestGrille::test_explose() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // On fait exploser toutes les cases une par une
      Attaque atk[5];
      grille->explose(i,j,atk);

      // On vérifie le resultat chaque fois
      for(int k=0; k<5; k++) {
        // On fait tout les cas où ça touche
        if     (i == 0 && j == 0) CPPUNIT_ASSERT(atk[0] == TOUCHE);
        else if(i == 0 && j == 0) CPPUNIT_ASSERT(atk[3] == TOUCHE);
        else if(i == 0 && j == 1) CPPUNIT_ASSERT(atk[3] == TOUCHE);
        else if(i == 0 && j == 2) CPPUNIT_ASSERT(atk[3] == TOUCHE);
        else if(i == 0 && j == 3) CPPUNIT_ASSERT(atk[3] == COULE);
        else if(i == 0 && j == 8) CPPUNIT_ASSERT(atk[3] == TOUCHE);
        else if(i == 0 && j == 9) CPPUNIT_ASSERT(atk[2] == COULE);
        else if(i == 2 && j == 5) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 3 && j == 5) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 4 && j == 5) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 5 && j == 5) CPPUNIT_ASSERT(atk[2] == COULE);
        else if(i == 6 && j == 9) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 7 && j == 9) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 8 && j == 0) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 8 && j == 1) CPPUNIT_ASSERT(atk[2] == TOUCHE);
        else if(i == 8 && j == 2) CPPUNIT_ASSERT(atk[2] == COULE);
        else if(i == 8 && j == 9) CPPUNIT_ASSERT(atk[2] == COULE);

        else {
          // Si on attaque chaque case, le centre le nord et l'ouest sont déjà attaqué
          // Sinon on ne touche que si on est pas sur les bords
          if(k == 2 && i < 9)
            CPPUNIT_ASSERT(atk[k] == ALO);
          else if(k == 3 && j < 9 && i == 0)
            CPPUNIT_ASSERT(atk[k] == ALO);
          else
            CPPUNIT_ASSERT(atk[k] == UNDEFINED_ATK);
        }
      }
    }
  }

  // Test de cas d'erreur
  Grille* grille2 = new Grille(JOUEUR_2);
  Attaque fail_atk = ALO;
  try {grille2->explose(0,0,&fail_atk);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'explose pas de bateau sur la grille du joueur 2 !");
  }
}

void TestGrille::test_explose_adversaire() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // On construit 2 grille pour simuler les deux adversaires
  Grille* grille2 = new Grille(JOUEUR_2);

  // On attaque la grille 1 pour pouvoir ecrire le resultat dans la grille 2
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      Attaque atk[5];
      grille->explose(i,j,atk);
      grille2->explose_adversaire(i,j,atk);

      // Puis on test que les cinq case on bien été attaqué
      CPPUNIT_ASSERT(grille2->a_ete_attaque(i,j));
      if(i > 0) CPPUNIT_ASSERT(grille2->a_ete_attaque(i - 1, j));
      if(i < 9) CPPUNIT_ASSERT(grille2->a_ete_attaque(i + 1, j));
      if(j > 0) CPPUNIT_ASSERT(grille2->a_ete_attaque(i, j - 1));
      if(j < 0) CPPUNIT_ASSERT(grille2->a_ete_attaque(i, j + 1));
    }
  }

  Attaque fail_atk = ALO;
  try {grille->explose_adversaire(0,0,&fail_atk);}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On n'explose pas de bateau sur la grille du joueur 1 !");
  }
}

void TestGrille::test_passe_un_tour() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // On commence par poser des mines
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      grille->set_mine(i,j);
    }
  }

  // Puis on check que rien n'explose dans les premiers tours
  for(int k = 0; k<NB_TOUR_MINE - 1 ; k++)
    CPPUNIT_ASSERT(grille->passe_un_tour() == "");

  // Puis on lit la string de retour et on s'assure qu'il n'y a pas d'erreur
  std::string res = grille->passe_un_tour();
  int debut_mine_string = -1;
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      // Pour chaque mine posé il doit y avoir une explosion
      debut_mine_string = res.find('*', debut_mine_string + 1);
      CPPUNIT_ASSERT(debut_mine_string != -1);
      // TODO: finir ce test en regardant la string
    }
  }

  // Test du cas d'erreur où on passe un tour sur la mauvaise grille
  Grille* grille2 = new Grille(JOUEUR_2);
  try {grille2->passe_un_tour();}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne passe pas de tour sur la grille du joueur 2 !");
  }
}

void TestGrille::test_passe_un_tour_2() {
  // On construit deux grille (une pour chaque adversaire)
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);
  Grille* grille2 = new Grille(JOUEUR_2);


  // On commence par poser des mines
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      grille->set_mine(i,j);
    }
  }

  // Puis on les fait toutes exploser dans la première grille,
  // pour passer le résultat à la deuxième
  for(int k = 0; k<NB_TOUR_MINE; k++) {
    std::string res = grille->passe_un_tour();
    grille2->passe_un_tour(res);
  }

  // Enfin on vérifie que toute les cases on bien été attaquée
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      CPPUNIT_ASSERT(grille2->a_ete_attaque(i,j));
    }
  }

  // Test du cas d'erreur où on passe un tour sur la mauvaise grille
  try {grille->passe_un_tour("error");}
  catch (std::exception const& e) {
    std::string msg_err(e.what());
    CPPUNIT_ASSERT(msg_err == "On ne passe pas de tour sur la grille du joueur 1 !");
  }
}


// TODO: Tester qu'il y a bien 200 lignes affichées 
// 100 pour l'explosion des mines
// 100 pour les cases touchées
void TestGrille::test_affiche_explosion() {
  // On construit la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h G6 v J10 v J1 h B10 v");
  std::cin.rdbuf(in_buf);
  Grille* grille = new Grille(JOUEUR_1);

  // On commence par poser des mines
  for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
      grille->set_mine(i,j);
    }
  }

  // Puis on les fait toutes exploser et on affiche le resultat
  for(int k = 0; k<NB_TOUR_MINE; k++) {
    std::string res = grille->passe_un_tour();
    grille->affiche_explosion(res);
  }
}
