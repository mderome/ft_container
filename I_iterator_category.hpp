#ifndef I_ITERATOR_CATEGORY_HPP
#define I_ITERATOR_CATEGORY_HPP

#include <iostream>
#include <string>
#include <iterator>

namespace ft
{
	template <class Derived, class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class I_input_iterator
	{
		private :
			typedef I_input_iterator<Derived,Category, T, Distance, Pointer, Reference>		iterator_type;
		
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	
			I_input_iterator() {}
			template <typename Category2, typename T2>
			I_input_iterator(const I_input_iterator<Derived, Category2, T2>&) {}
			virtual ~I_input_iterator() {}

			virtual bool operator==(const Derived& other) const = 0;
			virtual bool operator!=(const Derived& other) const = 0;

			virtual reference operator*() const = 0;
			virtual pointer operator->() const = 0;

			virtual Derived		&operator=(const Derived &other) = 0;
			virtual Derived		&operator++() = 0;
			virtual Derived		operator++(int) = 0; 
	};


	template <class Derived, class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class I_output_iterator
	{
		private :
			typedef I_output_iterator<Derived,Category, T, Distance, Pointer, Reference>		iterator_type;
		
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	
			I_output_iterator() {}
			template <typename Category2, typename T2>
			I_output_iterator(const I_output_iterator<Derived, Category2, T2>&) {}
			virtual ~I_output_iterator() {}

			virtual reference operator*() const = 0;

			virtual Derived		&operator=(const Derived &other) = 0;
			virtual Derived		&operator++() = 0;
			virtual Derived		operator++(int) = 0; 
	};

	template <class Derived, class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class I_forward_iterator : public I_input_iterator<Derived,Category, T, Distance, Pointer, Reference>
	{
		private :
			typedef I_forward_iterator<Derived,Category, T, Distance, Pointer, Reference>		iterator_type;
			typedef I_input_iterator<Derived,Category, T, Distance, Pointer, Reference>		input_iterator_type;
	
		
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		I_forward_iterator(void) :
			input_iterator_type() {}

		
		template <typename _Derived, typename _T>
		I_forward_iterator(I_forward_iterator<Derived, _Derived, _T> const &src) :
			input_iterator_type(src) {}


		virtual ~I_forward_iterator(void) {}
	};

	template <class Derived, class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class I_bidirectionnal_iterator : public I_forward_iterator<Derived, Category, T, Distance, Pointer, Reference>
	{
		private :
			typedef I_bidirectionnal_iterator<Derived,Category, T, Distance, Pointer, Reference>		iterator_type;
			typedef I_forward_iterator<Derived,Category, T, Distance, Pointer, Reference>			forward_iterator_type;

		
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

		I_bidirectionnal_iterator(void) :
			forward_iterator_type() {}

		
		template <typename _Derived, typename _T>
		I_bidirectionnal_iterator(I_bidirectionnal_iterator<Derived, _Derived, _T> const &src) :
			forward_iterator_type(src) {}


		virtual ~I_bidirectionnal_iterator(void) {}


		virtual Derived		&operator--() = 0;
		virtual Derived		operator--(int) = 0; 
	};

	template <class Derived, class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class I_random_access_iterator : public I_bidirectionnal_iterator<Derived,Category, T, Distance, Pointer, Reference>
	{
		private :
			typedef I_random_access_iterator<Derived,Category, T, Distance, Pointer, Reference>		iterator_type;
			typedef I_bidirectionnal_iterator<Derived,Category, T, Distance, Pointer, Reference>	bidirectionnal_iterator_type;

		
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	
		I_random_access_iterator(void) :
			bidirectionnal_iterator_type() {}

		
		template <typename _Derived, typename _T>
		I_random_access_iterator(I_random_access_iterator<Derived, _Derived, _T> const &src) :
			bidirectionnal_iterator_type(src) {}


		virtual ~I_random_access_iterator(void) {}

		virtual bool			operator<(Derived const &rhs) const = 0;
		virtual bool			operator>(Derived const &rhs) const = 0;
		virtual bool			operator<=(Derived const &rhs) const = 0;
		virtual bool			operator>=(Derived const &rhs) const = 0;

		virtual Derived			&operator+=(difference_type const rhs) = 0;
		virtual Derived			&operator-=(difference_type const rhs) = 0;
		virtual Derived			operator+(difference_type const rhs) const = 0;
		virtual Derived			operator-(difference_type const rhs) const = 0;

		virtual difference_type	operator-(Derived const &rhs) const = 0;

		virtual Reference		operator[](difference_type const idx) const = 0;
	};
}

#endif
