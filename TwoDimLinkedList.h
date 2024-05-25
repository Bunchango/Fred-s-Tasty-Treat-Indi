#ifndef TWO_DIMENSIONAL_LINKEDLIST_H
#define TWO_DIMENSIONAL_LINKEDLIST_H

#include "LinkedList.h"
#include <vector>

class TwoDimLinkedList {
public:
  TwoDimLinkedList();
  ~TwoDimLinkedList();

  /*
   * Add a new LinkedList to this list
   */
  void append(LinkedList *list);

  /*
   * Get the first element of the TwoDimLinkedList (or the head)
   */
  LinkedList *getFirst();

  /*
   * Get an element of the LinkedList by the category of the element
   */
  LinkedList *getByCat(std::string cat);

  /*
   * Get a food item of the LinkedList given an id
   */
  Node *getById(std::string id);

  /*
   * Add a new food item to corresponding LinkedList with the designated
   * category
   */
  void appendNode(std::string cat, Node *node);

  /*
   * Remove a Node using its id
   */
  void remove(std::string id);

  /*
   * Get the next available id in the system
   */
  int getNextId();

private:
  LinkedList *head;
  unsigned count;
};

#endif // !TWO_DIMENSIONAL_LINKEDLIST_H
