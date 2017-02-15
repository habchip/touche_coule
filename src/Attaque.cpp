#include <stdexcept>

#include "Attaque.h"

std::string to_string_attaque(Attaque a) {
  switch(a) {
    case ALO:
      return "ALO";
    case TOUCHE:
      return "TOUCHE";
    case COULE:
      return "COULE";
    default:
      return "VOID";
  }
  throw std::invalid_argument("Wrong attaque to string");
}


Attaque conv_to_attaque(std::string s) {
  if(s.compare("ALO") == 0)
    return ALO;
  if(s.compare("TOUCHE") == 0)
    return TOUCHE;
  if(s.compare("COULE") == 0)
    return COULE;
  if(s.compare("VOID") == 0)
    return UNDEFINED_ATK;
  throw std::invalid_argument("Bad string to convert to attaque " + s);
}
