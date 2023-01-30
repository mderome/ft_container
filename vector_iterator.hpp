#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iostream>
#include <string>
#include <iterator>
#include "I_iterator_category.hpp"
#include "iterator.hpp"

namespace ft
{
	template<typename RandomAccessIterator>
	class vector_iterator : public I_random_access_iterator<
		vector_iterator<RandomAccessIterator>,
		typename iterator_traits<RandomAccessIterator>::value_type,
		typename iterator_traits<RandomAccessIterator>::iterator_category,
		typename iterator_traits<RandomAccessIterator>::difference_type,
		typename iterator_traits<RandomAccessIterator>::pointer,
		typename iterator_traits<RandomAccessIterator>::reference>
	{
		public:
			typedef typename iterator_traits<RandomAccessIterator>::value_type			value_type;
			typedef typename iterator_traits<RandomAccessIterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<RandomAccessIterator>::difference_type		difference_type;
			typedef typename iterator_traits<RandomAccessIterator>::pointer				pointer;
			typedef typename iterator_traits<RandomAccessIterator>::reference			reference;
		protected:
			pointer	ptr;
		public:
			vector_iterator() : ptr(0) {}
			vector_iterator(pointer ptr) : ptr(ptr) {}
			template <class U>
			vector_iterator(const vector_iterator<U>& copy) : ptr(copy.base()) {}
			~vector_iterator() {}

			pointer base() const {
				return ptr;
			};

			vector_iterator<RandomAccessIterator>&	operator=(vector_iterator<RandomAccessIterator> const & copy)
			{
				if (this != &copy)
					this->ptr = copy.ptr;
				return (*this);
			}
			reference	operator*() const { return (*ptr); }
			pointer		operator->() const { return (ptr); }
			vector_iterator<RandomAccessIterator>&	operator++()
			{
				ptr++;
				return (*this);
			}
			vector_iterator<RandomAccessIterator>	operator++(int)
			{
				vector_iterator<RandomAccessIterator>	tmp(*this);
				operator++();
				return (tmp);
			}
			vector_iterator<RandomAccessIterator>&	operator--()
			{
				ptr--;
				return (*this);
			}
			vector_iterator<RandomAccessIterator>	operator--(int)
			{
				vector_iterator<RandomAccessIterator>	tmp(*this);
				operator--();
				return (tmp);
			}
			vector_iterator<RandomAccessIterator>&	operator+=(difference_type n)
			{
				ptr += n;
				return (*this);
			}
			vector_iterator<RandomAccessIterator>	operator+(difference_type n) const
			{
				vector_iterator<RandomAccessIterator>	tmp(*this);
				tmp += n;
				return (tmp);
			}
			vector_iterator<RandomAccessIterator>&	operator-=(difference_type n)
			{
				ptr -= n;
				return (*this);
			}
			vector_iterator<RandomAccessIterator>	operator-(difference_type n) const
			{
				vector_iterator<RandomAccessIterator>	tmp(*this);
				tmp -= n;
				return (tmp);
			}
			reference operator[](difference_type n) const
			{
				return (ptr[n]);
			}
			bool	operator==(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr == rhs.ptr);
			}
			bool	operator!=(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr != rhs.ptr);
			}
			bool	operator<(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr < rhs.ptr);
			}
			bool	operator<=(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr <= rhs.ptr);
			}
			bool	operator>(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr > rhs.ptr);
			}
			bool	operator>=(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr >= rhs.ptr);
			}
			template<class U>
			bool	operator==(vector_iterator<U> const & rhs) const
			{
				return (this->ptr == rhs.base());
			}
			template<class U>
			bool	operator!=(vector_iterator<U> const & rhs) const
			{
				return (this->base() != rhs.base());
			}
			template<class U>
			bool	operator<(vector_iterator<U> const & rhs) const
			{
				return (this->base() < rhs.base());
			}
			template<class U>
			bool	operator<=(vector_iterator<U> const & rhs) const
			{
				return (this->base() <= rhs.base());
			}
			template<class U>
			bool	operator>(vector_iterator<U> const & rhs) const
			{
				return (this->base() > rhs.base());
			}
			template<class U>
			bool	operator>=(vector_iterator<U> const & rhs) const
			{
				return (this->base() >= rhs.base());
			}
			difference_type	operator-(vector_iterator<RandomAccessIterator> const & rhs) const
			{
				return (this->ptr - rhs.ptr);
			}
			template<class U>
			difference_type	operator-(vector_iterator<U> const & rhs) const
			{
				return (this->base() - rhs.base());
			}
	};

	template<typename RandomAccessIterator>
	vector_iterator<RandomAccessIterator>	operator+(typename vector_iterator<RandomAccessIterator>::difference_type n, vector_iterator<RandomAccessIterator> const & rhs)
	{
		vector_iterator<RandomAccessIterator>	tmp(rhs);
		tmp += n;
		return (tmp);
	}
	
}

#endif
