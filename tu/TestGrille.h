#ifndef TEST_GRILLE_H
#define TEST_GRILLE_H

#include <cppunit/extensions/HelperMacros.h>


class TestGrille : public CppUnit::TestFixture {
  public:
    CPPUNIT_TEST_SUITE(TestGrille);
    CPPUNIT_TEST(test_Grille);
    CPPUNIT_TEST(test_affiche_grille);
    CPPUNIT_TEST(test_affiche_grille_2);
    CPPUNIT_TEST(test_get_joueur);
    CPPUNIT_TEST(test_get_nb_bateau_coule);
    CPPUNIT_TEST(test_retrouve_bateau);
    CPPUNIT_TEST(test_attaque);
    CPPUNIT_TEST(test_attaque_2);
    CPPUNIT_TEST(test_a_ete_attaque);
    CPPUNIT_TEST(test_espionne);
    CPPUNIT_TEST(test_espionne_2);
    CPPUNIT_TEST(test_a_ete_espionne);
    CPPUNIT_TEST(test_set_mine);
    CPPUNIT_TEST(test_explose);
    CPPUNIT_TEST(test_explose_adversaire);
    CPPUNIT_TEST(test_passe_un_tour);
    CPPUNIT_TEST(test_passe_un_tour_2);
    CPPUNIT_TEST(test_affiche_explosion);
    CPPUNIT_TEST_SUITE_END();

    void test_Grille();
    void test_affiche_grille();
    void test_affiche_grille_2();
    void test_get_joueur();
    void test_get_nb_bateau_coule();
    void test_retrouve_bateau();
    void test_attaque();
    void test_attaque_2();
    void test_a_ete_attaque();
    void test_espionne();
    void test_espionne_2();
    void test_a_ete_espionne();
    void test_set_mine();
    void test_explose();
    void test_explose_adversaire();
    void test_passe_un_tour();
    void test_passe_un_tour_2();
    void test_affiche_explosion();
};

#endif
