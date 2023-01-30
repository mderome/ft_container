#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <iostream>

namespace ft
{

	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const { return value; };
	};


	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <class T> struct is_integral : public false_type {};
	template <class T> struct is_integral<const T> : public is_integral<T> {};
	template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
	template <class T> struct is_integral<volatile T> : public is_integral<T>{};

	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<unsigned long> : public true_type{};

	template<> struct is_integral<signed char> : public true_type{};
	template<> struct is_integral<short> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<long> : public true_type{};

	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<bool> : public true_type{};


	template<> struct is_integral<wchar_t> : public true_type{};



	template <typename T> class is_trivially_copyable : public false_type {};
	template <> class is_trivially_copyable<bool> : public true_type {};
	template <> class is_trivially_copyable<char> : public true_type {};
	template <> class is_trivially_copyable<wchar_t> : public true_type {};
	template <> class is_trivially_copyable<signed char> : public true_type {};
	template <> class is_trivially_copyable<signed short> : public true_type {};
	template <> class is_trivially_copyable<signed int> : public true_type {};
	template <> class is_trivially_copyable<signed long> : public true_type {};
	template <> class is_trivially_copyable<unsigned char> : public true_type {};
	template <> class is_trivially_copyable<unsigned short> : public true_type {};
	template <> class is_trivially_copyable<unsigned int> : public true_type {};
	template <> class is_trivially_copyable<unsigned long> : public true_type {};
	template <> class is_trivially_copyable<float> : public true_type {};
	template <> class is_trivially_copyable<double> : public true_type {};
	template <> class is_trivially_copyable<long double> : public true_type {};

}

#endif
