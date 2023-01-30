#ifndef RBT_ITE_HPP
# define RBT_ITE_HPP

# include "iterator.hpp"
# include <iostream>

namespace ft
{
	template<typename T, typename node_type>
	class RBTIterator
	{

		public :
			typedef T								value_type;
			typedef T*								pointer;
			typedef const T*						const_pointer;
			typedef T&								reference;
			typedef const T&						const_reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef node_type*						node_pointer;

			node_pointer	_node;

			RBTIterator() : _node(NULL) {}
			RBTIterator(node_pointer src) : _node(src) {}
			RBTIterator(RBTIterator const &src) : _node(src._node) {}
			~RBTIterator() {}

			RBTIterator&	operator=(RBTIterator const &src) {
				if (this != &src)
					_node = src._node;
				return *this;
			}

			operator RBTIterator<const T, node_type>() const {
				return RBTIterator<const T, node_type>(_node);
			}

			reference	operator*() const {
				return *(_node->data);
			}

			pointer		operator->() const {
				return _node->data;
			}

			RBTIterator&	operator++() {
				increment();
				return *this;
			}

			RBTIterator	operator++(int) {
				RBTIterator tmp(*this);
				increment();		
				return tmp;
			}

			RBTIterator&	operator--() {
				decrement();
				return *this;
			}

			RBTIterator	operator--(int) {
				RBTIterator tmp(*this);
				decrement();
				return tmp;
			}

			bool	operator==(RBTIterator const &src) const {
				return (_node == src._node);
			}

			bool	operator!=(RBTIterator const &src) const {
				return (_node != src._node);
			}

			protected :
			
			void	increment() {
				if (_node == _node->nil_node)
					return ;
				if (_node->right != _node->nil_node) {
					_node = _min(_node->right);
					return ;
				}
				else
				{
					node_pointer tmp = _node->parent;
					while (tmp != 0 && tmp != _node->nil_node && _node == tmp->right)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					if (tmp == 0)
						_node = _node->nil_node;
					else
						_node = tmp;
				}
			}

			void	decrement() {
				if (_node == _node->nil_node)
				{
					_node = _node->nil_node->max;
					return ;
				}
				if (_node->left != _node->nil_node) {
					_node = _max(_node->left);
					return ;
				}
				else
				{
					node_pointer tmp = _node->parent;
					while (tmp != 0 && tmp != _node->nil_node && _node == tmp->left)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					if (tmp == 0)
						_node = _node->nil_node;
					else
						_node = tmp;
				}
			}

			private :

			node_pointer	_min(node_pointer node) {
				while (node->left != node->nil_node)
					node = node->left;
				return node;
			}

			node_pointer	_max(node_pointer node) {
				while (node->right != node->nil_node)
					node = node->right;
				return node;
			}

	};
}

#endif
