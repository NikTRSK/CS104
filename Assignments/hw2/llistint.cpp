#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
  // special case: empty list
  if (empty() && loc == 0) { 
    Item* newItem = new Item;
    newItem->val = val;
    head_ = newItem;
    tail_ = newItem;

    newItem->next = NULL;
    newItem->prev = NULL;

    size_++;
  }
  // special case: insert at head
  else if (loc == 0 && !empty()) {
    Item* newItem = new Item;
    newItem->val = val;

    head_->prev = newItem;
    newItem->next = head_;
    newItem->prev = NULL;
    head_ = newItem;

    size_++;
  }
  // special case: item is at the end of list
  else if (size() == loc) {
    Item* newItem = new Item;
    newItem->val = val;

    tail_->next = newItem;
    newItem->prev = tail_;
    newItem->next = NULL;
    tail_ = newItem;

    size_++;
  }
  else if (loc < size() && loc >= 0) {
    Item* newItem = new Item;
    newItem->val = val;

    Item* temp = getNodeAt(loc);
    newItem->next = temp;
    newItem->prev = temp->prev;

    temp->prev->next = newItem;
    temp->prev = newItem;

    size_++;
  }
  else
    return;
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  // base case
  if (loc < 0 || loc >= size_ || empty())
    return;
  // special case: only 1 item in list
  else if (size() == 1) {
    delete head_;
    head_ = NULL;
    tail_ = NULL;

    size_--;
  }
  // special case: deleting at head
  else if (loc == 0) {
    Item* toDelete = head_->next;
    toDelete->prev = NULL;
    delete head_;
    head_ = toDelete;

    size_--;
  }
  // special case: deleting at tail
  else if (loc == size()-1) {
    Item* toDelete = tail_->prev;
    toDelete->next = NULL;
    delete tail_;
    tail_ = toDelete;

    size_--;
  }
  else {
    Item* toDelete = getNodeAt(loc);
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;

    delete toDelete;

    size_--;
  }
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
  if(loc < 0 || loc >= size_)
    throw std::invalid_argument("bad location");
  else {
    Item *temp = head_;
    for (int cnt = 0; cnt < loc; cnt++)
      temp = temp->next;
    return temp;
  }
}
