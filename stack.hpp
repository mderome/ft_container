#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include "equal.hpp"
# include "vector.hpp"

namespace	ft
{
	template< class T, class C = ft::vector<T> >
	class stack
	{

		protected:
			C	container;

			public:
			typedef typename C::value_type		value_type;
			typedef typename C::size_type		size_type;
			typedef C							container_type;
			
			//constructor
			explicit stack (const container_type& ctnr = container_type()) : container(ctnr) {}
			//destructor
			~stack() {}
			//member function
			bool empty() const { return container.empty(); }
			size_type size() const { return container.size(); }
			value_type& top() { return container.back(); }
			const value_type& top() const { return container.back(); }
			void push (const value_type& val) { container.push_back(val); }
			void pop() { container.pop_back(); }
			void swap(stack& x);
			template <class T2, class Container>
			friend bool operator==(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
			template <class T2, class Container>
			friend bool operator!=(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
			template <class T2, class Container>
			friend bool operator<(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
			template <class T2, class Container>
			friend bool operator<=(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
			template <class T2, class Container>
			friend bool operator>(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
			template <class T2, class Container>
			friend bool operator>=(const stack<T2,Container>& lhs, const stack<T2,Container>& rhs);
	};

	
		//relational operator
		template <class T, class Container>
		bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.container == rhs.container);
		}
		template <class T, class Container>
		bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.container != rhs.container);
		}
		template <class T, class Container>
		bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.container < rhs.container);
		}
		template <class T, class Container>
		bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.container <= rhs.container);
		}
		template <class T, class Container>
		bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.container > rhs.container);
		}
		template <class T, class Container>
		bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>&rhs) {
			return (lhs.container >= rhs.container);
		}
}

#endif
