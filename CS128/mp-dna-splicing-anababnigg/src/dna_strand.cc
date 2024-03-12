#include "dna_strand.hpp"

#include <stdexcept>


// >> DRIVER FUNCTIONS <<
// (DRIVER) Travel
Node* DNAstrand::Travel(int dist) {
  Node* current = head_;
  for (int i = 0; i < dist; i++) {
    current = current->next;
  }
  return current;
}

// (DRIVER) NodeSetter
void DNAstrand::NodeSetter(Node* head, Node* tail) {
  head_ = head;
  tail_ = tail;
}


// CONSTRUCTOR and DESTRUCTOR
// >> DESTRUCTOR <<
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}

// >> HELPERS <<
// (HELPER) Match
bool DNAstrand::Match(const char* pattern, Node* current) {
  int index = 0;
  while (current != nullptr && pattern[index] != '\0') {
    if (current->next == nullptr && pattern[index + 1] != '\0') {
      return false;
    }
    if (current->data != pattern[index]) {
      return false;
    }
    index++;
    current = current->next;
  }
  return true;
}

// (HELPER) Editor
void DNAstrand::Editor(const char* pattern,
                       DNAstrand& to_splice_in,
                       unsigned int index) {
  Node* current = head_;
  Node* prev = current;
  for (unsigned int counter = 0; counter < index; counter++) {
    prev = current;
    current = current->next;
  }
  int counter = index;
  if (prev == current) {
    head_ = to_splice_in.head_;
  }

  while (current != nullptr && pattern[counter - index] != '\0' &&
         current != tail_) {
          counter++;
    Node* next_node = current->next;
    delete current;
    current = next_node;
  }
  if (current != nullptr) {
    to_splice_in.tail_->next = current;
  } 
  current = nullptr;
  delete current;
  if(head_ != to_splice_in.head_) {prev->next = to_splice_in.head_;}
  /*
  if (prev != nullptr) {prev->next = to_splice_in.head_;}
  else {head_ = to_splice_in.head_;}
  */
  // clear
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}

// >> MAIN FUNCTIONS <<
// (MAIN) SpliceIn
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  // check for any exceptions (any input empty)
  if (pattern == nullptr || head_ == nullptr || &to_splice_in == this) {
    return;
  }
  // variables
  Node* current = head_;
  int loc = -1;
  int counter = 0;

  // loop
  while (current != nullptr) {
      if (Match(pattern, current)) {
        loc = counter;
      }

    current = current->next;
    counter++;
  }

  if (loc == -1) {
    throw std::runtime_error("pattern not found.");
  }

  Editor(pattern, to_splice_in, loc);

  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}
