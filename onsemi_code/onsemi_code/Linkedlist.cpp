#include "stdafx.h"
#include <ostream>
#include <iostream>

template<class T> class node
{
	private:
		T data;
		node<T>* next;
		node<T>* last;

	public:
		node(T d) {
			data = d;
			next = nullptr;
			last = nullptr;
		}
		node(T d, node* n) {
			data = d;
			next = n;
			last = nullptr;
		}
		node(T d, node* n, node* l) {
			data = d;
			next = n;
			last = l;
		}

		~node()  {}

		node<T>* get_next() {
			return next;
		}

		node<T>* get_last() {
			return last;
		}

		T get_data() {
			return data;
		}

		void set_next(node* n) {
			next = n;
		}

		void set_last(node* n) {
			last = n;
		}

		void set_data(T d) {
			data = d;
		}
};

template <class T> class list
{
	private:
		int size;
		node<T>* head;
		node<T>* tail;

	public:
		list<T>() {
			size = 0;
			head = nullptr;
			tail = nullptr;

		}

		list<T>(node<T>* Node) {	// Takes a slice and converts it into a list.
			int i = 1;				//Should be garanteed one node
			node<T>* n = Node;
			if (n != nullptr) {	// check that they gave at least one node else defualt
				head = n;

				while (n->get_next()) {
					n = n->get_next();
					i++;
				}
				size = i;
				tail = n;
			}
			else {
				size = 0;
				head = nullptr;
				tail = nullptr;
			}
		}

		~list() {

		}
		void push(T data) {
			node<T> *n_ptr = new node<T>(data);

			if ((tail == nullptr) && (head == nullptr)) {	//list is empty 
				head = n_ptr;
				tail = n_ptr;
			}
			else {
				n_ptr->set_last(tail);
				tail->set_next(n_ptr);
				tail = n_ptr;
			}
			size++;
		}

		T pop() {
			T data_holder{};
			node<T>* ptr = nullptr;
			
			if (tail != nullptr) {	//Check if list is empty
				ptr = tail->get_last();			//get the new tail
				data_holder = tail->get_data();	//get data

				delete tail;					// delete old object
				tail = ptr;						// set new tail
				if (tail != nullptr)
					tail->set_next(nullptr);		// clear tail's next pointer
				size--;
			}

				if (ptr == nullptr)				//last item in the list set head to nullptr
					head = ptr;

			return data_holder;
		}

		void insert_at(T d,int num) {
			node<T>* ptr = head;

			if (num > size)		// If the insert is past the end of the list add to the end
				push(d);
			else {
				node<T>* n = new node<T>(d);		// Make new node to be inserted

				for (int i = 0; i < num; i++)			//Get pointer to new postion
					ptr = ptr->get_next();

				n->set_next(ptr);
				n->set_last(ptr->get_last());
				ptr->set_last(n);
				if (num != 0)							// inserting at the front of the list 
					n->get_last()->set_next(n);
				else
					head = n;
					

				size++;
			}
		}

		int search(T d) {
			node<T>* n = head;
			for (int i = 0; i < size; i++) {
				if (d == n->get_data())
					return i;				//found item
				n = n->get_next();
			}
			return -1;						//did not find item
		}

		node<T>* slice(int num1, int num2) {
			int j = num1;
			int k = num2;
			node<T>* NodeS = head;	// Start node and End node
			node<T>* NodeE;

			if ((num2 < num1) || (num1 > size)) {					
				std::cout << "Invaild slice";
				return nullptr;
			}

			if (num2 > size)		// If asking for a slice Greater then array of elements bound it to last element
				k = size;

			for (int i = 0; i < j; i++)		//Find Starting node
				NodeS = NodeS->get_next();

			NodeE = NodeS;				// NodeE is after NodeS

			for (int i = j; i < k; i++)	//Find Ending Node
				NodeE = NodeE->get_next();

			if(NodeS->get_last() != nullptr)	//Check if slice includes the beginning
				NodeS->get_last()->set_next(NodeE->get_next());
			else if (NodeE->get_next() != nullptr)	//Check if slice includes the end
					NodeE->get_next()->set_last(nullptr);
			
			
			if(NodeE->get_next() != nullptr)	//Check if slice includes the end
				NodeE->get_next()->set_last(NodeS->get_last());
			else if (NodeS->get_last() != nullptr)	//Check if slice includes the beginning
				NodeS->get_last()->set_next(nullptr);

			NodeS->set_last(nullptr);		//isolate the slice
			NodeE->set_next(nullptr);

			size = size - (k - j + 1);

			return NodeS;

		}
		void mergesort_start() {
			node<T>* temp;
			head = mergesort(head);
			temp = head;

			for (int i = 0; i < size; i++) {
				std::cout << "\n" << i << ":" << size;
				temp = temp->get_next();
			}
			tail = temp;
		}
		void reverse_mergesort_start() {
			node<T>* temp;
			head = Reverse_mergesort(head);
			temp = head;

			for (int i = 0; i < size; i++) {
				std::cout << "\n" << i << ":" << size;
				temp = temp->get_next();
			}
			tail = temp;
		}

		node<T>* mergesort(node<T>* h) {
			node<T>* first;
			node<T>*second;

			if ((h == nullptr) || (h->get_next() == nullptr))  // check for existince and trival case
				return h;

			second = split(h);

			first = mergesort(h);
			second = mergesort(second);

			return merge(h, second);
		}

		node<T>* Reverse_mergesort(node<T>* h) {
			node<T>* first;
			node<T>*second;

			if ((h == nullptr) || (h->get_next() == nullptr))  // check for existince and trival case
				return h;

			second = split(h);

			first = Reverse_mergesort(h);
			second = Reverse_mergesort(second);

			return reverse_merge(h, second);
		}
		

		node<T>* merge(node<T>* first, node<T>* second) {
			node<T>* ptr = first;

			if (first == nullptr) //If first list is empty	
				return second;

			if (second == nullptr)	//If second list is empty
				return first;

			//pick the smaller value
			if (first->get_data() < second->get_data()) {
				first->set_next(merge(first->get_next(), second));
				first->get_next()->set_last(first);
				first->set_last(nullptr);
				return first;
			}
			else {
				second->set_next(merge(first, second->get_next()));
				second->get_next()->set_last(second);
				second->set_last(nullptr);
				return second;
			}
		}

		node<T>* reverse_merge(node<T>* first, node<T>* second) {
			node<T>* ptr = first;

			if (first == nullptr)
				return second;

			if (second == nullptr)
				return first;

			//pick the larger value
			if (first->get_data() > second->get_data()) {
				first->set_next(reverse_merge(first->get_next(), second));
				first->get_next()->set_last(first);
				first->set_last(nullptr);
				return first;
			}
			else {
				second->set_next(reverse_merge(first, second->get_next()));
				second->get_next()->set_last(second);
				second->set_last(nullptr);
				return second;
			}
		}

		node<T>* split(node<T>* n) {	// split list into two half length bits
			node<T>* fast = n;
			node<T>* slow = n;
			node<T>* temp;

			while ((fast->get_next() == nullptr)  && (fast->get_next()->get_next() == nullptr)) {
				fast = fast->get_next()->get_next();
				slow = slow->get_next();
			}
			temp = slow->get_next();
			slow->set_next(nullptr);
			return temp;
		}

		int get_size() {
			return size;
		}


		friend std::ostream& operator<<(std::ostream& os,  list<T>& l)
		{
			node<T>* ptr = l.head;

			os << "\n\nContents of the List:\n";
			if (l.head == nullptr)
				return os << "List is empty";

			for (int i = 0; i < l.size; i++) {
				os << ptr->get_data() << ", ";
				if (i % 10 == 9)
					os << "\n";
				ptr = ptr->get_next();
			}
			return os << "\n";
		}

};

int main() {
	int temp;
	//node<int>* n;
	list<int> *l = new list<int>();
	list<int> *l2;
	
	l->push(5);
	l->push(3);
	l->push(6);
	l->push(1);
	l->push(2);
	l->push(4);
	l->push(0);
	l->push(8);
	l->push(7);
	l->push(9);
	l->push(10);

	std::cout << l->pop();

	l->pop();

	std::cout << *l;

	l->insert_at(11, 0);

	std::cout << l->search(11);

	std::cout << *l;
	std::cout << "\n size:" << l->get_size();

	l2 = new list<int>( l->slice(3, 5));

	std::cout << "\n size:" << l->get_size();
	std::cout << "\n size:" << l2->get_size();
	std::cout << *l;
	std::cout << *l2;
	
	l->mergesort_start();
	std::cout << *l;

	l->reverse_mergesort_start();
	std::cout << *l;

	std::cin >> temp;

	return 0;


}