#include "stdafx.h"

template<class T> class node
{
	private:
		T data;
		node* next;
		node* last;

	public:
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

			if(tail != nullptr)
				tail->set_next(n_ptr);
			tail = n_ptr;
		}

		T pop() {
			T data_holder;
			node* ptr;
			
			prt = tail->get_last();
			data_holder = tail->get_data();
			tail = ptr;

			return dataholder;
		}
		void insert_at(){}
		T search(){}
		void slice(){}
		void mergesort(){}
		void reverse_mergesort(){}

};