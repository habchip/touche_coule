#include <iostream>

#include "TestUser_input.h"
#include "User_input.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestUser_input);


void TestUser_input::test_choix_hebergement() {
  std::stringbuf* in_buf = new std::stringbuf("1");
  std::cin.rdbuf(in_buf);
  CPPUNIT_ASSERT(choix_hebergement() == 1);

  std::stringbuf* in_buf2 = new std::stringbuf("2");
  std::cin.rdbuf(in_buf2);
  CPPUNIT_ASSERT(choix_hebergement() == 2);
}


void TestUser_input::test_user_input_swap_arme() {
  std::stringbuf* in_buf = new std::stringbuf("1");
  std::cin.rdbuf(in_buf);
  CPPUNIT_ASSERT(user_input_swap_arme("") == 1);

  std::stringbuf* in_buf2 = new std::stringbuf("2");
  std::cin.rdbuf(in_buf2);
  CPPUNIT_ASSERT(user_input_swap_arme("") == 2);
}


void TestUser_input::test_choix_arme() {
  for(int i = 1; i<9; i++) {
    char constr_str = static_cast<char> (i + 48);
    std::string s (&constr_str);
    std::stringbuf* in_buf = new std::stringbuf(s.substr(0,1));
    std::cin.rdbuf(in_buf);
    if (i==1) CPPUNIT_ASSERT(choix_arme() == M4A1);
    if (i==2) CPPUNIT_ASSERT(choix_arme() == SG_553);
    if (i==3) CPPUNIT_ASSERT(choix_arme() == GATLING);
    if (i==4) CPPUNIT_ASSERT(choix_arme() == AWP);
    if (i==5) CPPUNIT_ASSERT(choix_arme() == LANCE_GRENADE);
    if (i==6) CPPUNIT_ASSERT(choix_arme() == POSE_MINES);
    if (i==7) CPPUNIT_ASSERT(choix_arme() == BOMBE_EM);
    if (i==8) CPPUNIT_ASSERT(choix_arme() == RADAR);
  }
}


void TestUser_input::test_user_input_coods() {
  for(int i = 0; i<10; i++) {
    for(int j = 0; j<9; j++) {
      // Construction de la string d'entré de la fonction
      char constr_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
      std::string coods_in(constr_str);

      // On met cette string dans cin
      std::stringbuf* in_buf = new std::stringbuf(coods_in.substr(0,2));
      std::cin.rdbuf(in_buf);

      CPPUNIT_ASSERT(user_input_coods() == coods_in.substr(0,2));
    }
    // La dixième boucle est plus délicate
    // Construction de la string d'entré de la fonction
    char constr_str[1] = {static_cast<char> (i+65)};
    std::string coods_in(constr_str);
    coods_in = coods_in.substr(0,1) + "10";

    // On met cette string dans cin
    std::stringbuf* in_buf = new std::stringbuf(coods_in);
    std::cin.rdbuf(in_buf);

    CPPUNIT_ASSERT(user_input_coods() == coods_in);
  }
}


void TestUser_input::test_user_input_sens() {
  std::stringbuf* in_buf = new std::stringbuf("v");
  std::cin.rdbuf(in_buf);
  CPPUNIT_ASSERT(user_input_sens() == 'v');

  std::stringbuf* in_buf2 = new std::stringbuf("V");
  std::cin.rdbuf(in_buf2);
  CPPUNIT_ASSERT(user_input_sens() == 'v');

  std::stringbuf* in_buf3 = new std::stringbuf("h");
  std::cin.rdbuf(in_buf3);
  CPPUNIT_ASSERT(user_input_sens() == 'h');

  std::stringbuf* in_buf4 = new std::stringbuf("H");
  std::cin.rdbuf(in_buf4);
  CPPUNIT_ASSERT(user_input_sens() == 'h');
}


void TestUser_input::test_user_input_bateau() {
  for(int b=0; b<5; b++) {
    for(int k=0; k<2; k++) {
      for(int i = 0; i<10; i++) {
        for(int j = 0; j<9; j++) {
          // Construction de la string d'entré de la fonction
          char constr_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
          std::string coods_in(constr_str);
          coods_in = coods_in.substr(0,2) + (k == 0 ? " v" : " h");

          // Pour la dixième colonne on contruit la string différemment
          if(j == 9) 
            coods_in = coods_in.substr(0,1) + "10" + (k == 0 ? " v" : " h");

          // On met cette string dans cin
          std::stringbuf* in_buf = new std::stringbuf(coods_in);
          std::cin.rdbuf(in_buf);

          // On sauvegarde les résultat des bateaux
          Bateau bateaux[5];

          // On fait bien attention de ne pas sortir du cardre
          if((k == 0 && i > 6 - b) || (k == 1 && j < 6 - b)) {

            // Et on apelle la fonction
            if(b==0) user_input_bateau(PORTE_AVION,bateaux);
            if(b==1) user_input_bateau(CROISEUR,bateaux);
            if(b==2) user_input_bateau(CONTRE_TORPILLEUR,bateaux);
            if(b==3) user_input_bateau(SOUS_MARIN,bateaux);
            if(b==4) user_input_bateau(TORPILLEUR,bateaux);

            // Puis on fait les tests
            if(b==0) CPPUNIT_ASSERT(bateaux[b].get_taille() == 5);
            if(b==1) CPPUNIT_ASSERT(bateaux[b].get_taille() == 4);
            if(b==2) CPPUNIT_ASSERT(bateaux[b].get_taille() == 3);
            if(b==3) CPPUNIT_ASSERT(bateaux[b].get_taille() == 3);
            if(b==4) CPPUNIT_ASSERT(bateaux[b].get_taille() == 2);
            CPPUNIT_ASSERT(bateaux[b].get_ligne() == i);
            CPPUNIT_ASSERT(bateaux[b].get_colonne() == j);
            CPPUNIT_ASSERT(bateaux[b].get_direction() == (k==0 ? VERTICAL : HORIZONTAL));
          }
        }
      }
    }
  }
}


void TestUser_input::test_user_input_attaque() {
  // Construction de la grille
  std::stringbuf* in_buf = new std::stringbuf("A1 h B1 h C1 h D1 h E1 h");
  std::cin.rdbuf(in_buf);
  Grille grille(1);

  for(int k=0; k<2; k++) {
    for(int i = 0; i<10; i++) {
      for(int j = 0; j<9; j++) {
        // Construction de la string d'entré de la fonction
        char constr_str[2] = {static_cast<char> (i+65), static_cast<char> (j+49)};
        std::string coods_in(constr_str);

        // On met cette string dans cin
        std::stringbuf* in_buf = new std::stringbuf(coods_in.substr(0,2));
        std::cin.rdbuf(in_buf);

        CPPUNIT_ASSERT(user_input_attaque(grille, k) == coods_in.substr(0,2));
      }
      // La dixième boucle est plus délicate
      // Construction de la string d'entré de la fonction
      char constr_str[2] = {static_cast<char> (i+65), ':'};
      std::string coods_in(constr_str);
      std::string coods_out(constr_str);
      coods_in = coods_in.substr(0,1) + "10";

      // On met cette string dans cin
      std::stringbuf* in_buf = new std::stringbuf(coods_in);
      std::cin.rdbuf(in_buf);

      CPPUNIT_ASSERT(user_input_attaque(grille, k).substr(0,2) == coods_out.substr(0,2));
    }
  }
}


void TestUser_input::test_user_input_addr_ip() {
  try {
    // On test le cas où l'utilisateur rentre l'adresse à la main
    std::stringbuf* in_buf = new std::stringbuf("10.0.2.15");
    std::cin.rdbuf(in_buf);
    CPPUNIT_ASSERT(user_input_addr_ip() == "10.0.2.15");

    // On test le cas où l'ip est récupérée automatiquement
    std::ofstream ip_file("ip.txt", std::ios::out | std::ios::trunc);
    if(ip_file) {
      ip_file << "10.0.2.14" << std::endl;
      CPPUNIT_ASSERT(user_input_addr_ip() == "10.0.2.14");
      remove("ip.txt");

    } else {
      // Si le fichier ne s'ouvre pas il y a une erreur
      CPPUNIT_ASSERT(false);
    }
  } catch(std::exception const& e) {
    // Si une exception est levé, il y a une erreur
    CPPUNIT_ASSERT(false);
  }
}
