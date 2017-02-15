#include "ArmeFactory.h"
#include "M4A1.h"
#include "SG_553.h"
#include "Gatling.h"
#include "Awp.h"
#include "Lance_Grenade.h"
#include "Pose_Mines.h"
#include "Bombe_EM.h"
#include "Radar.h"

ArmeFactory::ArmeFactory() {
  this->map_arme[M4A1] = new M4a1();
  this->map_arme[SG_553] = new SG553();
  this->map_arme[GATLING] = new Gatling();
  this->map_arme[AWP] = new Awp();
  this->map_arme[LANCE_GRENADE] = new Lance_Grenade();
  this->map_arme[POSE_MINES] = new Pose_Mines();
  this->map_arme[BOMBE_EM] = new Bombe_EM();
  this->map_arme[RADAR] = new Radar();

  this->map_string["M4A1"] = new M4a1();
  this->map_string["SG_553"] = new SG553();
  this->map_string["GATLING"] = new Gatling();
  this->map_string["AWP"] = new Awp();
  this->map_string["LANCE_GRENADE"] = new Lance_Grenade();
  this->map_string["POSE_MINES"] = new Pose_Mines();
  this->map_string["BOMBE_EM"] = new Bombe_EM();
  this->map_string["RADAR"] = new Radar();
}


ArmeFactory::~ArmeFactory() {
  this->map_arme[M4A1]->~IArme();
  this->map_arme[SG_553]->~IArme();
  this->map_arme[GATLING]->~IArme();
  this->map_arme[AWP]->~IArme();
  this->map_arme[LANCE_GRENADE]->~IArme();
  this->map_arme[POSE_MINES]->~IArme();
  this->map_arme[BOMBE_EM]->~IArme();
  this->map_arme[RADAR]->~IArme();

  this->map_string["M4A1"]->~IArme();
  this->map_string["SG_553"]->~IArme();
  this->map_string["GATLING"]->~IArme();
  this->map_string["AWP"]->~IArme();
  this->map_string["LANCE_GRENADE"]->~IArme();
  this->map_string["POSE_MINES"]->~IArme();
  this->map_string["BOMBE_EM"]->~IArme();
  this->map_string["RADAR"]->~IArme();
}

IArme* ArmeFactory::creer_arme(ARME arme) {
  // On vérifie en premier l'entré
  if( arme != M4A1 &&
      arme != SG_553 &&
      arme != GATLING &&
      arme != AWP &&
      arme != LANCE_GRENADE &&
      arme != POSE_MINES &&
      arme != BOMBE_EM &&
      arme != RADAR
    )
    throw std::invalid_argument("On ne peut pas creer une arme non référençée (Arme factory arme)");

  // Puis on renvoie un pointeur vers l'arme qui va bien
  IArme* tmp = map_arme[arme];
  return tmp;
}


IArme* ArmeFactory::creer_arme(std::string nom_arme) {
  // On vérifie en premier l'entré
  if( nom_arme != "M4A1" &&
      nom_arme != "SG_553" &&
      nom_arme != "GATLING" &&
      nom_arme != "AWP" &&
      nom_arme != "LANCE_GRENADE" &&
      nom_arme != "POSE_MINES" &&
      nom_arme != "BOMBE_EM" &&
      nom_arme != "RADAR"
    )
    throw std::invalid_argument("On ne peut pas creer une arme non référençée (Arme factory string)");

  // Puis on renvoie un pointeur vers l'arme qui va bien
  IArme* tmp = map_string[nom_arme];
  return tmp;
}
