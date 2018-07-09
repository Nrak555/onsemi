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
		~list() {

		}
		void push(T data) {
			node<T> *n_ptr = new node<T>(data);

			if (tail == nullptr && head == nullptr) {	//list is empty 
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
		node* slice(int num1, int num2) {
			int j = num1;
			int k = num2;
			node<T>* NodeS = head;	// Start node and End node
			node<T>* NodeE;

			if (num2 < num1) {					
				std::cout << "Invaild slice";
				return nullptr;
			}

			if (num2 > size)		// If asking for a slice Greater then array of elements bound it to last element
				k = size;

			for (int i = 0; i < j; i++)		//Find Starting node
				NodeS = NodeS->get_next;

			NodeE = NodeS;				// NodeE is after NodeS

			for (int i = j; i < k; i++)	//Find Ending Node
				NodeE = NodeE->get_next;

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

			size = size - (k - j);

			return NodeS;

		}
		void mergesort() {}
		void reverse_mergesort() {}

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
	list<int> *l = new list<int>();
	
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
	std::cout << "\n" << l->get_size();
	std::cin >> temp;

	return 0;


}