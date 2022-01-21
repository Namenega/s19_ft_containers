/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:32:37 by namenega          #+#    #+#             */
/*   Updated: 2022/01/21 14:42:56 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <type_traits>
# include <iostream>

namespace ft {
	/* *************************** BINARY_FUNCTION ************************** */
	/*	Base class for creating function objects with two arguments. It does not
		defined operator() [see: less]. */
	template< class Arg1, class Arg2, class Result >
	struct	binary_function {
		typedef	Arg1	first_argument_type;
		typedef	Arg2	second_argument_type;
		typedef	Result	result_type;
	};

	/* ******************************** LESS ******************************** */
	/*	std::less */
	/*	Function object for performing comparisons. Unless specialized, invokes
		operator< on type T. Needed in prototype of MAP.
		A specialization of std::less for any pointer yields the implementation
		-defined strict total order, even if the buildt-in < operator does not.
		Function deducing argument and returns types. */
	template< class T >
	struct	less : binary_function< T, T, bool > {
		/*	These member types are obtained via publicly inheriting
			std::binary_function<T, T, bool> */
		typedef	T		first_argument_type;
		typedef	T		second_argument_type;
		typedef	bool	result_type;

		bool	operator()(const T & x, const T & y) const {
			return (x < y);
		}
	};

	/* ****************************** NULLPTR_T ***************************** */
	static class	nullptr_t {
		public:
			template< class T >
			operator	T*() const {
				return (0);
			}
			template< class U, class T >
			operator	T U::*() const {
				return (0);
			}
		private:
			void	operator&() const;
	}				u_nullptr = {};

	/* ************************* INPUTITERATOR EQUAL ************************ */
	template< class InputIterator1, class InputIterator2 >
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template< class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate p) {
		while (first1 != last1) {
			if (!p(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* *********************** LEXICOGRAPHICAL_COMPARE ********************** */
	/*	Checks if the first range [first1, last1] is lexicographically less than
		the second range [first2, last2]. */
	template< class InputIterator1, class InputIterator2 >
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template< class InputIterator1, class InputIterator2, class Compare >
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	/* ********************************************************************** */
	/* ****************************** ENABLE_IF ***************************** */
	/* ********************************************************************** */

	template< bool Cond, class T = void >
	struct	enable_if {};

	template< class T >
	struct enable_if< true, T> {
		typedef	T	type;
	};

	/* ************************** INTEGRAL_CONSTANT ************************* */

	template< class T, T v>
	struct	integral_constant {
		static const	T							value = v;
		typedef			T							value_type;
		typedef			integral_constant< T, v >	type;
		operator		T() {
			return (v);
		}
	};

	/* ***************************** IS_INTEGRAL **************************** */

	template < class T >
	struct	is_integral : public ft::integral_constant< bool, false > {};

	template <>
	struct	is_integral< bool > : public ft::integral_constant< bool, true > {};
	
	template <>
	struct	is_integral< char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< char16_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< char32_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< wchar_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< signed char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< short int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< long long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< unsigned char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< unsigned short int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< unsigned int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< unsigned long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< unsigned long long int > : public ft::integral_constant< bool, true > {};

	/* ****************** */
	/*	Const is_integral */
	/* ****************** */
	template <>
	struct	is_integral< const bool > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const char16_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const char32_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const wchar_t > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const signed char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const short int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const long long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const unsigned char > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const unsigned short int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const unsigned int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const unsigned long int > : public ft::integral_constant< bool, true > {};

	template <>
	struct	is_integral< const unsigned long long int > : public ft::integral_constant< bool, true > {};
}

#endif
