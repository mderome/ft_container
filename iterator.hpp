#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iostream>
#include <limits>
#include <typeinfo>
#include <cstddef>

namespace ft
{

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	// generic definition
	template <class Iterator>
	class iterator_traits
	{
		public :
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};

	// T* specialization
	template <class T>
	class iterator_traits<T *>
	{
		public :
			typedef std::random_access_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef T&									reference;
	};

	// const T* specialization
	template <class T>
	class iterator_traits<const T *>
	{
		public :
			typedef std::random_access_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T const *									pointer;
			typedef T const &									reference;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {

			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;

	};

	// reverse iterator
	template <class Iterator>
	class reverse_iterator
	{
		public :
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
		
		public :
			Iterator	_current;
		
		public :
			typedef Iterator	iterator_type;

			explicit reverse_iterator(Iterator const& it = Iterator()) : _current(it) {};
			template <class Iter>
			reverse_iterator(reverse_iterator<Iter> const& rev_it) : _current(rev_it.base()) {};
			Iterator	base() const { return _current; };
			reference operator*() const { Iterator tmp = _current; return *--tmp; };
			pointer operator->() const { return &(operator*()); };
			reverse_iterator& operator++() { --_current; return *this; };
			reverse_iterator operator++(int) { reverse_iterator tmp = *this; --_current; return tmp; };
			reverse_iterator& operator--() { ++_current; return *this; };
			reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++_current; return tmp; };
			reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); };
			reverse_iterator& operator+=(difference_type n) { _current -= n; return *this; };
			reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); };
			reverse_iterator& operator-=(difference_type n) { _current += n; return *this; };
			reference operator[](difference_type n) const { return *(*this + n); };
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current == rhs._current; }
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current != rhs._current; }
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current > rhs._current; }
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current >= rhs._current; }
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current < rhs._current; }
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs._current <= rhs._current; }
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return reverse_iterator<Iterator>(rev_it._current - n); }
	template <class Iterator, class Iterator1>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator1>& rhs) { return rhs.base() - lhs.base(); }
	// template <class Iterator>
	// typename reverse_iterator<Iterator>::difference_type operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it.base() - n); }
	template <class Iterator, class Ierator2>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() == rhs.base(); }
	template <class Iterator, class Ierator2>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() != rhs.base(); }
	template <class Iterator, class Ierator2>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() > rhs.base(); }
	template <class Iterator, class Ierator2>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() >= rhs.base(); }
	template <class Iterator, class Ierator2>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iterator, class Ierator2>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Ierator2>& rhs) { return lhs.base() <= rhs.base(); }

}

#endif
