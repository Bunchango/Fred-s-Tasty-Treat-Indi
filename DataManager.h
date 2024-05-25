#ifndef MANAGER_H
#define MANAGER_H

#include "Balance.h"
#include "TwoDimLinkedList.h"
#include <fstream>

#define EMPTY_SPACE " "
#define SEPARATOR "|"
// Representing the number of separators to display the meals and balance
#define SEPARATOR_NUM 2
#define MONEY_SYMBOL "$"
#define DENOM_LENGTH 7
// The extra padding of LINEs
#define EXCESS_LINE 4
#define LINE "-"
#define DEFAULT_QUANTITY_LENGTH 9
// This is for dynamically printing out the values of balance
#define DEFAULT_VALUE_LENGTH 6

// Indicators in the first line of files to determine the format of the file
#define NEW_FORMAT_INDICATOR "#newformat"
#define NEW_FORMAT_PARAM_NUM 5
#define DEFAULT_FORMAT_PARAM_NUM 4

class DataManager {
private:
  /*
   * Read the default format
   */
  void readDefaultFormat(std::ifstream &mealFile);

  /*
   * Read the new format
   */
  void readNewFormat(std::ifstream &mealFile);

public:
  /*
   * Read the money data file and meal data file into meals and balance
   * This method assumes mealFile and moneyFile are valid
   */
  TwoDimLinkedList *meals;
  Balance *balance;
  // Hold the name of the files so we can save it
  std::string mealFile;
  std::string moneyFile;

  DataManager(std::string mealFileName, std::string moneyFileName);
  ~DataManager();

  /*
   * Save all data to data files depending on format
   */
  void save();
};

#endif // !MANAGER_H
