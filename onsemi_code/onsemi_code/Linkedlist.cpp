#include "stdafx.h"
#include <ostream>

template<class T> class node
{
	private:
		T data;
		node* next;
		node* last;

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

			node* get_next() {
			return next;
		}

		node* get_last() {
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
		list() {

		}
		~list() {

		}
		void push(T data) {
			node<T> n = new node<T>(data);
			node<T>* n_ptr = &n;

			n_ptr->set_last(tail);

			if (tail != nullptr && head != nullptr)	//Check if empty list
				tail->set_next(n_ptr);
			else
				head = n_ptr;		   //List was empty set head as well
			tail = n_ptr;
		}

		T pop() {
			T data_holder;
			node* ptr;
			
			ptr = tail->get_last();			//get the new tail

			data_holder = tail->get_data();	//get data

			delete tail;
			tail = ptr;						// set tail

			if(ptr == nullptr)				//last item in the list set head to nullptr
				head = ptr;


			return dataholder;
		}

		void insert_at() {}
		T search() {}
		void slice() {}
		void mergesort() {}
		void reverse_mergesort() {}

		ostream& operator<<(ostream& os, const list& l)
		{
			os << "\n\n";

			for(list.begin)
			return os;
		}

};