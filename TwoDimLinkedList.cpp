#include "TwoDimLinkedList.h"
#include "LinkedList.h"
#include <string>

TwoDimLinkedList::TwoDimLinkedList() {
  this->head = nullptr;
  this->count = 0;
}

TwoDimLinkedList::~TwoDimLinkedList() {
  // Deallocate all LinkedList within the Two dimension linked list
  while (head != nullptr) {
    LinkedList *temp = this->head;
    this->head = this->head->next;
    delete temp;
  }
}

void TwoDimLinkedList::append(LinkedList *list) {
  // Traverse to the end of the 2 dim linked list
  if (!this->head) {
    this->head = list;
  } else {
    LinkedList *current = this->head;
    while (current->next) {
      current = current->next;
    }
    current->next = list;
  }
  this->count++;
}

LinkedList *TwoDimLinkedList::getFirst() { return this->head; }

LinkedList *TwoDimLinkedList::getByCat(std::string cat) {
  LinkedList *current = this->head;
  LinkedList *result = nullptr;
  while (current != nullptr) {
    // Use.compare() to compare std::string objects
    if (current->category.compare(cat) == 0) { // Corrected line
      result = current;
    }
    current = current->next;
  }
  return result;
}

Node *TwoDimLinkedList::getById(std::string id) {
  Node *result = nullptr;
  LinkedList *current = this->head;

  // Traverse the list
  while (current != nullptr) {
    Node *search = current->getById(id);
    if (search) {
      result = search;
    }

    current = current->next;
  }

  return result;
}

void TwoDimLinkedList::appendNode(std::string cat, Node *node) {
  // Find the LinkedList and append the new Node
  LinkedList *current = this->head;
  while (current != nullptr) {
    if (current->category == cat) {
      current->append(node);
    }

    current = current->next;
  }
}

void TwoDimLinkedList::remove(std::string id) {
  LinkedList *current = this->head;
  while (current != nullptr) {
    current->remove(id);
    current = current->next;
  }
}

int TwoDimLinkedList::getNextId() {
  int largestId = 0;
  LinkedList *currentCat = this->head;

  // Traverse until the end of the LinkedList
  while (currentCat != nullptr) {
    Node *current = currentCat->getFirst();

    while (current) {
      // Remove the first character F
      std::string numberStr = current->data->id.substr(1);
      // Convert the remaining to integer
      int number = std::stoi(numberStr);

      if (number > largestId) {
        largestId = number;
      }

      current = current->next;
    }
    currentCat = currentCat->next;
  }

  return largestId + 1;
}
