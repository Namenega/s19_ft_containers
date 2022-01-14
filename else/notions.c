/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:04:17 by namenega          #+#    #+#             */
/*   Updated: 2022/01/14 14:52:47 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	If doing the function inside the template, the function acquires the
	implicit inline property. */

/* ************************************************************************** */
/* ***************************** UTILS/UTILS.HPP **************************** */
/* ************************************************************************** */

/*	Traits */
/*	The default traits class template is empty. It allows, when compiling,
	to get informations about data types on a generic base. It is a double
	abstraction. */

/*	Enable if */
/*	It is a trait that allows to control SFINAE application. It's defined on
	a static condition of a type (enable_if< bool,T=void >)
	std::enable_if< true, T >::type is equal to T.
	std::enable_if< false, T >::type is undefined which means that it eliminates
	a template among the examinated template to generate code.
	The type T is enabled as member type 'enable_if::type' if condition is true. 
	*/

/*	integral_constant */
/*	This template is designed to provide compile-time constants as types.
	It is used as the base class for trait types, especially in their bool
	variant. */

/*	is_integral */
/*	template<class T> struct is_integral.
	Trait class identifies whether T is an integral type. It inherits from
	integral_constant as being either true_type or false_type, depending on
	whether T is an integral type. */

/* ************************************************************************** */
/* ************************** ITERATOR/ITERATOR.HPP ************************* */
/* ************************************************************************** */

/*	ptrdiff_t */
/*	It is the signed integer type of the result of subtracting two pointers
	The bit width is not less than 17.
	It is used for pointer arithmetic and array indexing, if negative values
	are possible.
	Working with c++ container lib, the proper type for the difference between
	iterators is the member 'typedef difference_type'.
	https://en.cppreference.com/w/cpp/types/ptrdiff_t */

/*	iterator_traits */
/*	 */


/* ************************************************************************** */
/* **************************** VECTOR/VECTOR.HPP *************************** */
/* ************************************************************************** */

/*	A vector is a sequence container that encapsulates dynamic size arrays.
	If we reach the size of the array and want to put more data in it, it will
	expand the size by finding memory larger than the occupied size. It will
	copy the entire content on the larger space memory. If there is a pointer on
	an existing element and the content is copied somewhere else, the pointer
	will be completely invalid.
	Arrays have contiguous data (l'une a coté de l'autre) */

/* ***************************** std::allocator ***************************** */
/*	allocate() */
/*	pointer allocate(size_type n); <memory>; Attempts to allocate a block of
	storage with a size large enough to contain n elements of member type
	sizeof(value_type), and returns a pointers to the first element. */
/*	construct() */
/*	void construct(pointer p, const_reference val); Construct an object of
	type T in allocated storage pointed to by 'p', using placement-new.
	p = pointer to allocated uninitialized storage
	val = the value to use as the copy constructor argument. */
/*	explicit */
/*	The explicit keyword to the constructor prevents the compiler from using
	that constructor for implicit conversion. */

/* ************************************************************************** */
/* ******************************* MAP/MAP.HPP ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** STACK/STACK.HPP **************************** */
/* ************************************************************************** */

/*	Stacks are a type of container adaptor, specifically designed to operate in
	a LIFO context, where elements are inserted and extracted only from one end
	of the container.
	Container adaptor are classes the use an encapsulated object of a specific
	container class as its underlying container, providing a specific set of
	member functions to access its elements. */

/*	friend */
/*	In some circonstances, it is more convenient to grant member level access
	to functions that are not members of a class. Only the class implementer
	ca declare who its friends are. In a class definition, use the 'friend'
	keyword and the name of a non member function to grant it access to the
	and protected members of your class. In a template definition, a type
	parameter can be declared as a friend.
	
	I you declare a friend function that was not previously declared, that
	function is exported to the enclosing non-class scope. */
