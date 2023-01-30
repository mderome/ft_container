#ifndef EQUAL_HPP
# define EQUAL_HPP

//equal
namespace ft {
	template <class ite1, class ite2>
	bool	equal(ite1 first1, ite1 last1, ite2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class ite1, class ite2, class predicate>
	bool	equal(ite1 first1, ite1 last1, ite2 first2, predicate pred) {
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return (true);
	}

	template <class ite1, class ite2>
	bool	lexicographical_compare(ite1 first1, ite1 last1, ite2 first2, ite2 last2) {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class ite1, class ite2, class Compare>
	bool	lexicographical_compare(ite1 first1, ite1 last1, ite2 first2, ite2 last2, Compare comp) {
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class T>
	void	swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
}
#endif
