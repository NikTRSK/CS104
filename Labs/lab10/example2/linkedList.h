#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T> 
struct Node {
	T val;
	Node<T>* next;
};

template<class T>
class LinkedList {
	private:	
		Node<T>* head;
		int size;
	public:
		LinkedList();
		~LinkedList();
		void add(T nextVal);
		T get(int index);
};

template<class T>
LinkedList<T>::LinkedList() {
	head = NULL;
	size = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
	Node<T>* deleteNode = head;
	while(deleteNode != NULL) {
		Node<T>* temp = deleteNode;
		deleteNode = deleteNode->next;
		delete temp;
	}
}

template<class T>
void LinkedList<T>::add(T nextVal) {
	Node<T>* nextItem = new Node<T>;
	nextItem->val = nextVal;
	nextItem->next = head;
	head = nextItem;
	size++;
}

template<class T>
T LinkedList<T>::get(int index) {
	Node<T>* curr = head;
	for(int i = 0; i < index; i++) {
		curr = curr->next;
	}
	return curr->val;
}

#endif
