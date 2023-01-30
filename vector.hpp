#ifndef VECTOR_HPP
# define VECTOR_HPP


# include <iostream>
# include <memory>
# include <cstddef>
# include <cstring>
# include "vector_iterator.hpp"
# include "iterator.hpp"
# include "equal.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"

namespace	ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public :

		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::vector_iterator<pointer>				iterator;
		typedef ft::vector_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		//attribute
		private:

			pointer				_pointer;
			allocator_type		_alloc;
			size_type			_capacity;
			size_type			_size;

				template<typename U>
		inline void	_insertDispatch(iterator const pos, U const param1, U const param2, true_type const)
		{
			this->_insertFill(pos, param1, param2);
		}

		template<typename U>
		inline void	_insertDispatch(iterator const pos, U const param1, U const param2, false_type const)
		{
			this->_insertRange(pos, param1, param2, typename iterator_traits<U>::iterator_category());
		}

		inline void	_insertFill(iterator const pos, size_type const n, value_type const &val)
		{
			size_type const	offset = pos - this->begin();
			pointer			ptr0;
			pointer			ptr1;
			allocator_type	alloc;

			this->_prepareMemoryArea(pos, n);

			for (ptr0 = this->_pointer + offset, ptr1 = ptr0 + n ; ptr0 != ptr1 ; ++ptr0)
				alloc.construct(ptr0, val);
		}

		template <typename InputIterator>
		void	_insertRange(
			iterator const &pos,
			InputIterator first,
			InputIterator const last,
			std::input_iterator_tag const)
		{
			size_type const	offset = this->end() - pos;
			size_type		newCapacity;
			pointer			newHead;
			pointer			newTail;
			allocator_type	alloc;

			newCapacity = this->size() * 2;
			for ( ; first != last ; ++first)
			{
				if (this->size() < this->capacity())
					this->_rangeMove((this->_pointer + this->_size) - offset + 1, (this->_pointer + this->_size) - offset, (this->_pointer + this->_size));
				else
				{

					if (newCapacity < this->size() + 1)
						newCapacity = this->size() + 1;
					newHead = alloc.allocate(newCapacity, this->_pointer);
					newTail = newHead + this->size();
					if (this->_pointer)
					{
						this->_rangeMove(newHead, this->_pointer, (this->_pointer + this->_size) - offset);
						this->_rangeMove(newTail - offset + 1, (this->_pointer + this->_size) - offset, (this->_pointer + this->_size));
						alloc.deallocate(this->_pointer, this->capacity());
					}
					this->_pointer = newHead;
					this->_size = newTail - newHead;
					this->_capacity = newCapacity;
					++newCapacity;
				}
				alloc.construct((this->_pointer + this->_size) - offset, *first);
				++this->_size;
			}
		}

		void	_prepareMemoryArea(iterator const &pos, size_type const n)
		{
			size_type const	offset = pos - this->begin();
			size_type		newCapacity;
			pointer			newHead;
			pointer			newTail;
			allocator_type	alloc;


			if (!n)
				return ;
			if (this->size() + n <= this->capacity())
			{
				this->_rangeMove(this->_pointer + offset + n, this->_pointer + offset, (this->_pointer + this->_size));
				this->_size += n;
			}
			else
			{
				newCapacity = this->size() * 2;
				if (newCapacity < this->size() + n)
					newCapacity = this->size() + n;
				newHead = alloc.allocate(newCapacity, this->_pointer);
				newTail = newHead + this->size() + n;
				if (this->_pointer)
				{
					this->_rangeMove(newHead, this->_pointer, pos.base());
					this->_rangeMove(newHead + offset + n, pos.base(), (this->_pointer + this->_size));
					alloc.deallocate(this->_pointer, this->capacity());
				}
				this->_pointer = newHead;
				this->_size = newTail - newHead;
				this->_capacity = newCapacity;
			}
		}

		inline void	_rangeMove(pointer dst, pointer first, pointer last)
			__attribute__((nonnull))
		{
			allocator_type	alloc;


			if (is_trivially_copyable<value_type>::value)
				memmove(dst, first, (last - first) * sizeof(value_type));
			else if (dst < first)
				for ( ; first != last ; ++first, ++dst)
				{
					alloc.construct(dst, *first);
					alloc.destroy(first);
				}
			else if (dst > first)
				for (dst += (last - first - 1), --first, --last ; first != last ; --last, --dst)
				{
					alloc.construct(dst, *last);
					alloc.destroy(last);
				}
		}

		public :
			//member fonction
			explicit vector( const Allocator& alloc = Allocator() ) : _pointer(NULL), _alloc(alloc), _capacity(0), _size(0) {};

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) : _pointer(0), _alloc(alloc), _capacity(count), _size(count) {
				_pointer = _alloc.allocate(count);
				for (size_type i(0); i < count; i++) {
					_alloc.construct(_pointer + i, value);
				}
			};

		
			template <class InputIterator>
			vector( InputIterator first, InputIterator last, const Allocator& alloc = Allocator()) : _pointer(NULL), _alloc(alloc), _capacity(0), _size(0) {
					this->_insertDispatch(iterator(), first, last, is_integral<InputIterator>());
			
			};

			vector(const vector& x) : _pointer(NULL), _alloc(x._alloc), _capacity(0), _size(0) {
				this->_insertRange(iterator(), x.begin(), x.end(), typename iterator_traits<iterator>::iterator_category());
			}

			~vector() {
				clear();
				_alloc.deallocate(_pointer, _capacity);
			}

			vector<T, Allocator>& operator=(const vector< T, Allocator >& x) {
				if (this != &x) {
					assign(x.begin(), x.end());
				}
				return *this;
			};

			allocator_type get_allocator() const {return (_alloc);};

			//iterator
			iterator	begin() {
				return (iterator(_pointer));
			}

			const_iterator	begin() const {
				return (const_iterator(_pointer));
			}

			iterator	end() {
				return (iterator(_pointer + _size));
			}

			const_iterator	end() const {
				return (const_iterator(_pointer + _size));
			}

			reverse_iterator rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const {
				return (const_reverse_iterator(begin()));
			}
			//capacity
			
			size_type	size() const {
				return (_size);
			}
			size_type	max_size() const {
				return (_alloc.max_size());
			}

			void	resize(size_type n, value_type val = value_type()) {
				if (n > size())
					insert(end(), n - size(), val);
				else if (n < size())
					erase(begin() + n, end());
				else
					return ;
			}
			size_type	capacity() const {
				return (_capacity);
			}
			bool	empty() const {
				return (_size == 0);
			}
			void	reserve(size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				else if (n <= capacity())
					return;
				else {
					pointer	tmp;
					tmp = _alloc.allocate(n);
					for (size_type i(0); i < _size; i++) {
						_alloc.construct(tmp + i, *(_pointer + i));
						_alloc.destroy(_pointer + i);
					}
					_alloc.deallocate(_pointer, _capacity);
					_capacity = n;
					_pointer = tmp;
				}
			}

			//element access
			reference	operator[](size_type n) {
				return (*(this->begin() + n));
			}
			const_reference	operator[](size_type n) const {
				return (*(this->begin() + n));
			}
			reference	at(size_type n) {
				if (n >= size())
					throw std::out_of_range("out of range");
				return (*(this->begin() + n));
			}
			const_reference	at(size_type n) const {
				if (n >= size())
					throw std::out_of_range("out of range");
				return (*(this->begin() + n));
			}
			reference	front() {
				return (*(this->begin()));
			}
			const_reference	front() const {
				return (*(this->begin()));
			}
			reference	back() {
				return (*--this->end());
			}
			const_reference	back() const {
				return (*--this->end());
			}

			//modifiers
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last) {
				clear();
				insert(begin(), first, last);
			}
			void	assign(size_type n, const value_type& val) {
				clear();
				insert(begin(), n, val);
			}

			void push_back( const T& x ) {
			if (_capacity == 0) {
				reserve(1);
			}
			else if (_size == _capacity && _capacity != 0) {
				reserve(2 * _capacity);
			}
			_alloc.construct(_pointer + _size, x);
			_size++;
		};

		void pop_back() {
			_alloc.destroy(&this->back());
			_size--;
		};

		iterator insert( iterator position, const T& x ) {
			size_type distance;
			distance = position - this->begin();
			_insertFill(position, 1, x);
			return this->begin() + distance;
		};

		void insert( iterator position, size_type n, const T& x ) {
			if (n == 0)
				return ;
			difference_type distance;
			distance = position - this->begin();
			_insertFill(position, n, x);
		};

		template <class InputIterator>
		void insert( iterator position, InputIterator first, InputIterator last) {
				this->_insertDispatch(position, first, last, is_integral<InputIterator>());
		};

		iterator erase( iterator position ) {
			return this->erase(position, position + 1);
		};

		iterator erase( iterator first, iterator last ) {
			
			allocator_type	alloc;
			iterator		it;

			for (it = first ; it != last ; ++it)
				alloc.destroy(it.base());
			this->_rangeMove(first.base(), last.base(), this->_pointer + this->_size);
			this->_size -= last - first;
			return first;
		};

		void swap( vector<T,Allocator>& b) {
			std::swap(_pointer, b._pointer);
			std::swap(_size, b._size);
			std::swap(_capacity, b._capacity);
		};

		void clear() {
			iterator	it;
			it = this->begin();
			while (it != this->end()) {
				_alloc.destroy(&(*it));
				it++;
			}
			//_alloc.deallocate(_pointer, _capacity);
			_size = 0;
			// _capacity = 0;
		};
	};
		//relational operators
		template< class T, class Alloc >
		void swap( ft::vector<T,Alloc>& lhs, ft	::vector<T,Alloc>& rhs ) {
			lhs.swap(rhs);
		}

		template <class T, class Allocator>
		bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			if (x.size() != y.size())
				return false;
			for (size_t j = 0; j < x.size(); j++) {
				if (x.at(j) != y.at(j))
					return false;
			}
			return true;
		}

		template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			return (!(x==y));
		}

		template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			return (y < x);

		}

		template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			return (!(x < y));
		}

		template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
			return (!(y < x));
		}

}

#endif
