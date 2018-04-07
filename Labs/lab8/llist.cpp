#include "llistint.h"

LList::LList() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LList::LList(const LList& other) {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  Item* temp = other.head_;
  while(temp){
    push_back(temp->val);
    temp = temp->next;
  }
}

LList& LList::operator=(const LList& other) {
  if(this == &other){
    return *this;
  }
  clear();
  Item* temp = other.head_;
  while(temp){
    push_back(temp->val);
    temp = temp->next;
  }
  return *this;
}


LList::~LList() {
  clear();
}

int LList::size() const {
  return size_;
}

bool LList::empty() const {
  return size_ == 0;
}

void LList::push_back(const int& val) {
  if(head_ == NULL){
    head_ = new Item;
    head_->val = val;
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
    size_ = 1;
  }
  else {
    Item* n = new Item;
    n->val = val;
    n->next = NULL;
    n->prev = tail_;
    tail_->next = n;
    tail_ = n;
    size_++;
  }
}

int& LList::get(int loc) {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LList::get(int loc) const {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LList::clear() {
  while(head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

Item* LList::getNodeAt(int loc) const {
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}


