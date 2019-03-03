#pragma once

using namespace std;

template <class T>
struct generic_node {
	T data;

	struct generic_node *next = NULL;
	struct generic_node *prev = NULL;
};

template <class T>
class DoubleLinkedList {

private:

	generic_node<T> *head, *tail;

public:

	DoubleLinkedList<T>() {
		head = NULL;
		tail = NULL;
	};

	bool isEmpty();
	void display();
	void append(T value);
};

template <class T>
void DoubleLinkedList<T>::display() {

	generic_node<T> *display_node = new generic_node<T>;
	display_node = head;

	while (display_node != NULL) {
		std::cout << display_node->data << "\t";
		display_node = display_node->next;
	}
}

template <class T>
bool DoubleLinkedList<T>::isEmpty() {

	// if head is null, there are no items in the list and it is empty so return true.  
	if (head == NULL) {
		return true;
	}
	else {
		// if head is not null, there are items in the list and it is not empty so return false.  
		return false;
	}
};

template <class T>
void DoubleLinkedList<T>::append(T value) {

	generic_node<T> *new_node = new generic_node<T>;
	new_node->data = value;

	if (head == NULL) {
		// If head is null then list doesn't have any nodes, set head and tail to new node value. 
		head = new_node;
		tail = new_node;
		new_node = NULL;
	}
	else {
		// else set current tail to be previous node on chain before new_node then set current tail next value to new_node
		// finally we set tail to be new node value and discard new_node by setting null. 
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
		new_node = NULL;
	}
}
