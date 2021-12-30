/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:32:37 by namenega          #+#    #+#             */
/*   Updated: 2021/12/30 18:23:14 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <type_traits>

namespace ft {
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

	/*	Const is_integral */
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
