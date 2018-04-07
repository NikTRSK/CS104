Node* merge (Node*& first, Node*& second) {
	Node* finalList = NULL;

	// base cases. If we reach end of any list append the second and end
	if (first == NULL) return second;
	if (second == NULL) return first;
	
	if (first->value < second->value) {
		finalList = first;
		finalList->next = merge(first->next, second);
	}
	else {
		finalList = second;
		finalList->next = merge(second->next, first);
	}

	first = NULL;
	second = NULL;
	return finalList;
}