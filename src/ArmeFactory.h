#ifndef ARME_FACTORY_H
#define ARME_FACTORY_H

#include <map>

#include "IArme.h"

class ArmeFactory {
  public:
    ArmeFactory();
    ~ArmeFactory();
    IArme* creer_arme(ARME arme);
    IArme* creer_arme(std::string nom_arme);

  private:
    std::map<ARME, IArme*> map_arme;
    std::map<std::string, IArme*> map_string;
};

#endif
