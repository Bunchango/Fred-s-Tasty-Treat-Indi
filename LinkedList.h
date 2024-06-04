#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <vector>

#define MAX_CAT_LEN 40

class LinkedList {
public:
  // Pointer to the next LinkedList
  LinkedList *next;
  // A special category of items
  std::string category;

  LinkedList();
  ~LinkedList();

  // Add a new Node at the back
  void append(Node *node);

  void remove(std::string id);

  // Get Node
  Node *getFirst();
  Node *getById(std::string id);

  // Utility methods
  bool isEmpty();
  int size();
  // Get the next Id of all the Nodes in the LinkedList
  int getNextId();

  // Get all prices
  std::vector<float> getPrices();

  // Sort the LinkedList by alphabetical order
  void sortByAlpha();

  // Check if category is in correct forrmat
  static bool isValidCategory(std::string cat);

private:
  // the beginning of the list
  Node *head;
  // The end of the list
  Node *end;

  // how many nodes are there in the list?
  unsigned count;
};

#endif // LINKEDLIST_H
