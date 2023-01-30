// create class map with red-blacktree

 #ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include <algorithm>
# include "equal.hpp"
# include "rb_tree.hpp"
# include "iterator.hpp"
# include "pair.hpp"
# include "rbt_ite.hpp"


namespace ft {
    template < class Key, class T, class Compare = std::less<Key>,
                class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {

        public:
            typedef Key											key_type;
            typedef T											mapped_type;
            typedef ft::pair<const key_type, mapped_type>		value_type;
            typedef Compare										key_compare;
            typedef Alloc										allocator_type;


            class value_compare : public std::binary_function<value_type, value_type, bool> {
                public:
                    bool	operator()(const value_type &x, const value_type &y) const {
                        return comp(x.first, y.first);
                    }
                    value_compare(Compare c) : comp(c) {}

                protected:
                    Compare comp;
            };

            typedef typename allocator_type::reference							reference;
            typedef typename allocator_type::const_reference					const_reference;
            typedef typename allocator_type::pointer							pointer;
            typedef typename allocator_type::const_pointer						const_pointer;

            typedef Red_Black_Tree<value_type, value_compare, allocator_type>		        tree_type;
            typedef typename tree_type::pair_type								pair_type;
            typedef typename tree_type::pair_range								pair_range;
            typedef typename tree_type::const_pair_range						const_pair_range;
            typedef typename tree_type::iterator 								iterator;
            typedef typename tree_type::const_iterator							const_iterator;
            typedef typename tree_type::reverse_iterator						reverse_iterator;
            typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
            
            typedef typename iterator_traits<iterator>::difference_type			difference_type;
            typedef size_t														size_type;

        private:
            key_compare		_key_comp;
            tree_type		_rbt;

        public:
            explicit map(const key_compare & comp = key_compare(),
                            const allocator_type & alloc = allocator_type())
                            : _rbt(comp , alloc) {}

            template <class InputIterator>
            map(InputIterator first, InputIterator last,
                    const key_compare & comp = key_compare(),
                    const allocator_type & alloc = allocator_type())
                    : _rbt(comp , alloc) {
                    while (first != last)
                        _rbt.insert(*first++);
                }

            map(const map & x) : _rbt(x.key_comp(), x.get_allocator()) {
                const_iterator pos = x.begin();
                while (pos != x.end())
                    _rbt.insert(*pos++);
            }

            ~map() {}

            map &	operator=(const map & rhs) {
                _rbt = rhs._rbt;
                _key_comp = rhs._key_comp;
                return *this;
            }

            iterator				begin() { return _rbt.begin(); }

            const_iterator			begin() const { return _rbt.begin(); }

            iterator				end() { return (_rbt.end()); }

            const_iterator			end() const { return (_rbt.end()); }

            reverse_iterator		rbegin() { return (_rbt.rbegin()); }

            const_reverse_iterator	rbegin() const { return (_rbt.rbegin()); }

            reverse_iterator		rend() { return (_rbt.rend()); }

            const_reverse_iterator	rend() const { return (_rbt.rend()); }

            bool		            empty() const { return (_rbt.empty() == true); }

            size_type	            size() const { return (_rbt.get_size()); }

            size_type	            max_size() const {
                return _rbt.get_max_size();
            }

            mapped_type& at (const key_type& k) {
                iterator it = find(k);
                if (it == end())
                    throw std::out_of_range("map::at");
                return it->second;
            }

            mapped_type&		    operator[](const key_type &k) {
                value_type val = ft::make_pair(k, mapped_type());
                return (((_rbt.insert(val)).first)->second);
            }

            pair_type	            insert(value_type const & val) {
                return _rbt.insert(val);
            }

            iterator	            insert(iterator position, value_type const & val) {
                return _rbt.insertIter(position, val);
            }

            template <class InputIterator>
            void	insert(InputIterator first, InputIterator last) {
                while (first != last)
                    _rbt.insert(*first++);	
            }

            void	                erase(iterator position) {
                if (position == end())
                        return;
                key_type key = position->first;
                value_type val = ft::make_pair(key, mapped_type());

                _rbt.deleteNode(_rbt.searchTree(val));
            }

            size_type	            erase(const key_type & k) {
                value_type val = ft::make_pair(k, mapped_type());

                iterator pos(_rbt.searchTree(val));
                if (pos != end()) {
                    _rbt.deleteNode(_rbt.searchTree(val));
                    return 1;
                }
                return 0;
            }

            void	                erase(iterator first, iterator last) {
                if (first != end()) {
                    while(first != last)
                        _rbt.deleteNode(_rbt.searchTree(*first++));
                }
            }

            void	swap(map& x) {
                _rbt.swap(x._rbt);
            }

            void	clear() {
                _rbt.clean();
            }

            key_compare		key_comp() const { return (this->_key_comp); }

            value_compare	value_comp() const { return _rbt.get_key_compare(); }

            iterator	find(key_type const & k) {
                value_type val = ft::make_pair(k, mapped_type());
                return iterator(_rbt.searchTree(val));
            }

            const_iterator	find(key_type const & k) const {
                value_type val = ft::make_pair(k, mapped_type());
                return const_iterator(_rbt.searchTree(val));
            }

            size_type	count(key_type const & k) const {
                value_type val = ft::make_pair(k, mapped_type());
                const_iterator res = _rbt.searchTree(val);
                if (res == end())
                    return 0;
                else
                    return 1;
            }

            iterator	lower_bound(const key_type & k) {
                value_type val = ft::make_pair(k, mapped_type());
                return (iterator(_rbt.get_lower_bound(val)));
            }

            const_iterator	lower_bound(const key_type & k) const {
                value_type val = ft::make_pair(k, mapped_type());
                return (const_iterator(_rbt.get_lower_bound(val)));
            }

            iterator	upper_bound(const key_type & k) {
                value_type val = ft::make_pair(k, mapped_type());
                return (iterator(_rbt.get_upper_bound(val)));
            }

            const_iterator	upper_bound(const key_type & k) const {
                value_type val = ft::make_pair(k, mapped_type());
                return (const_iterator(_rbt.get_upper_bound(val)));
            }

            pair_range	equal_range(const key_type & k) {
                value_type val = ft::make_pair(k, mapped_type());
                return (_rbt.get_equal_range(val));
            }

            const_pair_range	equal_range(const key_type & k) const {
                value_type val = ft::make_pair(k, mapped_type());
                return (_rbt.get_equal_range(val));
            }
            allocator_type	get_allocator() const { return _rbt.get_data_allocator(); }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool	operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator<=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        if (lhs == rhs || lhs < rhs)
            return true;
        return false;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator>(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        return (rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator>=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs) {
        if (lhs == rhs || lhs > rhs)
            return true;
        return false;
    }

    template <class Key, class T, class Compare, class Alloc>
    void	swap(map<Key, T, Compare, Alloc> & x, map<Key, T, Compare, Alloc> & y){
        x.swap(y);
    }
};

#endif
