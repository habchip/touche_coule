#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>

#include "Grille.h"


int main( int argc, char* argv[] ) {

#if TEST != 0
  // On commence par vérifier que la constante TEST n'est pas à 1
  // Sinon les tests de la grille ne passerons pas
  std::cout << std::endl << "Attention :" << std::endl;
  std::cout << "La constante TEST doit être égal à 0 dans le fichier source Grille.h" << std::endl << std::endl;
  return 0;
#endif

  std::string testPath = (argc > 1) ? std::string(argv[1]) : std::string("");

  // Create the event manager and test controller
  CppUnit::TestResult controller;

  // Add a listener that colllects test result
  CppUnit::TestResultCollector result;
  controller.addListener( &result );

  // Add the top suite to the test runner
  CppUnit::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

  try {
    std::cout << "************************************************" << std::endl;
    std::cout << "**** Début des tests" << std::endl;
    std::cout << "************************************************" << std::endl << std::endl;

    // On redirige la sortie standard vers le fichier log.tu
    // afin de ne pas surcharger inutilement le terminal
    std::ofstream Out("log.tu");
    std::streambuf* OldBuf = std::cout.rdbuf();
    std::cout.rdbuf(Out.rdbuf());

    // On lance les tests
    runner.run( controller, testPath );

    // On remet la sortie standard vers le terminal
    std::cout.rdbuf(OldBuf);

    // Print test in a compiler compatible format.
    CppUnit::CompilerOutputter outputter( &result, CppUnit::stdCOut() );
    outputter.write(); 


    std::cout << std::endl << "************************************************" << std::endl;
    std::cout << "**** Fin des tests" << std::endl;
    std::cout << "************************************************" << std::endl;
  } catch ( std::exception const& e ) {
    std::cerr << "ERROR : " << e.what() << std::endl;
  }

  return 0;
}
