/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <iostream>
/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
  //return   ListIterator(head_) : position_(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_-> next);
  //return   ListIterator(tail_) : position_(tail_);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1

  _destroy();

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* current = head_;
	while(current != NULL) {
		ListNode* prev;
		prev = current;
		current = current->next;
		delete prev;
	}
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
  /// @todo Graded in MP3.1
  length_ ++;
  ListNode *node = new ListNode(ndata);
if (head_ != NULL) {
    node -> next = head_;
    node -> prev = NULL;
    head_ -> prev = node;//change head previous, not head next
    head_ = node; // update head
  } else { // empty head, just insert

    node -> next = NULL;
    node -> prev = NULL;
    head_ = node;
    tail_ = node;

  }

  //node = NULL;   //delete node

return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  length_ ++;
  ListNode *node = new ListNode(ndata);
  if (tail_ != NULL) {
    node -> prev = tail_;
    node -> next = NULL;
    tail_ -> next = node;//change tail next, not tail previous
    tail_ = node; //update tail
  } else { // empty tail
    node -> next = NULL;
    node -> prev = NULL;
    tail_ = node;
    head_ = node;

  }

  //node = NULL; //delete node

  return;
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
  /// @todo Graded in MP3.1

if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) { return; }

if (startPoint == head_ && endPoint == tail_ ) { // the whole linkedlist
  ListNode *temp1 = endPoint;
  temp1 -> next = endPoint -> prev;
  ListNode *temp2 = startPoint;
  temp2 -> next = NULL;
  temp2 -> prev = startPoint -> next;

  endPoint = temp1; //new head, does not have a previous
  ListNode *originalEd = endPoint; // make a copy
  endPoint = endPoint -> prev;

  startPoint = temp2; // new tail, has a next
  ListNode *originalSt = startPoint; // make a copy

  while (endPoint != startPoint) {
    ListNode *temp = endPoint -> prev;
    endPoint -> prev = endPoint -> next;
    endPoint -> next = temp;
    endPoint = endPoint -> next; // update endPoint
  }
//endPoint has already been updated, now update startPoint
    startPoint = originalEd;
//update head and tail
    head_ = startPoint;
    tail_ = endPoint;
    return;

}  else {
    ListNode *originalSt = startPoint;
    ListNode *originalEd = endPoint;
    ListNode *insideL = startPoint -> next;
    ListNode *insideR = endPoint -> prev;

    endPoint = endPoint -> prev;
    while (endPoint != startPoint) {
      ListNode *temp = endPoint -> prev;
      endPoint -> prev = endPoint -> next;
      endPoint -> next = temp;
      endPoint = endPoint -> next;
    }

    if (head_ == originalSt) {
      ListNode * outsideR = originalEd -> next;

      endPoint -> next = outsideR;
      endPoint -> prev = insideL;

      ListNode * temp = originalEd;
      temp -> next = insideR;
      startPoint = temp;

      outsideR -> prev = endPoint;
      head_ = startPoint;
      return;

    } else if (tail_ == originalEd) {
      ListNode *outsideL = originalSt -> prev;

      endPoint -> next = NULL;
      endPoint -> prev = insideL;
      startPoint = originalEd;

      startPoint -> next = insideR;
      startPoint -> prev = outsideL;

      outsideL -> next = startPoint;
      tail_ = endPoint;
      return;

    } else {
      ListNode * outsideR = originalEd -> next;
      ListNode * outsideL = originalSt -> prev;

      endPoint -> next = outsideR;
      endPoint -> prev = insideL;
      startPoint = originalEd;
      startPoint -> next = insideR;
      startPoint -> prev = outsideR;
      outsideR -> prev = endPoint;
      outsideL -> next = startPoint;
      return;
    }

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
  /// @todo Graded in MP3.1
  //std::cout << "2333333333333333333" << std::endl;
  if (head_ == NULL) { return; }

  ListNode *s = head_;
  ListNode *e = head_;
  while (e -> next && s -> next) {
    e = s;
    for (int i = 0; i < n-1; i++) {
      if (e -> next) { e = e-> next;}
    }
    reverse(s,e);
    s = e -> next;
  }
return;
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
  /// @todo Graded in MP3.1
  if(head_ == NULL || head_->next == NULL) { return; }

	ListNode* tr = head_;
	ListNode* ho = tr -> next;
	while( tr -> next -> next ){ // track always to the tail
		tr = tr->next;
		tr->prev->next = tr->next;
		tr->next->prev = tr->prev;
		ho = tr->next;
		tail_->next = tr; // move track after the tail
		tr->prev = tail_;
		tr->next = NULL;
		tail_ = tr; // update tail
		tr = ho;
}

//return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if (start == NULL || splitPoint == 0) { return start; }

  ListNode * newHead = start;
  for (int i = 0; i < splitPoint; i++) {
    newHead = newHead -> next;
  }

  newHead -> prev -> next = NULL;
  newHead -> prev = NULL;

  return newHead;
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
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    //cout << "here121212121" << endl;
    while (tail_->next != NULL)
    //cout << "here3333334444" << endl;
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  /*
  if (chainLength == 1) {
    return start;
  }
  // split
  chainLength = chainLength / 2;
  ListNode * startRef = start;
  List<T> secondList = split(chainLength);

  while (startRef != NULL) {
    if (startRef -> data == secondList.head_ -> data) {
      break;
    }
    startRef = startRef -> next;
  }

  ListNode * first = mergesort(start, chainLength);
  ListNode * second = mergesort(startRef, chainLength);
  start = merge(first, second);
  return start;
  // mergesort recursion
  // merge
*/
if (length_ == 1) {
  return start;
}
List second = split(chainLength / 2); // the second half of the split list
start = mergesort(start, length_); //  sort the first half of the list. which was split into a half
second.head_ = second.mergesort(second.head_, second.length_); //  sort the second half of the list
this -> mergeWith(second); // merge the first half with the second half
return head_;

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
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first != NULL && second == NULL) {
    return first;
  }
  if (first == NULL && second != NULL) {
    return second;
  }

  ListNode* result = NULL;
  ListNode* resultHead = NULL; // want to return this
  //ListNode* originalFirst = first; // do not change
  //ListNode* originalSecond = second; // do not change

  if (first -> data < second -> data) {
  //cout << "here44444111111" << endl;
    result = first;
    resultHead = first;
    first = first -> next;
  } else {
  //  cout << "here4444422222" << endl;
    result = second;
    resultHead = second;
    second = second -> next;
  }

  while (first != NULL || second != NULL) {
   if (first == NULL || (second != NULL && (second -> data < first -> data))) { // F: 126 S:345
      result -> next = second;
      second  -> prev = result;
      result = result -> next;
      second = second -> next;

    } else {
      result -> next = first;
      first -> prev = result;
      result = result -> next;
      first =  first -> next;
    }
  }
// cout << "here44444" << endl;
// second = NULL;
// first = resultHead;
// head_ = resultHead;
  return resultHead;

/*
 if (first == NULL) { // F: 126 S: 345[789]
   result -> next = second;
   second -> prev = result;
   cout << "Second: " << second -> data << endl;
   cout << "here55555" << endl;
} else {
   result -> next = first;
   first -> prev = result;
    cout << "here66666" << endl;
}
   second = NULL;
   first = resultHead;
   head_ = resultHead;
   return first;
   */
}
