/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1 - IP
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1 - IP
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1 - IP
  return List<T>::ListIterator(tail_->next); // is it null or this->tail_ or tail_->next?
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1 - IP
  ListNode* curr = head_;
  ListNode* next = NULL;

  while (curr != NULL) {
    next = curr->next;
    delete curr;
    curr = next;
  }

  //need to set both created listnode objects to NULL as well? [error?]
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1 
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_) {head_ -> prev = newNode;}
  if (!tail_) {tail_ = newNode;}
  
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_) {tail_->next = newNode;} 
  else {head_ = newNode;} // if list in empty

  // update so it points to tail_
  tail_ = newNode; //need to update?
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  /* -- edge cases --
  > splitting when splitpoint 0 -> return whole list
  > splitting when given list is null -> return null (X)
  > splitting when splitpoint > list.size()
  > position of the list iterator be zero indexed? what
  > length = 0 -> return NULL (X)
  > splitpoint < 0 -> splitpoint = 0; (X)
  */
  if (splitPoint < 0) {splitPoint = 0;}
  if (splitPoint == 0) {return start;}
  if (start == NULL || length_ == 0) {return NULL;}
  for (int i = 0; i < splitPoint - 1; i++) { //changed to &&
    if (start) {start = start->next;} //if not null, iterate
    else {return NULL;}
  }

  // disconnect and return next node
  if (start) {
      ListNode* temp = start->next;
      if(temp) {temp->prev = NULL;}
      start->next = NULL;
      return temp;
  }

  return NULL; 
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (!head_ || !head_->next) {return;} //empty list or one node, return

  ListNode* curr = head_->next; // as function keeps first node same
  ListNode* meow; // next node (to save while moved)

  //two steps forward for each node that is moved to end
  while(curr && curr != tail_) {
    meow = curr->next;

    //revmoving
    if(curr->prev) {curr->prev->next = curr->next;}
    if(curr->next) {curr->next->prev = curr->prev;}

    // append to end and move
    tail_->next = curr;
    curr->prev = tail_;
    curr->next = NULL;
    tail_ = curr;
    curr = meow->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  // kinda looked at several common algorithms and applied to this function
  if (startPoint == endPoint) {return;}

  ListNode* curr = startPoint;
  ListNode* meow;

  while (curr != endPoint->next) {
    //switch
    meow = curr->next;
    curr->next = curr->prev;
    curr->prev = meow;

    if(meow == endPoint) {
      endPoint = startPoint;
      startPoint = meow;
    }
    curr = meow;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(head_ == NULL || n == 0) {return;}
  if(n >= length_) {return reverse();}

  ListNode* startPoint = head_;
  ListNode* curr = head_;
  ListNode* next;

  while(curr) {
    next = NULL;
    for (int i = 0; i < n && (curr); i++) {
      if (i == n - 1 || curr->next == NULL) {
        next = curr->next;
        reverse(startPoint, curr);
        startPoint = next;
      }
      curr = next;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  if (!first && !second) {return NULL;}
  if (!first) {return second;}
  if (!second) {return first;}

  ListNode* merge_head;
  ListNode* curr = head_;

  // where does the head begin?
  if (first->data < second->data) {
    merge_head = first;
    first = first->next;
  } else {
    merge_head = second;
    second = second->next;
  }

  // sift through nodes to merge in order
  while (first && second) {
    if (first->data < second->data) {
      curr->next = first;
      first->prev = curr;
      first = first->next;
    } else {
      curr->next = second;
      second->prev = curr;
      second = second->next;
    }
    curr = curr->next;
  }

  // handle leftover nodes
  if (first) {
    curr->next = first;
    first->prev = curr;
  } else {
    curr->next = second;
    second->prev = curr;
  }

  return merge_head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  // researched general algorithm based on guidelines
  if (start == NULL) {return NULL;}
  if (chainLength == 0 || start->next == NULL) {return start;}

  // split into manageable parts and get midnode to middle
  int half = (int)(chainLength / 2);
  ListNode* mid_node = start;
  for (int i = 0; i < half; i++) {
    mid_node = mid_node->next;
  }

  ListNode* temp = mid_node->next;
  mid_node->next = NULL;

  // recursively sort
  ListNode* first = mergesort(start, half);
  ListNode* second = mergesort(temp, chainLength - half);

  // merge sorted halves
  return merge(first, second);
}
