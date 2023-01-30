/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:30:10 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/28 18:31:49 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
template <typename T0, typename T1>
struct pair
{
	// Member types
	typedef T0	first_type;
	typedef T1	second_type;

	// Attributes
	first_type	first;
	second_type	second;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new pair object. (Default constructor)
	 */
	pair(void) :
		first(),
		second() {}

	/**
	 * @brief	Construct a new pair object. (Parameters constructor)
	 * 
	 * @param	a The value of the `first` attribute of the pair.
	 * @param	b The value of the `second` attribute of the pair.
	 */
	pair(first_type const &a, second_type const &b) :
		first(a),
		second(b) {}
	
	/**
	 * @brief	Construct a new pair object from another one.
	 * 			Allow mutable to constant pair conversion. (copy constructor)
	 * 
	 * @tparam	U0 The type of the `first` attribute of the pair to copy.
	 * @tparam	U1 The type of the `second` attribute of the pair to copy.
	 * 
	 * @param	src The pair to copy.
	 */
	template <typename U0, typename U1>
	pair(pair<U0, U1> const &src) :
		first(src.first),
		second(src.second) {}

}; // struct pair

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

/**
 * @brief	Check if two pair are equivalent.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are equivalent, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator==(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

/**
 * @brief	Check if two pair are different.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are different, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator!=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return !(lhs == rhs);
}

/**
 * @brief	Check if two pair are strictly ordered.
 * 			Allow comparison between mutable and constant pair.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are strictly ordered, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator<(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

/**
 * @brief	Check if two pair are strictly reverse ordered.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are strictly reverse ordered, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator>(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return rhs < lhs;
}

/**
 * @brief	Check if two pair are ordered or equivalent.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are ordered or equivalent, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator<=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return !(rhs < lhs);
}

/**
 * @brief	Check if two pair are reverse ordered or equivalent.
 * 
 * @tparam	T0 The type of the `first` member of both of the pair.
 * @tparam	T1 The type of the `second` member of both of the pair.
 * 
 * @param	lhs The left hand side pair to compare.
 * @param	rhs The right hand side pair to compare.
 * 
 * @return	Either true if the two pair are reverse ordered or equivalent, or false if not.
 */
template <typename T0, typename T1>
inline bool	operator>=(pair<T0, T1> const &lhs, pair<T0, T1> const &rhs)
{
	return !(lhs < rhs);
}

// ***************************************************************************************************************** //
//                                               Specialized Functions                                               //
// ***************************************************************************************************************** //

/**
 * @brief	Create a new pair object.
 * 
 * @tparam	T0 The type of the `first` member of the pair.
 * @tparam	T1 The type of the `second` member of the pair.
 * 
 * @param	a The value of the `first` member of the pair.
 * @param	b The value of the `second` member of the pair.
 * 
 * @return	The newly created pair.
 */
template <typename T0, typename T1>
pair<T0, T1>	make_pair(T0 const &a, T1 const &b)
{
	return pair<T0, T1>(a, b);
}

} // namespace ft

#endif
