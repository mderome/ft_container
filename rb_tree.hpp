//create class red_black_tree iterator

#ifndef RB_TREE_HPP
# define RB_TREE_HPP


# include "rbt_ite.hpp"
# include "node.hpp"
# include "pair.hpp"
# include <algorithm>
# include <memory>
# include <cstddef>
# include <iomanip>
# include <iostream>
# include <utility>
# include <string>
# include <sstream>
# include "enable_if.hpp"
# include "is_integral.hpp"

template<class T, class Comp, class Alloc>
class Red_Black_Tree 
{
	public :
		// typedefs tree
		typedef Red_Black_Tree<T, Comp, Alloc>										Tree;
		typedef T																	value_type;
		typedef size_t																size_type;
		typedef ptrdiff_t															difference_type;
		
		// typedefs node
		typedef node<T> 															node_type;
		typedef node<T>*															node_pointer;

		// typedefs allocator
		typedef typename Alloc::template rebind<tmpnode<value_type> >::other		tmp_allocator;
		typedef typename Alloc::template rebind<value_type>::other					data_allocator;
		typedef typename Alloc::template rebind<node<value_type> >::other			node_allocator;

		// typedefs iterator
		typedef ft::RBTIterator<value_type, node_type>								iterator;
		typedef ft::RBTIterator<const value_type, node_type>						const_iterator;
		typedef ft::reverse_iterator<iterator>										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;

		// typedefs pair
		typedef ft::pair<iterator, bool>										pair_type;
		typedef ft::pair<iterator, iterator>									pair_range;
		typedef ft::pair<const_iterator, const_iterator>						const_pair_range;

	private:
        node_allocator	_node_allocator;
        data_allocator	_allocator;
		Comp				_key_compare;
		node_type		*_root;
		node_type		*_nil;
		size_type		_size;

	public:

		explicit Red_Black_Tree(const Comp compare, const Alloc allocator)
			: _allocator(allocator), _key_compare(compare) {
			_size = 0;
			_nil = _node_allocator.allocate(1);
			_nil->color = BLACK;
			_nil->data = _allocator.allocate(1);
			_nil->nil_node = _nil;
			_nil->parent = 0;
			_nil->left = 0;
			_nil->right = 0;
			_nil->min = _nil;
			_nil->max = _nil;
			_root = _nil;
		}

		Red_Black_Tree(const Red_Black_Tree & src);

		~Red_Black_Tree() {
			if (this->_root != _nil)
				clean();
			_allocator.deallocate(_nil->data, 1);
			_node_allocator.deallocate(_nil, 1);
		}

		Red_Black_Tree&	operator=(const Red_Black_Tree & src) {
			if (this != &src) {
				clean();
				for (const_iterator i = src.begin(); i != src.end(); i++)
					insert(*i);
			}
			return *this;
		}

		iterator				begin() { return iterator(this->_min(_root)); }

		const_iterator			begin() const { return const_iterator(this->_min(_root)); }

		iterator				end() { return iterator(this->_max(_nil)); }

		const_iterator			end() const { return const_iterator(this->_max(_nil)); }

		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }

		const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }

		reverse_iterator		rend() { return reverse_iterator(this->begin()); }
		
		const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

		size_type		        get_size() const { return _size; }
		
		size_type		        get_max_size() const {
			tmp_allocator node_size;
			return node_size.max_size();
		}

		data_allocator	        get_data_allocator() const { return _allocator; }

		Comp				        get_key_compare() const { return _key_compare; }

		bool			        empty() const {
			if (_size == 0)
				return true;
			return false;
		}
		

		void			        swap(Red_Black_Tree & x) {
			std::swap(_root, x._root);
			std::swap(_nil, x._nil);
			std::swap(_size, x._size);
		}

		iterator		        get_lower_bound(const value_type & val) {
			iterator it = begin();
			while (it != end()) {
				if (!_key_compare(*it , val))
					return it;
				it++;
			}
			return it;
		}

		const_iterator	        get_lower_bound(const value_type & val) const {
			const_iterator it = begin();
			while (it != end()) {
				if (!_key_compare(*it , val))
					return it;
				it++;
			}
			return it;
		}

		iterator		        get_upper_bound(const value_type & val) {
			iterator it = begin();
			while (it != end()) {
				if (_key_compare(val , *it))
					return it;
				it++;
			}
			return it;
		}

		const_iterator	        get_upper_bound(const value_type & val) const {
			const_iterator it = begin();
			while (it != end()) {
				if (_key_compare(val , *it))
					return it;
				it++;
			}
			return it;
		}

		pair_range		        get_equal_range(const value_type & val) {
			iterator b = get_lower_bound(val);
			iterator e = get_upper_bound(val);
			return pair_range(b, e);  
		}

		const_pair_range		get_equal_range(const value_type & val) const {
			const_iterator b = get_lower_bound(val);
			const_iterator e = get_upper_bound(val);
			return const_pair_range(b, e);  
		}

		void	clean() {
			_cleanTree(_root);
			_root = _nil;
			_nil->max = _nil;
			_nil->min = _nil;
			_size = 0;
		}

		void _insertFix(node_pointer node) {
			node_pointer y;
			while (node->parent->color == RED) {
				if (node->parent == node->parent->parent->right) {
					y = node->parent->parent->left;
					if (y->color == RED) {
						node->parent->color = BLACK;
						y->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else { 
						if (node == node->parent->left)
						{
							node = node->parent;
							_rightRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_leftRotate(node->parent->parent);
					}
				}
				else {
					y = node->parent->parent->right;
					if (y->color == RED)
					{
						node->parent->color = BLACK;
						y->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{    
							node = node->parent;
							_leftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rightRotate(node->parent->parent);
					}
				}
				if (node == _root)
					break;
			}
			_root->color = BLACK;
			_nil->max = _max(_root);
			_nil->min = _min(_root);
		}

		pair_type	insertNode(const value_type &val, node_pointer pos) {
			node_pointer y = 0;
			node_pointer x;

			if (pos != _nil)
				x = pos;
			else
				x = _root;
			while (x != _nil) {
				y = x;
				if (_isEqual(val, *x->data)) {
					_nil->max = _max(_root);
					_nil->min = _min(_root);	
					return pair_type(iterator(x), BLACK);
				}
				else if (_key_compare(val, *x->data))
					x = x->left;
				else
					x = x->right;
			}
			node_pointer new_node = _newNode(val);
			new_node->parent = y;
			if (y == 0)
				_root = new_node;
			else if (_key_compare(val, *y->data))
				y->left = new_node;
			else
				y->right = new_node;
			_size++;
			if (new_node->parent == 0) {
				new_node->color = BLACK;
				_nil->max = _max(_root);
				_nil->min = _min(_root);
				return pair_type(iterator(new_node), RED);
			}
			if (new_node->parent->parent == 0) {
				_nil->max = _max(_root);
				_nil->min = _min(_root);
				return pair_type(iterator(new_node), RED);
			}
			_insertFix(new_node);
			return pair_type(iterator(new_node), RED);
		}

		pair_type	insert(const value_type &val) {
			return insertNode(val, _root);
		}

		iterator	insertIter(const_iterator it, const value_type & val) {
			iterator pos;
			if (it != end() && _key_compare(val, *(it._node->data))
					&& it._node->parent != _nil
					&& _key_compare(*(it._node->parent->data), val))
				pos = insertNode(val, const_cast<typename Tree::node_pointer>(it._node)).first;
			else
				pos = insertNode(val, _root).first;
			return pos;
		}

		node_pointer	searchTree(const value_type & val) const {
			node_pointer node = _root;
			while (node != _nil && !_isEqual(val, *node->data)) {
				if (_key_compare(val, *node->data))
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		void _deleteFix(node_pointer node) {
			node_pointer tmp_w;
			while (node != _root && node->color == BLACK) {
				if (node == node->parent->left) {
					tmp_w = node->parent->right;
					if (tmp_w->color == RED) {
						tmp_w->color = BLACK;
						node->parent->color = RED;
						_leftRotate(node->parent);
						tmp_w = node->parent->right;
					}
					if (tmp_w->left->color == BLACK && tmp_w->right->color == BLACK) {
						tmp_w->color = RED;
						node = node->parent;
					}
					else {   
						if (tmp_w->right->color == BLACK) {
							tmp_w->left->color = BLACK;
							tmp_w->color = RED;
							_rightRotate(tmp_w);
							tmp_w = node->parent->right;
						}
						tmp_w->color = node->parent->color;
						node->parent->color = BLACK;
						tmp_w->right->color = BLACK;
						_leftRotate(node->parent);
						node = _root;
					}
				}
				else {
					tmp_w = node->parent->left;
					if (tmp_w->color == RED) {
						tmp_w->color = BLACK;
						node->parent->color = RED;
						_rightRotate(node->parent);
						tmp_w = node->parent->left;
					}
					if (tmp_w->right->color == BLACK && tmp_w->left->color == BLACK) {
						tmp_w->color = RED;
						node = node->parent;
					}
					else {	
						if (tmp_w->left->color == BLACK) {
							tmp_w->right->color = BLACK;
							tmp_w->color = RED;
							_leftRotate(tmp_w);
							tmp_w = node->parent->left;
						}
						tmp_w->color = node->parent->color;
						node->parent->color = BLACK;
						tmp_w->left->color = BLACK;
						_rightRotate(node->parent);
						node = _root;
					}
				}
			}
			node->color = BLACK;
		}
		
		void	deleteNode(node_pointer node) {
			node_pointer tmp_x;
			node_pointer tmp_y;
			if (node == _nil)
				return;
			tmp_y = node;
			bool color = node->color;
			if (node->left == _nil) {
				tmp_x = node->right;
				_Red_Black_Treeransplant(node, node->right);
			}
			else if (node->right == _nil) {
				tmp_x = node->left;
				_Red_Black_Treeransplant(node, node->left);
			}
			else {
				tmp_y = _min(node->right);
				color = tmp_y->color;
				tmp_x = tmp_y->right;
				if (tmp_y->parent == node)
					tmp_x->parent = tmp_y;
				else {
					_Red_Black_Treeransplant(tmp_y, tmp_y->right);
					tmp_y->right = node->right;
					tmp_y->right->parent = tmp_y;
				}
				_Red_Black_Treeransplant(node, tmp_y);
				tmp_y->left = node->left;
				tmp_y->left->parent = tmp_y;
				tmp_y->color = node->color;
			}
			_cleanNode(node);
			if (color == BLACK)
				_deleteFix(tmp_x);
			_nil->max = _max(_root);
			_nil->min = _min(_root);
			_nil->parent = _nil;
			_size--;
		}

    protected:
		node_pointer    _newNode(const value_type &val) {
			node_pointer	node = _node_allocator.allocate(1);

			node->parent = 0;
			node->nil_node = _nil;
			node->left = _nil;
			node->right = _nil;
			node->color = RED;
			node->data = _allocator.allocate(1);
			_allocator.construct(node->data, val);
			return node;
		}

		node_pointer	_min(node_pointer node) const {
			if (node == _nil)
				return _nil;
			node_pointer	res = node;
			while (res->left != _nil)
				res = res->left;
			return res;
		}

		node_pointer	_max(node_pointer node) const {
			if (node == _nil)
				return _nil;
			node_pointer res = node;
			while (res->right != _nil)
				res = res->right;
			return res;
		}

		bool	        _isEqual(value_type const & x, value_type const & y) const {
			return !_key_compare(x, y) && !_key_compare(y, x);
		}

		void	        _cleanNode(node_pointer node) {
			if (node != _nil) {
				_allocator.destroy(node->data);
				_allocator.deallocate(node->data, 1);
				_node_allocator.deallocate(node, 1);
			}
		}

		void	        _cleanTree(node_pointer node) {
			if (node != _nil) {
				_cleanTree(node->left);
				_cleanTree(node->right);
				_cleanNode(node);
			}
		}

		void            _leftRotate(node_pointer x) {
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == 0)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void            _rightRotate(node_pointer x) {
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == 0)
				this->_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void            _Red_Black_Treeransplant(node_pointer node_a, node_pointer node_b) {
			if (node_a->parent == 0)
				_root = node_b;
			else if (node_a->parent->left == node_a)
				node_a->parent->left = node_b;
			else
				node_a->parent->right = node_b;
			node_b->parent = node_a->parent;
		}
};

#endif
