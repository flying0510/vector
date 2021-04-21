#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include <iostream>
#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
	/**
	 * a data container like std::vector
	 * store data in a successive memory and support random access.
	 */
	template<typename T>
	class vector {
	public:
		/**
		 * TODO
		 * a type for actions of the elements of a vector, and you should write
		 *   a class named const_iterator with same interfaces.
		 */
		T* data;
		size_t currentlength;
		size_t maxsize;
		/**
		 * you can see RandomAccessIterator at CppReference for help.
		 */
		class const_iterator;
		class iterator {
		private:
			/**
			 * TODO add data members
			 *   just add whatever you want.
			 */
			vector<T>* ptr;
			size_t index;
		public:
			iterator()
			{
				ptr = NULL;
				index = 0;
			}
			iterator(vector<T>* p, size_t n)
			{
				ptr = p;
				index = n;
			}
			size_t getindex()
			{
				return index;
			}
			vector<T>* getptr()
			{
				return ptr;
			}
			/**
			 * return a new iterator which pointer n-next elements
			 * as well as operator-
			 */
			iterator operator+(const int& n) const {
				//TODO
				iterator tmp(ptr, index + n);
				return tmp;
			}
			iterator operator-(const int& n) const {
				//TODO
				iterator tmp(ptr, index - n);
				return tmp;
			}
			// return the distance between two iterators,
			// if these two iterators point to different vectors, throw invaild_iterator.
			int operator-(const iterator& rhs) const {
				//TODO
				if (ptr != rhs.ptr) throw invalid_iterator();
				else return (index - rhs.index);
			}
			iterator& operator+=(const int& n) {
				//TODO
				index += n;
				return *this;
			}
			iterator& operator-=(const int& n) {
				//TODO
				index -= n;
				return *this;
			}
			/**
			 * TODO iter++
			 */
			iterator operator++(int) {
				iterator tmp(ptr, index);
				++index;
				return tmp;
			}
			/**
			 * TODO ++iter
			 */
			iterator& operator++() {
				++index;
				return *this;
			}
			/**
			 * TODO iter--
			 */
			iterator operator--(int) {
				iterator tmp(ptr, index);
				--index;
				return tmp;
			}
			/**
			 * TODO --iter
			 */
			iterator& operator--() {
				--index;
				return *this;
			}
			/**
			 * TODO *it
			 */
			T& operator*() const {
				return (*ptr)[index];
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory address).
			 */
			bool operator==(const iterator& rhs) const {
				if ((ptr == rhs.ptr) && (index == rhs.index)) return true;
				else return false;
			}
			bool operator==(const const_iterator& rhs) const {
				if ((ptr == rhs.ptr) && (index == rhs.index)) return true;
				else return false;
			}
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator& rhs) const {
				if (*this == rhs) return false;
				else return true;
			}
			bool operator!=(const const_iterator& rhs) const {
				if ((ptr == rhs.ptr) && (index == rhs.index)) return false;
				else return true;
			}
		};
		/**
		 * TODO
		 * has same function as iterator, just for a const object.
		 */
		class const_iterator {
		private:
			const vector<T>* ptr;
			size_t index;
		public:
			const_iterator()
			{
				ptr = NULL;
				index = 0;
			}
			const_iterator(const vector<T>* p, size_t n)
			{
				this->ptr = p;
				this->index = n;
			}
			size_t getindex()const
			{
				return index;
			}
			vector<T>* const getptr()const
			{
				return ptr;
			}
			const_iterator operator+(const int& n) const {
				const_iterator tmp(ptr, index + n);
				return tmp;
			}
			const_iterator operator-(const int& n) const {
				const_iterator tmp(ptr, index - n);
				return tmp;
			}
			int operator-(const const_iterator& rhs) const {
				//TODO
				if (*this == rhs.ptr)
					throw invalid_iterator();
				else return (index - rhs.index);
			}
			const_iterator& operator+=(const int& n) {
				//TODO
				index += n;
				return *this;
			}
			const_iterator& operator-=(const int& n) {
				//TODO
				index -= n;
				return *this;
			}
			/**
			 * TODO iter++
			 */
			const_iterator operator++(int) {
				const_iterator tmp(ptr, index);
				++index;
				return tmp;
			}
			/**
			 * TODO ++iter
			 */
			const_iterator& operator++() {
				++index;
				return *this;
			}
			/**
			 * TODO iter--
			 */
			const_iterator operator--(int) {
				const_iterator tmp(ptr, index);
				--index;
				return tmp;
			}
			/**
			 * TODO --iter
			 */
			const_iterator& operator--() {
				--index;
				return *this;
			}
			/**
			 * TODO *it
			 */
			const T& operator*() const {
				return (*ptr)[index];
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory address).
			 */
			bool operator==(const iterator& rhs) const {
				if ((ptr == rhs.ptr) && (index == rhs.index)) return true;
				else return false;
			}
			bool operator==(const const_iterator& rhs) const {
				if ((ptr == rhs.ptr) && (index == rhs.index)) return true;
				else return false;
			}
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator& rhs) const {
				if (*this == rhs) return false;
				else return true;
			}
			bool operator!=(const const_iterator& rhs) const {
				if (*this == rhs) return false;
				else return true;
			}
		};
		/**
		 * TODO Constructs
		 * Atleast two: default constructor, copy constructor
		 */
		vector() {
			data = (T*)malloc(sizeof(T) * 10);
			memset(data, 0, sizeof(T) * 10);
			currentlength = 0;
			maxsize = 10;
		}
		vector(const vector& other) {
			this->data = (T*)malloc(sizeof(T) * other.maxsize);
			memset(data, 0, sizeof(T) * other.maxsize);
			currentlength = other.currentlength;
			for (size_t i = 0;i < currentlength;++i)
				this->data[i] = other.data[i];
			maxsize = other.maxsize;
		}
		/**
		 * TODO Destructor
		 */
		~vector() {
			for (size_t i = 0;i < maxsize;++i)
				data[i].~T();
			currentlength = 0;
			maxsize = 0;
			free(data);
		}
		/**
		 * TODO Assignment operator
		 */
		bool operator==(const vector& other) {
			if (data == other.data && currentlength == other.currentlength && maxsize == other.maxsize)
				return true;
			else return false;
		}
		vector& operator=(const vector& other) {
			if (*this == other) return *this;
			else
			{
				for (size_t i = 0;i < maxsize;++i)
					data[i].~T();
				free(data);
				this->data = (T*)malloc(sizeof(T) * other.maxsize);
				memset(data, 0, sizeof(T) * other.maxsize);
				currentlength = other.currentlength;
				maxsize = other.maxsize;
				for (size_t i = 0;i < currentlength;++i)
					this->data[i] = other.data[i];
				return *this;
			}
		}
		/**
		 * assigns specified element with bounds checking
		 * throw index_out_of_bound if pos is not in [0, size)
		 */
		T& at(const size_t& pos) {
			if (pos < 0 || pos >= currentlength) throw index_out_of_bound();
			else return data[pos];
		}
		const T& at(const size_t& pos) const {
			if (pos < 0 || pos >= currentlength) throw index_out_of_bound();
			else return data[pos];
		}
		/**
		 * assigns specified element with bounds checking
		 * throw index_out_of_bound if pos is not in [0, size)
		 * !!! Pay attentions
		 *   In STL this operator does not check the boundary but I want you to do.
		 */
		T& operator[](const size_t& pos) {
			if (pos < 0 || pos >= currentlength) throw index_out_of_bound();
			else	return data[pos];
		}
		const T& operator[](const size_t& pos) const {
			if (pos < 0 || pos >= currentlength) throw index_out_of_bound();
			else return data[pos];
		}
		/**
		 * access the first element.
		 * throw container_is_empty if size == 0
		 */
		const T& front() const {
			if (currentlength == 0)
				throw container_is_empty();
			else return data[0];
		}
		/**
		 * access the last element.
		 * throw container_is_empty if size == 0
		 */
		const T& back() const {
			if (currentlength == 0)
				throw container_is_empty();
			else return data[currentlength - 1];
		}
		/**
		 * returns an iterator to the beginning.
		 */
		iterator begin() {

			iterator it(this, 0);
			return it;
		}
		const_iterator cbegin() const {
			const_iterator cit(this, 0);
			return cit;
		}
		/**
		 * returns an iterator to the end.
		 */
		iterator end() {
			iterator it(this, currentlength);
			return it;
		}
		const_iterator cend() const {
			const_iterator cit(this, currentlength);
			return cit;
		}
		/**
		 * checks whether the container is empty
		 */
		bool empty() const {
			if (currentlength == 0) return true;
			else return false;
		}
		/**
		 * returns the number of elements
		 */
		size_t size() const {
			return currentlength;
		}
		/**
		 * clears the contents
		 */
		void clear() {
			currentlength = 0;
		}
		/**
		 * inserts value before pos
		 * returns an iterator pointing to the inserted value.
		 */
		iterator insert(iterator pos, const T& value) {
			if (currentlength + 1 == maxsize) resize(maxsize * 2);
			for (size_t i = currentlength;i >= pos.getindex() + 1;--i)
			{
				data[i] = data[i - 1];
			}
			data[pos.getindex()] = value;
			++currentlength;
			iterator it(pos.getptr(), pos.getindex());
			return it;
		}
		/**
		 * inserts value at index ind.
		 * after inserting, this->at(ind) == value
		 * returns an iterator pointing to the inserted value.
		 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
		 */
		iterator insert(const size_t& ind, const T& value) {

			if (ind > currentlength)
				throw index_out_of_bound();
			else {
				if (currentlength + 1 == maxsize) resize(maxsize * 2);
				for (int i = currentlength - 1;i >= ind;--i)
					data[i + 1] = data[i];
				data[ind] = value;
				++currentlength;
				iterator it(this, ind);
				return it;
			}
		}
		/**
		 * removes the element at pos.
		 * return an iterator pointing to the following element.
		 * If the iterator pos refers the last element, the end() iterator is returned.
		 */
		iterator erase(iterator pos) {
			--currentlength;
			for (size_t i = pos.getindex();i < currentlength;++i)
				data[i] = data[i + 1];
			if (pos.getindex() == currentlength) return end();
			else
			{
				iterator it(pos.getptr(), pos.getindex() + 1);
				return it;
			}
		}
		/**
		 * removes the element with index ind.
		 * return an iterator pointing to the following element.
		 * throw index_out_of_bound if ind >= size
		 */
		iterator erase(const size_t& ind) {
			if (ind >= size())
				throw index_out_of_bound();
			else {

				for (size_t i = ind; i < currentlength - 1;++i)
					data[i] = data[i + 1];
				--currentlength;
				iterator it(this, ind + 1);
				return it;
			}
		}
		/**
		 * adds an element to the end.
		 */
		void push_back(const T& value) {
#ifdef debug1
			debug1;
#endif
			if (currentlength + 1 == maxsize) resize(maxsize * 2);
#ifdef debug1
			debug1;
#endif
			data[currentlength] = value;
#ifdef debug1
			debug1;
#endif
			++currentlength;
		}
		/**
		 * remove the last element from the end.
		 * throw container_is_empty if size() == 0
		 */
		void pop_back() {
			if (currentlength == 0) throw container_is_empty();
			--currentlength;
		}
		void resize(size_t size)
		{
			T* tmp = data;
			data = (T*)malloc(sizeof(T) * size);
			memset(data, 0, sizeof(T) * size);
			for (size_t i = 0;i < currentlength;++i)
				data[i] = tmp[i];
			for (size_t i = 0;i < maxsize;++i)
				tmp[i].~T();
			free(tmp);
			maxsize = size;
		}
	};


}

#endif
