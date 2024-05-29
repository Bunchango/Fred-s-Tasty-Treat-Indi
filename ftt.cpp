#include "Machine.h"
#include "iostream"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

int main(int argc, char **argv) {
  // Read arguments into an array of strings
  // bools to toggle enhancements
  bool useDoubly = true;
  bool useTwoD = true;
  bool useColour = true;

  if (argc <= 7 && argc >= 3) {
    std::string strArgs[5];
    for (int i = 0; i < argc; i++) {
      std::string strArg(argv[i]);
      strArgs[i] = strArg;

      // Check if the user want the enhancements

      if (strArg == "-no2DLL") {
        useTwoD = false;
      } else if (strArg == "-noColour") {
        useColour = false;
      }
    }

    Machine *machine = new Machine(strArgs[1], strArgs[2], useTwoD, useColour);
    machine->start();
    delete machine;
  } else {
    std::cout << "Invalid arguments" << "\n";
  }

  return EXIT_SUCCESS;
}
