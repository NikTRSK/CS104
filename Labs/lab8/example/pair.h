template <class FirstType, class SecondType>
class Pair {
public:
	Pair(FirstType f, SecondType s);

	FirstType getFirst();
	SecondType getSecond();

private:
	FirstType first;
	SecondType second;
};

template <class FirstType, class SecondType>
Pair<FirstType, SecondType>::Pair(FirstType f, SecondType s)
		: first(f), second(s) {
}

template <class FirstType, class SecondType>
FirstType Pair<FirstType, SecondType>::getFirst() {
	return first;
}

template <class FirstType, class SecondType>
SecondType Pair<FirstType, SecondType>::getSecond() {
	return second;	
}
