// TODO(1): Copy the contents of llist.cpp here, below the class definition

// TODO(2): Template the item
struct Item {
  int val;
  Item *prev;
  Item *next;
};


// TODO(3): Template the class, as well as all the functions inside it
// Change all mentions of int to the templated type name

class LList {
 public:
  LList();
  LList(const LList& other);
  LList& operator=(const LList& other);
  ~LList();

  // TODO(5): Change the signatures of these methods appropriately
  int size() const;
  bool empty() const;
  void push_back(const int& val);
  int& get(int pos);
  int const & get(int pos) const;
  void clear();

 private:
  Item* getNodeAt(int pos) const;
  
  // TODO(4): What types should these data members me?
  Item* head_;
  Item* tail_;
  int size_;
};

