#include "DataManager.h"
#include "Coin.h"
#include "Helper.h"
#include "LinkedList.h"
#include "Node.h"
#include "TwoDimLinkedList.h"
#include <fstream>
#include <string>
#include <vector>

void DataManager::readDefaultFormat(std::ifstream &mealFile) {
  // For the default format, there will be only 1 LinkedList in the 2d
  // LinkedList without any category
  LinkedList *list = new LinkedList();
  this->meals->append(list);

  std::string line;
  // Read the files
  while (std::getline(mealFile, line)) {
    // Process each line: Create a new FoodItem, assign it to a Node, then add
    // that Node to LinkedList
    std::vector<std::string> tokens = {};
    std::vector<std::string> prices = {};
    Helper::splitString(line, tokens, "|");

    if (tokens.size() == DEFAULT_FORMAT_PARAM_NUM &&
        tokens[1].size() <= NAMELEN && tokens[2].size() <= DESCLEN &&
        FoodItem::isValidIdFormat(tokens[0]) &&
        Price::isValidPrice(tokens[3]) && !this->meals->getById(tokens[0])) {
      // Slit the price into its integer and fractional part to create Price
      // object
      Helper::splitString(Helper::floatToString(std::stof(tokens[3]), 2),
                          prices, ".");
      Price price = Price();
      price.dollars = std::stoi(prices[0]);
      price.cents = std::stoi(prices[1]);

      // Create FoodItem object
      FoodItem *item = new FoodItem(tokens[0], tokens[1], tokens[2], price);

      // Create node
      Node *node = new Node();
      node->data = item;

      list->append(node);
    }
  }
}

void DataManager::readNewFormat(std::ifstream &mealFile) {
  std::string line;
  // Read the files
  while (std::getline(mealFile, line)) {
    // Process each line: Create a new FoodItem, assign it to a Node, then add
    // that Node to LinkedList
    std::vector<std::string> tokens = {};
    std::vector<std::string> prices = {};
    Helper::splitString(line, tokens, "|");

    if (tokens.size() == NEW_FORMAT_PARAM_NUM && tokens[1].size() <= NAMELEN &&
        tokens[2].size() <= DESCLEN && FoodItem::isValidIdFormat(tokens[0]) &&
        Price::isValidPrice(tokens[3]) && !this->meals->getById(tokens[0]) &&
        tokens[4].size() <= MAX_CAT_LEN && !tokens[4].empty()) {
      // If the category has not exist, then we create a new one and append it
      if (!this->meals->getByCat(tokens[4])) {
        LinkedList *newCat = new LinkedList();
        newCat->category = tokens[4];
        this->meals->append(newCat);
      }

      // Slit the price into its integer and fractional part to create Price
      // object
      Helper::splitString(Helper::floatToString(std::stof(tokens[3]), 2),
                          prices, ".");
      Price price = Price();
      price.dollars = std::stoi(prices[0]);
      price.cents = std::stoi(prices[1]);

      // Create FoodItem object
      FoodItem *item = new FoodItem(tokens[0], tokens[1], tokens[2], price);

      // Create node
      Node *node = new Node();
      node->data = item;

      // Add the node to the meals
      this->meals->appendNode(tokens[4], node);
    }
  }
}

DataManager::DataManager(std::string mealFileName, std::string moneyFileName) {
  // Create an empty LinkedList and balance
  this->meals = new TwoDimLinkedList();
  this->balance = new Balance();

  this->mealFile = mealFileName;
  this->moneyFile = moneyFileName;

  std::ifstream mealFile(mealFileName);
  std::ifstream moneyFile(moneyFileName);

  // Determine the format of meals and read file
  std::string line;
  if (std::getline(mealFile, line)) {
    if (line == NEW_FORMAT_INDICATOR && !line.empty()) {
      this->readNewFormat(mealFile);
    } else if (line != NEW_FORMAT_INDICATOR && !line.empty()) {
      this->readDefaultFormat(mealFile);
    }
  }

  while (std::getline(moneyFile, line)) {
    // Process each line: Split by "." and create Coin objects
    std::vector<std::string> tokens = {};
    Helper::splitString(line, tokens, DELIM);

    if (tokens.size() == 2 && Helper::isNumber(tokens[0]) &&
        Helper::isNumber(tokens[1]) && Coin::isDenomination(tokens[0]) &&
        Helper::isValidInteger(tokens[1])) {
      Coin coin = Coin();
      coin.denom = Coin::intToDenomination(std::stoi(tokens[0]));
      coin.count = std::stoi(tokens[1]);
      // Insert coin to Balance
      this->balance->insert(coin);
    }
  }

  // Close the files
  mealFile.close();
  moneyFile.close();
}

// Save the file
void DataManager::save() {
  std::ofstream mealFile(this->mealFile);
  std::ofstream coinFile(this->moneyFile);

  if (!mealFile.is_open()) {
    std::cerr << "Failed to open file: " << this->mealFile << std::endl;
    return;
  }

  // Loop through all the LinkedList inside the 2d LinkedList
  std::string line;
  LinkedList *currentCat = this->meals->getFirst();

  // Check the format and add format indicator to the file
  if (currentCat != nullptr && !currentCat->category.empty()) {
    mealFile << NEW_FORMAT_INDICATOR << "\n";
  }

  while (currentCat) {
    Node *current = currentCat->getFirst();

    while (current) {
      mealFile << current->data->id << SEPARATOR << current->data->name
               << SEPARATOR << current->data->description << SEPARATOR
               << Helper::floatToString(current->data->price.value(), 2);

      if (!currentCat->category.empty()) {
        mealFile << SEPARATOR << currentCat->category;
      }
      mealFile << "\n";
      current = current->next;
    }
    currentCat = currentCat->next;
  }

  for (Coin coin : this->balance->balance) {
    coinFile << coin.denom << DELIM << coin.count << "\n";
  }

  mealFile.close();
  coinFile.close();
};

DataManager::~DataManager() {
  delete this->meals;
  delete this->balance;
}
