#include "alist.h"

AList::AList() :
  _size(0), _cap(10) {
  _data = new std::string[_cap];
}

AList::~AList()  {
  delete [] _data;
}

bool AList::empty() const {
  return _size==0;
}

int AList::size() const {
  return _size;
}

void AList::insert (const std::string val) {
  if(_size+1 > _cap){
    resize();
  }
  int position = _size;
  for(int i=_size-1; i >= position; --i){
    _data[i+1] = _data[i];
  }
  _data[position] = val;
  _size++;
}

std::string& AList::get (int position) {
  // Will this throw an error?
  return _data[position];
}

void AList::resize() {
  std::string* temp = new std::string[2*_cap];
  for(int i=0; i < _size; i++){
    temp[i] = _data[i];
  }
  _cap *= 2;
  delete [] _data;
  _data = temp;
}
